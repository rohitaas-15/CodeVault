/*You are given a rows x cols matrix grid representing a field of cherries where grid[i][j] represents the number of cherries that you can collect from the (i, j) cell.

You have two robots that can collect cherries for you:

Robot #1 is located at the top-left corner (0, 0), and
Robot #2 is located at the top-right corner (0, cols - 1).
Return the maximum number of cherries collection using both robots by following the rules below:

From a cell (i, j), robots can move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).
When any robot passes through a cell, It picks up all cherries, and the cell becomes an empty cell.
When both robots stay in the same cell, only one takes the cherries.
Both robots cannot move outside of the grid at any moment.
Both robots should reach the bottom row in grid.
https://leetcode.com/problems/cherry-pickup-ii/description/*/

#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> grid;
int dp[71][71][71][2];
int go(int c1, int c2, int row, int turn)
{
    int n = grid.size(), m = grid[0].size();
    if (row == n)
    {
        return 0;
    }
    if (dp[c1][c2][row][turn] != -1)
    {
        return dp[c1][c2][row][turn];
    }
    int ans = 0;
    if (!turn)
    {
        for (int i = -1; i <= 1; i++)
            if (c1 + i >= 0 && c1 + i < m)
            {
                ans = max(ans, ((c2 == c1) ? 0 : grid[row][c1]) + go(c1 + i, c2, row, 1 - turn));
            }
    }
    else
    {
        for (int i = -1; i <= 1; i++)
            if (c2 + i >= 0 && c2 + i < m)
            {
                ans = max(ans, grid[row][c2] + go(c1, c2 + i, row + 1, 1 - turn));
            }
    }
    return dp[c1][c2][row][turn] = ans;
}
class Solution
{
public:
    int cherryPickup(vector<vector<int>> &Grid)
    {
        grid = Grid;
        memset(dp, -1, sizeof(dp));
        return go(0, grid[0].size() - 1, 0, 0);
    }
};