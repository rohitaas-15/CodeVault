/*You are given an m x n integer matrix grid, and three integers row, col, and color. Each value in the grid represents the color of the grid square at that location.

Two squares are called adjacent if they are next to each other in any of the 4 directions.

Two squares belong to the same connected component if they have the same color and they are adjacent.

The border of a connected component is all the squares in the connected component that are either adjacent to (at least) a square not in the component, or on the boundary of the grid (the first or last row or column).

You should color the border of the connected component that contains the square grid[row][col] with color.

Return the final grid.*/

//https://leetcode.com/problems/coloring-a-border/description/



#include <bits/stdc++.h>
using namespace std;

int n, m;
int vis[51][51];

void borderColoring(vector<vector<int>> &grid, int row, int col, int color)
{

    int original = grid[row][col];
    if (row == 0 || row == n - 1 || col == 0 || col == m - 1)
    {
        grid[row][col] = color;
    }

    vis[row][col] = 1;

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (abs(i) != abs(j))
            {
                int nrow = row + i, ncol = col + j;

                if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && !vis[nrow][ncol])
                {
                    if (grid[nrow][ncol] != original)
                    {
                        grid[row][col] = color;
                    }
                    else
                    {
                        borderColoring(grid, nrow, ncol, color);
                    }
                }
            }
    return;
}

class Solution
{
public:
    vector<vector<int>> colorBorder(vector<vector<int>> &grid, int row, int col, int color)
    {
        n = grid.size(), m = grid[0].size();
        memset(vis, 0, sizeof(vis));

        borderColoring(grid, row, col, color);
        return grid;
    }
};