/*Given a matrix and a target, return the number of non-empty submatrices that sum to target.

A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.

Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.
https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/description/?envType=daily-question&envId=2024-01-28*/
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int numSubmatrixSumTarget(vector<vector<int>> &matrix, int target)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        int pre[n + 1][m + 1];
        memset(pre, 0, sizeof(pre));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                pre[i][j] = pre[i][j - 1] + pre[i - 1][j] - pre[i - 1][j - 1] + matrix[i - 1][j - 1];
            }
        }

        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                for (int k = i; k <= n; k++)
                {
                    for (int l = j; l <= m; l++)
                    {
                        int subMatSum = pre[k][l] - pre[i - 1][l] - pre[k][j - 1] + pre[i - 1][j - 1];
                        if (subMatSum == target)
                        {
                            ans++;
                        }
                    }
                }
            }
        }
        return ans;
    }
};