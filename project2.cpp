#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <regex>
#include <stdio.h>
#include <streambuf>
#include <string>
#include <vector>

using namespace std;

queue<double> solution;

void setSolution(vector<double> seq1, int seq1_len, vector<double> seq2,
				 int seq2_len, vector<double> target,
				 vector<vector<double>> &array, int x, int y)
{
	if (x + y == target.size())
		return;
	else if ((array[x][y] - (seq1[x] * target[x + y]) - array[x + 1][y]) <
				 .000000001 &&
			 x != seq1_len)
	{
		solution.push(seq1[x]);
		setSolution(seq1, seq1_len, seq2, seq2_len, target, array, x + 1, y);
	}
	else if ((array[x][y] - (seq2[y] * target[x + y]) - array[x][y + 1]) <
				 .000000001 &&
			 y != seq2_len)
	{
		solution.push(seq2[y]);
		setSolution(seq1, seq1_len, seq2, seq2_len, target, array, x, y + 1);
	}
	return;
}

double maxAlignment(vector<double> seq1, int seq1_len, vector<double> seq2,
					int seq2_len, vector<double> target,
					vector<vector<double>> &array, int x, int y)
{
	double a, b, c;
	if (array[x][y] != -1)
		return array[x][y];
	else if (x == seq1_len + 1 || y == seq2_len + 1 ||
			 (x == seq1_len && y == seq2_len))
	{
		array[x][y] = 0;

		if (x == seq1_len + 1 && y != seq2_len + 1)
			maxAlignment(seq1, seq1_len, seq2, seq2_len, target, array, x, y + 1);
		else if (x != seq1_len + 1 && y != seq2_len + 1)
			maxAlignment(seq1, seq1_len, seq2, seq2_len, target, array, x + 1, y);
		else if (x == seq1_len && y == seq2_len)
		{
			maxAlignment(seq1, seq1_len, seq2, seq2_len, target, array, x, y + 1);
			maxAlignment(seq1, seq1_len, seq2, seq2_len, target, array, x + 1, y);
		}
	}
	else
	{
		a = (seq1[x] * target[x + y]) +
			maxAlignment(seq1, seq1_len, seq2, seq2_len, target, array, x + 1, y);
		b = (seq2[y] * target[x + y]) +
			maxAlignment(seq1, seq1_len, seq2, seq2_len, target, array, x, y + 1);
		c = max(a, b);
		array[x][y] = c;
	}

	return array[x][y];
}

double maxAlignmentWrapper(vector<double> seq1, int seq1_len,
						   vector<double> seq2, int seq2_len,
						   vector<double> target)
{
	vector<vector<double>> array(seq1_len + 2, vector<double>(seq2_len + 2));

	for (int i = 0; i < seq1_len + 2; i++)
	{
		for (int j = 0; j < seq2_len + 2; j++)
		{
			array[i][j] = -1;
		}
	}

	double max =
		maxAlignment(seq1, seq1_len, seq2, seq2_len, target, array, 0, 0);

	setSolution(seq1, seq1_len, seq2, seq2_len, target, array, 0, 0);

	return max;
}

//splice of given vector is copied to temp vector and then returned
vector<double> GetSubVector(vector<double> buffer_vector, double start,
							double stop, double size)
{
	vector<double> temp(size);
	copy(buffer_vector.begin() + start, buffer_vector.begin() + stop,
		 temp.begin());
	return temp;
}

int main(int argc, char *argv[])
{
	//if a text file is used as an argument, it will read from it as the input,
	//otherwise input.txt is the default
	string file_name = "input.txt";
	if (argc > 1)
	{
		file_name = argv[1];
	}

	// vector to store all number from input.txt
	vector<double> buffer_vector;

	// defining regular expressions to extract numbers and remove whitespace
	regex number_input("(-?\\s*\\d+\\.?\\d*)");
	regex whitespace("\\s*");
	smatch match;

	// reading input.txt file and converting it to a single string
	ifstream input_stream(file_name);
	string input_file_text((std::istreambuf_iterator<char>(input_stream)),
						   std::istreambuf_iterator<char>());

	// regular expression loops through and get every number and negative sign and
	// discards whitespace so that seperated number and negative signs can be
	// joined. Converted to double and put in vector.
	while (regex_search(input_file_text, match, number_input))
	{
		buffer_vector.push_back(stod(regex_replace(match.str(), whitespace, "")));
		input_file_text = match.suffix();
	}

	//getting lengths for subvectors
	int seq1_len = int(buffer_vector.at(0));
	int seq2_len = int(buffer_vector.at(1));
	//getting seq1 subvector
	vector<double> seq1 =
		GetSubVector(buffer_vector, 2, 2 + seq1_len,
					 seq1_len);
	//getting seq2 subvector
	vector<double> seq2 =
		GetSubVector(buffer_vector, 2 + seq1_len, 2 + seq1_len + seq2_len,
					 seq2_len);
	//getting target vector
	vector<double> target = GetSubVector(
		buffer_vector, 2 + seq1_len + seq2_len, 2 + seq1_len * 2 + seq2_len * 2,
		seq1_len + seq2_len);

	// results are output to text file
	ofstream output_file;
	output_file.open("output.txt");
	if (!output_file.is_open())
	{
		return 1;
	}
	double max = maxAlignmentWrapper(seq1, seq1_len, seq2, seq2_len, target);
	cout << max << endl;
	output_file << max << endl;

	while (!solution.empty())
	{
		cout << solution.front() << " ";
		output_file << solution.front() << " ";
		solution.pop();
	}
	cout << endl;

	output_file.close();
}