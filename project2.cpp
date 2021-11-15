#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int MaxAlignment(vector<int> seq1, int seq1_len, vector<int> seq2, int seq2_len, vector<int> target, vector<vector<int>> &array, int x, int y)
{
    int z;
    if(array[x][y] != 0)
        return array[x][y];
    else if (x == seq1_len + 2 || y == seq2_len + 2 || (x == seq1_len + 1 && y == seq2_len + 1))
        array[x][y] = 0;
    else
        z = max( (seq1[x] * target[x+y]) + MaxAlignment(seq1, seq1_len, seq2, seq2_len, target, array, x + 1, y), (seq2[y] * target[x+y]) + MaxAlignment(seq1, seq1_len, seq2, seq2_len, target, array, x, y + 1));
        array[x][y] = z;
    
    return array[x][y];
}

int MaxAlignmentWrapper(vector<int> seq1, int seq1_len, vector<int> seq2, int seq2_len, vector<int> target)
{
    vector<vector<int>> array(seq1_len+2, vector<int>(seq2_len+2));

    for(int i = 0; i < seq1_len + 2; i++)
        for(int j = 0; j < seq2_len + 2; j++)
            array[i][j] = 0;

    return MaxAlignment(seq1, seq1_len, seq2, seq2_len, target, array, 0, 0);
}

vector<int> GetSubVector(vector<int> buffer_vector, int start, int stop, int size)
{
    vector<int> temp(size);
    copy(buffer_vector.begin() + start, buffer_vector.begin() + stop, temp.begin());
    return temp;
}

int main()
{
    int buffer;
    vector<int> buffer_vector;

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

    int seq1_len = buffer_vector.at(0);
    int seq2_len = buffer_vector.at(1);
    //comments assume example input.txt numbers from project pdf, start index 0
    vector<int> seq1 = GetSubVector(buffer_vector, 2, 2 + seq1_len, seq1_len); //start = 2, stop = 4, size = 3
    vector<int> seq2 = GetSubVector(buffer_vector, 2 + seq1_len, 2 + seq1_len + seq2_len, seq2_len); //start = 5, stop = 7, size = 3
    vector<int> target = GetSubVector(buffer_vector, 2 + seq1_len + seq2_len, 2 + seq1_len * 2 + seq2_len * 2, seq1_len + seq2_len); //start = 8, stop =13, size = 3

    //int max_alignment_score = MaxAlignmentWrapper(seq1, seq1_len, seq2, seq2_len, target);
    //cout << max_alignment_score << endl;
}