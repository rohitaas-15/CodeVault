/*You are given an integer matrix isWater of size m x n that represents a map of land and water cells.

If isWater[i][j] == 0, cell (i, j) is a land cell.
If isWater[i][j] == 1, cell (i, j) is a water cell.
You must assign each cell a height in a way that follows these rules:

The height of each cell must be non-negative.
If the cell is a water cell, its height must be 0.
Any two adjacent cells must have an absolute height difference of at most 1. A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
Find an assignment of heights such that the maximum height in the matrix is maximized.

Return an integer matrix height of size m x n where height[i][j] is cell (i, j)'s height. If there are multiple solutions, return any of them.
https://leetcode.com/problems/map-of-highest-peak/
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> highestPeak(vector<vector<int>> &isWater)
    {
        int n = isWater.size(), m = isWater[0].size();

        vector<vector<int>> dis(n, vector<int>(m, 1e9));

        queue<pair<int, int>> q;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                if (isWater[i][j])
                {
                    q.push({i, j});
                    dis[i][j] = 0;
                }
            }

        while (!q.empty())
        {
            auto p = q.front();
            q.pop();
            int x = p.first, y = p.second;

            for (int i = -1; i <= 1; i++)
                for (int j = -1; j <= 1; j++)
                    if (abs(i) != abs(j))
                    {
                        int nx = x + i, ny = y + j;

                        if (nx >= 0 && nx < n && ny >= 0 && ny < m && dis[nx][ny] > dis[x][y] + 1)
                        {
                            dis[nx][ny] = dis[x][y] + 1;
                            q.push({nx, ny});
                        }
                    }
        }

        return dis;
    }
};