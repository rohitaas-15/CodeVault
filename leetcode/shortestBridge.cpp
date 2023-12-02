/*You are given an n x n binary matrix grid where 1 represents land and 0 represents water.

An island is a 4-directionally connected group of 1's not connected to any other 1's. There are exactly two islands in grid.

You may change 0's to 1's to connect the two islands to form one island.

Return the smallest number of 0's you must flip to connect the two islands.
https://leetcode.com/problems/shortest-bridge/description/
*/

#include <bits/stdc++.h>
using namespace std;

int vis[101][101];
int n;
void bfs(queue<pair<int, int>> q, vector<vector<int>> &dis, vector<vector<int>> &grid)
{
    while (!q.empty())
    {
        auto p = q.front();
        q.pop();

        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
                if (abs(i) != abs(j))
                {
                    int nx = p.first + i, ny = p.second + j;

                    if (nx < n && ny < n && min(nx, ny) >= 0 && grid[nx][ny] == 0 && !vis[nx][ny])
                    {
                        vis[nx][ny] = 1;
                        dis[nx][ny] = dis[p.first][p.second] + 1;
                        q.push({nx, ny});
                    }
                }
    }
}

void dfs(int x, int y, vector<vector<int>> &grid, int col)
{
    int ori = grid[x][y];

    grid[x][y] = col;
    vis[x][y] = 1;

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (abs(i) != abs(j))
            {
                int nx = x + i, ny = y + j;

                if (max(nx, ny) < n && min(nx, ny) >= 0 && grid[nx][ny] == ori && !vis[nx][ny])
                {
                    dfs(nx, ny, grid, col);
                }
            }
}

class Solution
{
public:
    int shortestBridge(vector<vector<int>> &grid)
    {
        n = grid.size();
        memset(vis, 0, sizeof(vis));

        int col = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1 && !vis[i][j])
                {
                    dfs(i, j, grid, col++);
                }
            }

        vector<vector<int>> dis(n + 1, vector<int>(n + 1, 1e8));
        auto dis2 = dis;
        queue<pair<int, int>> q1, q2;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    q1.push({i, j});
                    dis[i][j] = 0;
                }
                else if (grid[i][j] == 2)
                {
                    q2.push({i, j});
                    dis2[i][j] = 0;
                }
            }

        memset(vis, 0, sizeof(vis));
        bfs(q1, dis, grid);
        memset(vis, 0, sizeof(vis));
        bfs(q2, dis2, grid);

        long long ans = 1e8;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0)
                {
                    ans = min(ans, dis[i][j] + dis2[i][j] - 1ll);
                }
            }
        return ans;
    }
};