/*A critical connection refers to an edge that, upon removal, will make it impossible for certain nodes to reach each other through any path. You are given an undirected connected graph with v vertices and e edges and each vertex distinct and ranges from 0 to v-1, and you have to find all critical connections in the graph. It is ensured that there is at least one such edge present.

Note: The answers may be presented in various potential orders. Each edge should be displayed in sorted order. For instance, if there's an edge between node 1 and node 2, it should be stored as (1,2) rather than (2,1). Additionally, it is expected that you store the edges in sorted order.

https://www.geeksforgeeks.org/problems/critical-connections/1*/
//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++
const int N = 1e4 + 2;
int disc[N], lowest[N], vis[N], tme = 0;
vector<vector<int>> bridges;

class Solution
{
public:
    vector<vector<int>> criticalConnections(int v, vector<int> adj[])
    {
        tme = 0, memset(disc, 0, sizeof(disc)), memset(lowest, 0, sizeof(lowest)), memset(vis, 0, sizeof(vis));
        bridges.clear();

        auto dfs = [&](auto rec, int node, int par) -> void
        {
            vis[node] = 1;
            disc[node] = lowest[node] = tme++;
            for (auto i : adj[node])
            {
                if (!vis[i])
                {
                    rec(rec, i, node);

                    if (lowest[i] > disc[node])
                    {
                        bridges.push_back({node, i});
                    }
                    lowest[node] = min(lowest[node], lowest[i]);
                }
                else if (i != par && vis[i] == 1)
                {
                    lowest[node] = min(lowest[node], disc[i]);
                }
            }
            vis[node] = 2;
        };

        dfs(dfs, 0, -1);

        for (auto &i : bridges)
        {
            if (i[0] > i[1])
                swap(i[0], i[1]);
        }
        sort(bridges.begin(), bridges.end());
        return bridges;
    }
};

//{ Driver Code Starts.

int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        int V, E;
        cin >> V >> E;
        vector<int> adj[V];
        for (int i = 0; i < E; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        Solution obj;
        vector<vector<int>> ans = obj.criticalConnections(V, adj);

        for (int i = 0; i < ans.size(); i++)
            cout << ans[i][0] << " " << ans[i][1] << endl;
    }
    return 0;
}
// } Driver Code Ends