/*You are given a matrix ‘MAT’, of size ‘M’ * ‘N’ and has numbers from 1 to 9. Find the number of magic square submatrix present in the matrix. A submatrix is a magic square if that matrix's size is 3 * 3 and consists of distinct numbers from 1 to 9 and having the sum of all the rows, columns, and diagonals equal.

For example:
Let matrix be :
8 3 4
1 5 9
6 7 2

The sum of the first row is: 15
The sum of the second row is: 15
The sum of the third row is: 15
The sum of the first column is: 15
The sum of the second column is: 15
The sum of the third column is: 15
The sum of both the diagonals is: 15
The matrix consists of distinct numbers from 1 to 9 and has the sum of all the rows, columns, and diagonals equal. So, it is a magic square
https://www.codingninjas.com/studio/problem-of-the-day/moderate*/

#include <bits/stdc++.h>
using namespace std;
map<vector<vector<int>>, int> isMagic;

void makeMagicSquares(int i, int j, int mask, vector<vector<int>> &temp)
{
    if (i == 3)
    {
        int sum = 15, sd1 = 0, sd2 = 0;
        for (int i = 0; i < 3; i++) // diagonals
        {
            sd1 += temp[i][i];
            sd2 += temp[i][2 - i];
        }

        if (sd1 != sd2)
            return;
        if (sd1 != sum)
            return;

        for (int i = 0; i < 3; i++)
        {
            int rsum = 0;
            for (int j = 0; j < 3; j++)
            {
                rsum += temp[i][j];
            }
            if (rsum != sum)
                return;
        }

        for (int i = 0; i < 3; i++)
        {
            int csum = 0;
            for (int j = 0; j < 3; j++)
            {
                csum += temp[j][i];
            }
            if (csum != sum)
                return;
        }
        isMagic[temp]++;
        return;
    }

    if (j == 3)
    {
        makeMagicSquares(i + 1, 0, mask, temp);
        return;
    }

    for (int no = 1; no <= 9; no++)
    {
        if ((mask & (1ll << no)) == 0)
        {
            temp[i][j] = no;
            makeMagicSquares(i, j + 1, mask | (1ll << no), temp);
            temp[i][j] = 0;
        }
    }
    return;
}
int countSqaures(int m, int n, vector<vector<int>> &mat)
{

    if (isMagic.size() == 0)
    {
        vector<vector<int>> temp(3, vector<int>(3, 0));
        makeMagicSquares(0, 0, 0, temp);
    }

    int ans = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int si = i, ei = i + 3, sj = j, ej = j + 3;
            if (ei <= m && ej <= n)
            {
                vector<vector<int>> check;
                for (int k = si; k < ei; k++)
                {
                    vector<int> temp;
                    for (int l = sj; l < ej; l++)
                    {
                        temp.push_back(mat[k][l]);
                    }
                    check.push_back(temp);
                }
                if (isMagic.count(check))
                    ans++;
            }
        }
    }
    return ans;
}