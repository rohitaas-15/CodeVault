/*You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.

Return the size of the largest island in grid after applying this operation.

An island is a 4-directionally connected group of 1s.
https://leetcode.com/problems/making-a-large-island/description/*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
int color[501][501], Size[501 * 501];

int dfs(int i, int j, vector<vector<int>> &grid, int col)
{
    color[i][j] = col;
    int sz = 1;

    for (int x = -1; x <= 1; x++)
        for (int y = -1; y <= 1; y++)
            if (abs(x) != abs(y))
            {
                int ni = i + x, nj = j + y;

                if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] == 1)
                {
                    if (color[ni][nj] == -1)
                    {
                        sz += dfs(ni, nj, grid, col);
                    }
                }
            }
    return sz;
}

class Solution
{
public:
    int largestIsland(vector<vector<int>> &grid)
    {
        n = grid.size(), m = grid[0].size();
        memset(color, -1, sizeof(color));
        memset(Size, 0, sizeof(Size));

        int col = 1, ans = 0;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (grid[i][j] == 1 && color[i][j] == -1)
                {
                    Size[col] = dfs(i, j, grid, col);
                    ans = max(ans, Size[col]);
                    col++;
                }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (grid[i][j] == 0)
                {
                    set<int> colors;
                    for (int x = -1; x <= 1; x++)
                        for (int y = -1; y <= 1; y++)
                            if (abs(x) != abs(y))
                            {
                                int ni = i + x, nj = j + y;

                                if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] == 1)
                                {
                                    colors.insert(color[ni][nj]);
                                }
                            }
                    int temp = 1;
                    for (auto i : colors)
                    {
                        temp += Size[i];
                    }
                    ans = max(ans, temp);
                }
        return ans;
    }
};
