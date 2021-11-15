#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int maxAlignmentWrapper(vector<double> seq1, int n, vector<double> seq2, int m, vector<double> target)
{
    vector<vector<double>> array(n+2, vector<double>(m+2));

    for(int i = 0; i < n + 2; i++)
        for(int j = 0; j < m + 2; j++)
            array[i][j] = 0;

    return maxAlignment(seq1, n, seq2, m, target, array, 0, 0);
}

int maxAlignment(vector<double> seq1, int n, vector<double> seq2, int m, vector<double> target, vector<vector<double>> &array, int x, int y)
{
    double z;
    if(array[x][y] != 0)
        return array[x][y];
    else if (x == n + 2 || y == m + 2 || (x == n + 1 && y == m + 1))
        array[x][y] = 0;
    else
        z = max( (seq1[x] * target[x+y]) + maxAlignment(seq1, n, seq2, m, target, array, x + 1, y), (seq2[y] * target[x+y]) + maxAlignment(seq1, n, seq2, m, target, array, x, y + 1));
        array[x][y] = z;
    
    return array[x][y];
}

int main()
{
    //read file and fill: n, m, seq1, seq2, and target
    

    int n = 3;
    int m = 3;
    vector<double> seq1{1, 2, 7};
    vector<double> seq2{1, 3, 6};
    vector<double> target{1, 2, 1, 3, 7, 6};


    double max = maxAlignmentWrapper(seq1, n, seq2, m, target);
    cout << max << endl;
}