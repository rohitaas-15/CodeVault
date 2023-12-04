/*Given an undirected connected graph with V vertices and adjacency list adj. You are required to find all the vertices removing which (and edges through it) disconnects the graph into 2 or more components.
Note: Indexing is zero-based i.e nodes numbering from (0 to V-1). There might be loops present in the graph.
https://www.geeksforgeeks.org/problems/articulation-point-1/1*/

//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

vector<int> vis, disc, low;
int tme;
set<int> arti_points;
vector<vector<int>> gr;

void dfs(int cur, int par)
{
    disc[cur] = low[cur] = tme++;
    vis[cur] = 1;
    int child = 0;

    for (auto x : gr[cur])
    {
        if (!vis[x])
        {
            dfs(x, cur);
            child++;

            low[cur] = min(low[cur], low[x]);

            if (par != -1 && low[x] >= disc[cur])
            {
                arti_points.insert(cur);
            }
        }
        else if (x != par && vis[x] == 1)
        {
            low[cur] = min(low[cur], disc[x]);
        }
    }

    if (par == -1 && child > 1)
    {
        arti_points.insert(cur);
    }
}

class Solution
{
public:
    vector<int> articulationPoints(int V, vector<int> adj[])
    {
        gr.clear();
        gr.resize(10001);
        for (int i = 0; i < V; i++)
        {
            for (auto j : adj[i])
            {
                gr[i].push_back(j);
            }
        }
        arti_points.clear();
        tme = 1;
        vis.clear();
        vis.resize(10001, 0);
        disc.clear();
        disc.resize(10001);
        low.clear();
        low.resize(10001);

        vector<int> ans;
        dfs(0, -1);
        for (auto i : arti_points)
        {
            ans.push_back(i);
        }
        if (arti_points.empty())
        {
            ans.push_back(-1);
        }
        return ans;
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
        vector<int> ans = obj.articulationPoints(V, adj);
        for (auto i : ans)
            cout << i << " ";
        cout << "\n";
    }
    return 0;
}
// } Driver Code Ends