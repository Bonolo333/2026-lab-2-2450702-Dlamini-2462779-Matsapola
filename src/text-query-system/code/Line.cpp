// -------------------------------------------
//					Line
// -------------------------------------------

#include "Line.h"
#include <sstream>
#include <algorithm>
#include <cctype>

Line::Line(const string& line)
{
	string word;

	istringstream stream(line);

	while (stream >> word)
	{
		auto letter = find_if(word.begin(), word.end(), [](char c) {
			return isalpha(static_cast<unsigned char>(c));
		});

		if (letter != word.end())
		{
			words_.push_back(Word{word});
		}
	}
}

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
