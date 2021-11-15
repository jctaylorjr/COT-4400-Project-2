#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

double maxAlignment(vector<double> seq1, int seq1_len, vector<double> seq2, int seq2_len, vector<double> target, vector<vector<double>> &array, int x, int y)
{
    double a, b, c;
    if (array[x][y] != -1)
        return array[x][y];
    else if (x == seq1_len + 1 || y == seq2_len + 1 || (x == seq1_len && y == seq2_len))
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
        a = (seq1[x] * target[x + y]) + maxAlignment(seq1, seq1_len, seq2, seq2_len, target, array, x + 1, y);
        b = (seq2[y] * target[x + y]) + maxAlignment(seq1, seq1_len, seq2, seq2_len, target, array, x, y + 1);
        c = max(a, b);
        array[x][y] = c;
    }

    return array[x][y];
}

double maxAlignmentWrapper(vector<double> seq1, int seq1_len, vector<double> seq2, int seq2_len, vector<double> target)
{
    vector<vector<double>> array(seq1_len + 2, vector<double>(seq2_len + 2));

    for (int i = 0; i < seq1_len + 2; i++)
    {
        for (int j = 0; j < seq2_len + 2; j++)
        {
            array[i][j] = -1;
        }
    }

    double max = maxAlignment(seq1, seq1_len, seq2, seq2_len, target, array, 0, 0);

    return max;
}

vector<double> GetSubVector(vector<double> buffer_vector, double start, double stop, double size)
{
    vector<double> temp(size);
    copy(buffer_vector.begin() + start, buffer_vector.begin() + stop, temp.begin());
    return temp;
}

int main()
{
    //read file and fill: seq1_len, seq2_len, seq1, seq2, and target
    double buffer;
    vector<double> buffer_vector;

    // read file and fill: seq1_len, seq2_len, seq1, seq2, and target
    ifstream input_file;
    input_file.open("input.txt");
    if (!input_file.is_open()) {
        return 1;
    }
    while (input_file >> buffer) {
        buffer_vector.push_back(buffer);
    }
    input_file.close();

    int seq1_len = int(buffer_vector.at(0));
    int seq2_len = int(buffer_vector.at(1));
    vector<double> seq1 = GetSubVector(buffer_vector, 2, 2 + seq1_len, seq1_len); //start = 2, stop = 4, size = 3;
    vector<double> seq2 = GetSubVector(buffer_vector, 2 + seq1_len, 2 + seq1_len + seq2_len, seq2_len); //start = 5, stop = 7, size = 3;
    vector<double> target = GetSubVector(buffer_vector, 2 + seq1_len + seq2_len, 2 + seq1_len * 2 + seq2_len * 2, seq1_len + seq2_len); //start = 8, stop =13, size = 3;

    double max = maxAlignmentWrapper(seq1, seq1_len, seq2, seq2_len, target);
    cout << max << endl;
}