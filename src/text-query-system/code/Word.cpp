// -------------------------------------------
//					Word
// -------------------------------------------

#include "Word.h"
#include <algorithm>
#include <cctype>

Word::Word(const string& word)
{
	// A word cannot contain a space - check this BEFORE stripping punctuation,
	// since a space is not punctuation and would otherwise be lost.
	if (word.find(' ') != string::npos) throw WordContainsSpace{};

	// Make a working copy and strip out all punctuation characters.
	auto cleaned = word;
	cleaned.erase(remove_if(cleaned.begin(), cleaned.end(),
		[](unsigned char c) { return ispunct(c); }), cleaned.end());

	// If nothing is left after removing punctuation, the word contained no
	// letters (e.g. it consisted solely of punctuation, or was empty to
	// begin with).
	if (cleaned.empty()) throw WordContainsNoLetters{};

	// Store the word in lowercase. This means operator== (below) and
	// isQueryable() automatically become case-insensitive, since they just
	// compare/measure this normalised form.
	transform(cleaned.begin(), cleaned.end(), cleaned.begin(),
		[](unsigned char c) { return tolower(c); });

	word_ = cleaned;
}

// overloads the equivalence operator which allows to Words to be compared using ==
bool Word::operator==(const Word& rhs) const
{
	if (word_ == rhs.word_)
		return true;
	else
		return false;
}

bool Word::isQueryable() const
{
	// Words having less than 3 letters cannot be queried
	return word_.size() >= 3;
}