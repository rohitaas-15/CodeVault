/*There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.

A critical connection is a connection that, if removed, will make some servers unable to reach some other server.

Return all critical connections in the network in any order.
https://leetcode.com/problems/critical-connections-in-a-network/description/*/

#include <bits/stdc++.h>
using namespace std;

int disc[100001], low[100001], vis[100001], tme = 1;
vector<vector<int>> bridges, adj;
vector<int> arti_points;

void dfs(int cur, int par)
{
    disc[cur] = low[cur] = tme++;
    vis[cur] = 1;
    int child = 0;

    for (auto x : adj[cur])
    {
        if (!vis[x])
        {
            dfs(x, cur);
            child++;

            // bridges

            low[cur] = min(low[cur], low[x]);

            if (low[x] > disc[cur])
            {
                bridges.push_back({cur, x});
            }

            // articulation points

            if (par != -1 && low[x] >= disc[cur])
            {
                arti_points.push_back(cur);
            }
        }
        else if (x != par && vis[x] == 1) // backedge
        {
            low[cur] = min(low[cur], disc[x]);
        }
    }

    if (par == -1 && child > 1) // for root node
    {
        arti_points.push_back(cur);
    }

    vis[cur] = 2;
    return;
}

class Solution
{
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>> &connections)
    {

        adj.clear(), adj.resize(n + 1), bridges.clear();
        memset(vis, 0, sizeof(vis));

        for (auto i : connections)
        {
            adj[i[0]].push_back(i[1]);
            adj[i[1]].push_back(i[0]);
        }

        dfs(0, -1);
        return bridges;
    }
};