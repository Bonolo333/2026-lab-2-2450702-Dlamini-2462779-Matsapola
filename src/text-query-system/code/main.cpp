#include <iostream>
#include <string>
#include "FileReader.h"
#include "Paragraph.h"
#include "Word.h"

using namespace std;

int main()
{
	auto filename = ""s;
	cout << "Please enter file name: ";
	cin >> filename;

	auto paragraph = Paragraph{};

	try {
		auto reader = FileReader{filename};
		reader.readFileInto(paragraph);
	}
	catch (const FileCannotBeOpened&) {
		cout << "Could not open file: " << filename << endl;
		return 1;
	}

	cout << "Please enter a word to search for or \".\" to quit: ";
	auto search_term = ""s;

	while (cin >> search_term && search_term != ".") {
		cout << endl;

		try {
			auto search_word = Word{search_term};
			auto [found, line_numbers] = paragraph.contains(search_word);

			if (found) {
				cout << "Word found: line " << line_numbers.front() << endl;
				for (auto it = next(line_numbers.begin()); it != line_numbers.end(); ++it) {
					cout << "            line " << *it << endl;
				}
			}
			else {
				cout << "Word not found" << endl;
			}
		}
		catch (const WordContainsNoLetters&) {
			cout << "That is not a valid word - please try again." << endl;
		}
		catch (const WordContainsSpace&) {
			cout << "Please enter a single word, without spaces." << endl;
		}

		cout << endl << "Please enter a word to search for or \".\" to quit: ";
	}

	return 0;
}

// --- Answer to Exercise 5.4, part 2 ---
// If a word appears twice on the same line, our program still only reports
// that line number once. This is because Line::contains() only returns a
// bool (does this line contain the word at all?), and Paragraph::contains()
// simply adds a line's number to the result once if that bool is true - it
// has no way of knowing there were multiple matches on that line.
//
// To report this properly (e.g. print the line number twice, or show a
// count of occurrences per line), we would need to change the design:
// Line::contains() would need to return something richer than a bool, such
// as a count of matches or a vector of the word's positions within the
// line, and Paragraph::contains() would need to use that information and
// change its own return type accordingly. Since we were told not to modify
// the public interfaces of Word, Line and Paragraph, this redesign is
// outside the scope of the current exercise - but it illustrates how a
// small change in requirements can ripple through class interfaces in an
// OO design.