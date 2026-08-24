// -------------------------------------------
//					Line
// -------------------------------------------

//#include "Line.h"

//Line::Line(const string& line)
//{
	// Hint: some of string's member functions might come in handy here
	// for extracting words.
//}

//bool Line::contains(const Word& search_word) const
//{
//	return false;
//}
// whole cpp replaced
// -------------------------------------------
//					Line
// -------------------------------------------

#include "Line.h"
#include <sstream>

Line::Line(const string& line)
{
	string word;

	istringstream stream(line);

	while (stream >> word)
	{
		words_.push_back(Word{word});
	}
}

//bool Line::contains(const Word& search_word) const
//{
//	for (const auto& word : words_)
//	{
//		if (word == search_word)
//			return true;
//	}

//	return false;
//}
//replaced 
bool Line::contains(const Word& search_word) const
{
	if (!search_word.isQueryable())
		return false;

	for (const auto& word : words_)
	{
		if (word == search_word)
			return true;
	}

	return false;
}
