// https://leetcode.com/problems/number-of-closed-islands/submissions/
/* Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally connected group of 0s and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.

Return the number of closed islands.*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
int vis[101][101];
int dp[101][101];

bool isClosed(vector<vector<int>> &grid, int x, int y)
{
    vis[x][y] = 1;
    bool ans = (x != 0 && x != n - 1) && (y != 0 && y != m - 1);

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (abs(i) != abs(j))
            {
                int nx = x + i, ny = y + j;
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 0)
                {
                    if (!vis[nx][ny])
                    {
                        ans = ans && isClosed(grid, nx, ny);
                    }
                    else if (dp[nx][ny] != -1)
                        ans = ans && dp[nx][ny];
                }
            }
    return dp[x][y] = ans;
}

class Solution
{
public:
    int closedIsland(vector<vector<int>> &grid)
    {

        memset(vis, 0, sizeof(vis));
        memset(dp, -1, sizeof(dp));
        n = grid.size(), m = grid[0].size();
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (!vis[i][j] && grid[i][j] == 0 && isClosed(grid, i, j))
                {
                    cnt++;
                }
            }
        }
        return cnt;
    }
};