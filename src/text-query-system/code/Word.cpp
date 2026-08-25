// -------------------------------------------
//					Word
// -------------------------------------------

#include "Word.h"
#include <algorithm>
#include <cctype>


//Word::Word(const string& word): word_{word}
//{
	// throws an exception (in the form of WordContainsNoLetters object)
	// indicating that the word being constructed contains no letters
//	if (word_.empty()) throw WordContainsNoLetters{};

	// Note, we will cover exceptions in more detail later on in the course.
//}
// constructor replaced 1st time
//Word::Word(const string& word): word_{word}
//{
//	auto letter = find_if(word_.begin(), word_.end(), [](char c) {
//		return isalpha(static_cast<unsigned char>(c));
//	});

//	if (letter == word_.end())
//		throw WordContainsNoLetters{};
//}
// contstructor replaced 2nd time 
Word::Word(const string& word): word_{word}
{
	auto letter = find_if(word_.begin(), word_.end(), [](char c) {
		return isalpha(static_cast<unsigned char>(c));
	});

	if (letter == word_.end())
		throw WordContainsNoLetters{};

	auto space = find(word_.begin(), word_.end(), ' ');

	if (space != word_.end())
		throw WordContainsSpace{};
}
// overloads the equivalence operator which allows to Words to be compared using ==
//bool Word::operator==(const Word& rhs) const
//{
//	if (word_ == rhs.word_)
//		return true;
//	else
//		return false;
//}
// replaced operator
//bool Word::operator==(const Word& rhs) const
//{
//	string lhs = word_;
//	string rhsWord = rhs.word_;

//	transform(lhs.begin(), lhs.end(), lhs.begin(), ::tolower);
//	transform(rhsWord.begin(), rhsWord.end(), rhsWord.begin(), ::tolower);

//	return lhs == rhsWord;
//}
// replaced operator 2nd time
 bool Word::operator==(const Word& rhs) const
{
	string lhs;
	string rhsWord;

	for (char c : word_) {
		if (isalpha(static_cast<unsigned char>(c))) {
			lhs += static_cast<char>(tolower(static_cast<unsigned char>(c)));
		}
	}

	for (char c : rhs.word_) {
		if (isalpha(static_cast<unsigned char>(c))) {
			rhsWord += static_cast<char>(tolower(static_cast<unsigned char>(c)));
		}
	}

	return lhs == rhsWord;
}
//bool Word::isQueryable() const
//{
//	return false;
//}
// bool replaced 
bool Word::isQueryable() const
{
	return word_.size() >= 3;
}
