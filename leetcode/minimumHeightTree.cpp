/*A tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.

Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges where edges[i] = [ai, bi] indicates that there is an undirected edge between the two nodes ai and bi in the tree, you can choose any node of the tree as the root. When you select a node x as the root, the result tree has height h. Among all possible rooted trees, those with minimum height (i.e. min(h))  are called minimum height trees (MHTs).

Return a list of all MHTs' root labels. You can return the answer in any order.

The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.

https://leetcode.com/problems/minimum-height-trees/description/
*/

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
int doBfs(int node, vector<int> &dis, vector<int> &par)
{
    int n = par.size() - 1;
    queue<int> q;
    q.push(node);
    dis[node] = 0, par[node] = node;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (auto i : adj[node])
        {
            if (i != par[node])
            {
                dis[i] = dis[node] + 1;
                par[i] = node;
                q.push(i);
            }
        }
    }

    int mxIndex, mx = -1;

    for (int i = 0; i < n; i++)
    {
        if (dis[i] > mx)
        {
            mx = dis[i];
            mxIndex = i;
        }
    }
    return mxIndex;
}
class Solution
{
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
    {
        adj.clear(), adj.resize(n + 1);

        for (auto i : edges)
        {
            adj[i[0]].push_back(i[1]);
            adj[i[1]].push_back(i[0]);
        }

        vector<int> dis(n + 1, 1e9), par(n + 1, -1);

        int mxIndex = doBfs(0, dis, par);

        dis.clear(), dis.resize(n + 1, 1e9), par.clear(), par.resize(n + 1, -1);

        mxIndex = doBfs(mxIndex, dis, par);

        vector<int> path;
        int temp = mxIndex;

        while (par[temp] != temp)
        {
            path.push_back(temp);
            temp = par[temp];
        }

        path.push_back(temp);
        vector<int> ans;

        if (path.size() % 2)
        {
            ans.push_back(path[(path.size() - 1) / 2]);
            return ans;
        }
        else
        {
            ans.push_back(path[(path.size() - 1) / 2]);
            ans.push_back(path[(path.size() - 1) / 2 + 1]);
            return ans;
        }
    }
};