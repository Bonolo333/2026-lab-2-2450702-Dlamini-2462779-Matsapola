// -------------------------------------------
//					Paragraph
// -------------------------------------------

//#include "Paragraph.h"

//void Paragraph::addLine(const Line& line)
//{
//}

//tuple<bool, vector<int>> Paragraph::contains(const Word& search_word) const
//{
//	return {false, vector<int>{}};
//}
//replaced
// -------------------------------------------
//					Paragraph
// -------------------------------------------

#include "Paragraph.h"

void Paragraph::addLine(const Line& line)
{
	lines_.push_back(line);
}

tuple<bool, vector<int>> Paragraph::contains(const Word& search_word) const
{
	vector<int> line_numbers;

	for (int i = 0; i < lines_.size(); i++)
	{
		if (lines_[i].contains(search_word))
			line_numbers.push_back(i + 1);
	}

	return {!line_numbers.empty(), line_numbers};
}