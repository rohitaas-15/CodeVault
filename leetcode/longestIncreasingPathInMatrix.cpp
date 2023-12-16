/*Given an m x n integers matrix, return the length of the longest increasing path in matrix.

From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).

https://leetcode.com/problems/longest-increasing-path-in-a-matrix/description/*/

#include <bits/stdc++.h>
using namespace std;

const int N = 202;
int vis[N][N];
vector<vector<int>> dp(N, vector<int>(N, -1));

int n, m;

int dfs(int x, int y, vector<vector<int>> &matrix)
{
    if (dp[x][y] != -1)
    {
        return dp[x][y];
    }

    int len = 1;

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (abs(i) != abs(j))
            {
                int nx = x + i, ny = y + j;

                if (nx >= 0 && nx < n && ny >= 0 && ny < m && matrix[nx][ny] > matrix[x][y])
                {
                    len = max(len, 1 + dfs(nx, ny, matrix));
                }
            }

    return dp[x][y] = len;
}

class Solution
{
public:
    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        n = matrix.size(), m = matrix[0].size();
        dp.clear();
        dp.resize(N, vector<int>(N, -1));

        int ans = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                ans = max(ans, dfs(i, j, matrix));
            }
        return ans;
    }
};