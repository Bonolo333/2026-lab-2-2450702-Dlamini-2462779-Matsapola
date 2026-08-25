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
	auto line_numbers = vector<int>{};

	// Line numbers are 1-indexed (as shown in the sample program output),
	// so we track our own counter rather than using the loop index.
	auto line_number = 1;
	for (const auto& line : lines_) {
		if (line.contains(search_word)) {
			line_numbers.push_back(line_number);
		}
		++line_number;
	}

	return {!line_numbers.empty(), line_numbers};
}