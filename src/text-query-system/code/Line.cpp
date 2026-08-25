// -------------------------------------------
//					Line
// -------------------------------------------

#include "Line.h"
#include <sstream>
#include <algorithm>

Line::Line(const string& line)
{
	// Split the line into whitespace-separated tokens using a stringstream -
	// this is exactly what the >> operator does for strings.
	auto stream = istringstream{line};
	auto token = ""s;

	while (stream >> token) {
		try {
			// Word's constructor does all the validation (no spaces, at
			// least one letter) and normalisation (lowercase, punctuation
			// stripped) for us.
			words_.push_back(Word{token});
		}
		catch (const WordContainsNoLetters&) {
			// The token was made up entirely of punctuation (e.g. "--" or
			// "...") so it isn't a real word - simply skip it.
		}
	}
}

bool Line::contains(const Word& search_word) const
{
	// The brief states the system does not need to support queries for
	// words shorter than 3 letters, so we refuse those up front.
	if (!search_word.isQueryable()) return false;

	return any_of(words_.begin(), words_.end(),
		[&search_word](const Word& word) { return word == search_word; });
}