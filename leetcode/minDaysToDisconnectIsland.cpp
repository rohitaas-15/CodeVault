
#include <bits/stdc++.h>
using namespace std;

int n, m;
int vis[31][31], disc[31][31], low[31][31], tme = 1;
int ans = 1e9;
int cntOnes;
set<int> dfs(int x, int y, int parx, int pary, vector<vector<int>> &grid) // returns the vector of backedges that have lowest time < disc[node]
{
    cntOnes++;
    disc[x][y] = low[x][y] = tme++;
    vis[x][y] = 1;

    set<int> curBackedges;
    int child = 0;

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (abs(i) != abs(j))
            {
                int nx = x + i, ny = y + j;

                if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1)
                {
                    if (!vis[nx][ny])
                    {
                        set<int> subEdges = dfs(nx, ny, x, y, grid), usefulSubEdges;
                        child++;
                        low[x][y] = min(low[x][y], low[nx][ny]);

                        usefulSubEdges.insert(disc[x][y]); /*to check if removing all backedge nodes with cur node
                                                            will result in an articulation point*/
                        for (auto k : subEdges)
                        {
                            if (k < disc[x][y])
                            {
                                curBackedges.insert(k);
                                usefulSubEdges.insert(k);
                            }
                        }

                        if (parx != -1) // not a root node
                        {
                            ans = min(ans, (int)usefulSubEdges.size());
                        }
                    }
                    else if ((nx != parx || ny != pary) && vis[nx][ny] == 1)
                    {
                        low[x][y] = min(low[x][y], disc[nx][ny]);
                        curBackedges.insert(disc[nx][ny]);
                    }
                }
            }

    if (child > 1 && parx == -1) // root node
    {
        ans = 1;
    }
    vis[x][y] = 2;
    return curBackedges;
}

class Solution
{
public:
    int minDays(vector<vector<int>> &grid)
    {
        n = grid.size(), m = grid[0].size(), cntOnes = 0;
        ans = 1e9, tme = 1;
        memset(vis, 0, sizeof(vis));

        int cntIslands = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (!vis[i][j] && grid[i][j] == 1)
                {
                    dfs(i, j, -1, -1, grid);
                    cntIslands++;
                }
        if (cntIslands > 1)
            return 0;
        return (ans == 1e9) ? cntOnes : ans;
    }
};