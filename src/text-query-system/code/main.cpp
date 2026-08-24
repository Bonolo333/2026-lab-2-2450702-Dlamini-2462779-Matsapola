#include <iostream>
#include "FileReader.h"

using namespace std;
using namespace std::string_literals;

int main()
{
	auto file_name = ""s;
	cout << "Please enter file name: ";
	cin >> file_name;

	auto filereader = FileReader{file_name};
	auto paragraph = Paragraph{};
	filereader.readFileInto(paragraph);

	auto search_word = ""s;

	while (true)
	{
		cout << "Please enter a word to search for or \".\" to quit: ";
		cin >> search_word;

		if (search_word == ".")
			break;

		auto [found, line_numbers] = paragraph.contains(Word{search_word});

		if (found)
		{
			cout << "Word found:";
			for (auto line_number : line_numbers)
				cout << " line " << line_number;
			cout << endl;
		}
		else
		{
			cout << "Word not found" << endl;
		}
	}
  // If a word appears twice on the same line, the current design only returns
// the line number once because Paragraph records whether each Line contains
// the word, rather than counting how many times it occurs.
	return 0;
}