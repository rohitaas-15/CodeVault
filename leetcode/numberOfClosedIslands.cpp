/*Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally connected group of 0s and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.

Return the number of closed islands.

https://leetcode.com/problems/number-of-closed-islands/description/*/
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> vis;
int n, m;
bool checkIfPartOfClosedIsland(int x, int y, vector<vector<int>> &grid)
{
    vis[x][y] = 1;

    bool closedIsland = true;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (abs(i) != abs(j))
            {
                int nx = x + i, ny = y + j;
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 0 && !vis[nx][ny])
                {
                    bool closed = checkIfPartOfClosedIsland(nx, ny, grid);
                    if (!closed)
                    {
                        closedIsland = false;
                    }
                }
            }
        }
    }
    closedIsland = closedIsland && (x > 0 && x < n - 1 && y > 0 && y < m - 1);
    return closedIsland;
}
class Solution
{
public:
    int closedIsland(vector<vector<int>> &grid)
    {
        n = grid.size(), m = grid[0].size();
        vis.clear(), vis.resize(n + 1, vector<int>(m + 1, 0));
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (!vis[i][j] && grid[i][j] == 0)
                {
                    ans += checkIfPartOfClosedIsland(i, j, grid);
                }
            }
        }
        return ans;
    }
};