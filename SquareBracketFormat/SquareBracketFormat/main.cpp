/*
* Created by Jason Domican
*
* Program to numerically format references in the format [1], [2], [3], etc.
* 
* Text file should have sets of empty [] brackets in the file already in two sections -
* the 'body' and the 'references' section. This is to ensure that references are kept together
*
* Example orginal file: 
*
*	This is a reference []
*	This is another reference []
*	You can read more about this at the link [] below
*
*	References -
*
*	[] Amazon.com: https://amazon.com
*	[] Google.com: https://google.com
*	[] Wikipeia.org: https://wikipedia.org
*
* Becomes:
*
*	This is a reference [1]
*	This is another reference [2]
*	You can read more about this at the link [3] below
*
*	References - 
* 
*	[1] Amazon.com: https://amazon.com 
*	[2] Google.com: https://google.com
*	[3] Wikipeia.org: https://wikipedia.org
*
* This program adds the numbers to the references for you, when creating the original file you should just use [] in the text.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp> // include Boost, a C++ library
using namespace std;

int main()
{
	//string file_name;
	//cout << "Enter a filename: ";
	//cin >> file_name;

	ifstream input_file("text-to-reference.txt");
	char input_char;
	string full_file;

	// While the next character is not an End Of File marker
	// read the character and put it into a string
	while ((input_char = input_file.get()) != EOF)	
	{
		full_file += input_char;
	}
	input_file.close();

	// First get the total number of [] references in the file
	int count_references = 0;
	for (int i = 0; i < full_file.size() - 1; i++)
	{
		if (full_file[i] == '[' && full_file[i + 1] == ']')
		{
			count_references++;
		}
	}

	// Divide by 2 as each reference has 2 []'s, one in the body of 
	// the text, one in the references section at the end of the text
	cout << "\n*** There are " << count_references / 2 << " references in this file ***\n\n";

	// Replace the [] with a temporary number in the format '[n' to keep track of each reference.
	int count_replaced = 0;
	for (int i = 0; i < full_file.size() - 1; i++)
	{
		// After passing the halfway mark (end of body of text), restart at 1 (for the references section)
		if (count_replaced >= count_references / 2)
		{
			count_replaced = 0;
		}
		else
		{
			// Replace '[]' with '[n', n being the reference number
			if (full_file[i] == '[' && full_file[i + 1] == ']')
			{
				full_file[i + 1] = '0' + (count_replaced + 1);
				count_replaced++;
			}
		}

	}

	// For each reference, replace '[n' with '[n]' in both the body and references section
	for (int i = 0; i < count_references / 2; i++)
	{
		boost::replace_all(full_file, "[" + to_string(i + 1), "[" + to_string(i + 1) + "]");
	}

	ofstream out("referenced.txt");
	out << full_file;
	out.close();

	cout << full_file;

	system("pause");
	return 0;
}
