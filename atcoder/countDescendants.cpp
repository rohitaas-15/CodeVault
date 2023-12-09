/*https://atcoder.jp/contests/abc202/tasks/abc202_e
We have a rooted tree with 
N vertices, numbered 
1,2,…,N.

Vertex 
1 is the root, and the parent of Vertex 
i(2≤i≤N) is Vertex 
P 
i
​
 .

You are given 
Q queries. In the 
i-th query 
(1≤i≤Q), given integers 
U 
i
​
  and 
D 
i
​
 , find the number of vertices 
u that satisfy all of the following conditions:

Vertex 
U 
i
​
  is in the shortest path from 
u to the root (including the endpoints).
There are exactly 
D 
i
​
  edges in the shortest path from 
u to the root.
Constraints
2≤N≤2×10 
5
 
1≤P 
i
​
 <i
1≤Q≤2×10 
5
 
1≤U 
i
​
 ≤N
0≤D 
i
​
 ≤N−1
All values in input are integers.*/


#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define endl "\n"
#define nl cout << endl
#define INF 1000000000000000000ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
int _p = 0;
template <typename Arg1>
void print(Arg1 &&arg1)
{
    cout << arg1 << " ";
    if (!_p)
        nl;
}
template <typename Arg1>
void print(vector<Arg1> x)
{
    _p = 1;
    for (Arg1 i : x)
        print(i);
    if (_p)
        nl;
    _p = 0;
}
template <typename Arg1, typename... Args>
void print(Arg1 &&arg1, Args &&...args)

{
    _p = 1;
    print(arg1);
    _p = 0;
    print(args...);
}
template <typename Arg1>
void assign(Arg1 arg1, Arg1 &arg2)
{
    arg2 = arg1;
}
template <typename Arg1, typename Arg2>
void assign(Arg1 arg1, vector<Arg2> &arg2)
{
    for (Arg2 &i : arg2)
        assign(arg1, i);
}
template <typename Arg1, typename Arg2, typename... Args>
void assign(Arg1 arg1, Arg2 &arg2, Args &...args)
{
    assign(arg1, arg2);
    assign(arg1, args...);
}

int N = 2e5 + 2, tme = 0;
vector<vector<int>> adj(N);
vector<int> tin(N), tout(N), flat(N), edges(N);

void dfs(int node, int par, int edgeCnt)
{

    edges[node] = edgeCnt, tin[node] = ++tme;
    for (auto i : adj[node])
        if (i != par)
            dfs(i, node, edgeCnt + 1);
    tout[node] = tme;
}

struct SegmentTree
{
    vector<map<int, int>> tree;
    SegmentTree(int n)
    {
        tree.resize(4 * n + 1);
    }

    void makeTree(int ss, int se, int ti, vector<int> &flat)
    {
        if (ss > se)
            return;
        if (ss == se)
        {
            tree[ti][flat[ss]] = 1;
            return;
        }

        int mid = (ss + se) >> 1;

        makeTree(ss, mid, ti * 2, flat), makeTree(mid + 1, se, ti * 2 + 1, flat);
        map<int, int> make;
        for (auto i : tree[ti * 2])
        {
            make[i.first] += i.second;
        }
        for (auto i : tree[ti * 2 + 1])
        {
            make[i.first] += i.second;
        }
        tree[ti] = make;
    }

    int query(int ss, int se, int qs, int qe, int edgeCnt, int ti)
    {
        if (qs > se || qe < ss)
            return 0;

        if (qs <= ss && qe >= se)
        {
            if (tree[ti].count(edgeCnt))
                return tree[ti][edgeCnt];
            return 0;
        }

        int mid = (ss + se) >> 1;

        return query(ss, mid, qs, qe, edgeCnt, ti * 2) + query(mid + 1, se, qs, qe, edgeCnt, ti * 2 + 1);
    }
};

void solve()
{

    int n;
    cin >> n;
    for (int i = 2; i <= n; i++)
    {
        int x;
        cin >> x;
        adj[i].push_back(x);
        adj[x].push_back(i);
    }

    dfs(1, 0, 0);

    for (int node = 1; node <= n; node++)
    {
        flat[tin[node]] = edges[node];
    }

    SegmentTree tree(n + 2);
    tree.makeTree(1, n, 1, flat);

    int q;
    cin >> q;
    while (q--)
    {
        int u, d;
        cin >> u >> d;

        int qs = tin[u], qe = tout[u];
        print(tree.query(1, n, qs, qe, d, 1ll));
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int _t = 1;
    // cin >> _t;
    while (_t--)
        solve();
}

// cin does not move the input cursor to the next line, use cin.ignore() to move it to the next line
