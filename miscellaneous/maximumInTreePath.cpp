/*You are given an undirected Tree with n nodes rooted at node 1 , every ith node is assigned a value denoted by ai .

The tree is given as an array of edges where edges[i] = [ui, vi] is a bidirectional edge between node ui and node vi , and also you are given an array of queries where queries[i] = [ui, vi ] , you have to calculate the maximum value of the node present  on a simple path from node ui to vi for each query.

Return an array containing the answer of each query respectively.
3≤ n ≤10^5

2<= edges.length <= n-1

1≤ queries.length ≤10^5

1≤ ai ≤10^9

1<= ui, vi <=n
*/


#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define nl cout << endl
//print helper
int _p = 0; template <typename Arg1> void print(Arg1 &&arg1) { cout << arg1 << " "; if (!_p) nl; }
template <typename Arg1> void print(vector<Arg1> &arg1) { _p = 1; for (Arg1 &i : arg1) print(i); if (_p) nl; _p = 0; }
template <typename Arg1, typename... Args> void print(Arg1 &&arg1, Args &&...args) { _p = 1; print(arg1); _p = 0; print(args...); }
//scan helper
template <typename Arg1> void scan(Arg1 &arg1) { cin>>arg1; }
template <typename Arg1>void scan(vector<Arg1> &arg1) { for (Arg1 &i : arg1) scan(i);}
template <typename Arg1, typename... Args> void scan(Arg1 &arg1, Args &...args) { scan(arg1); scan(args...); }
//fill bulk data
template <typename Arg1> void fill(Arg1 arg1, Arg1 &arg2) { arg2 = arg1; }
template <typename Arg1, typename Arg2>void fill(Arg1 arg1, vector<Arg2> &arg2) { for (Arg2 &i : arg2) fill(arg1, i); }
template <typename Arg1, typename Arg2, typename... Args>void fill(Arg1 arg1, Arg2 &arg2, Args &...args) { fill(arg1, arg2); fill(arg1, args...); }

int N = 1e5 + 2, M = 22;
vector<vector<int>> adj(N), Par(N, vector<int>(M)), Max(N, vector<int>(M));
vector<int> depth(N);

void dfs(int node, int parent, int dep, vector<int> &a)
{
    if (node == 1)
        Max[node][0] = a[node - 1];
    else
        Max[node][0] = max(a[node - 1], a[parent - 1]);
    depth[node] = dep, Par[node][0] = parent;

    for (int j = 1; j < M; j++)
    {
        Par[node][j] = Par[Par[node][j - 1]][j - 1];
        Max[node][j] = max(Max[node][j - 1], Max[Par[node][j - 1]][j - 1]);
    }
    for (auto i : adj[node])
        if (i != parent)
            dfs(i, node, dep + 1, a);
}

int findMax(int x, int y, vector<int> &a)
{
    int mx = max(a[x - 1], a[y - 1]);
    if (depth[x] < depth[y])
        swap(x, y);

    int diff = depth[x] - depth[y];
    for (int j = 0; j < M; j++)
    {
        if (diff & (1 << j))
        {
            mx = max(mx, Max[x][j]);
            x = Par[x][j];
        }
    }

    if (x == y)
        return mx;

    for (int j = M - 1; j >= 0; j--)
    {
        if (Par[x][j] != Par[y][j])
        {
            mx = max({mx, Max[x][j], Max[y][j]});
            x = Par[x][j], y = Par[y][j];
        }
    }
    return max(mx, a[Par[x][0] - 1]);
}

vector<int> maximumPath(int n, vector<int> a, vector<vector<int>> edges, vector<vector<int>> queries)
{
    fill(0, Par, Max, depth);
    adj.clear(), adj.resize(n + 1);
    for (auto i : edges)
    {
        adj[i[0]].push_back(i[1]);
        adj[i[1]].push_back(i[0]);
    }

    dfs(1, 0, 0, a);
    vector<int> ans;

    for (auto i : queries)
    {
        ans.push_back(findMax(i[0], i[1], a));
    }
    return ans;
}