/*You are given a weighted tree consisting of 𝑛
 vertices. Recall that a tree is a connected graph without cycles. Vertices 𝑢𝑖
 and 𝑣𝑖
 are connected by an edge with weight 𝑤𝑖
.

You are given 𝑚
 queries. The 𝑖
-th query is given as an integer 𝑞𝑖
. In this query you need to calculate the number of pairs of vertices (𝑢,𝑣)
 (𝑢<𝑣
) such that the maximum weight of an edge on a simple path between 𝑢
 and 𝑣
 doesn't exceed 𝑞𝑖
.

Input
The first line of the input contains two integers 𝑛
 and 𝑚
 (1≤𝑛,𝑚≤2⋅105
) — the number of vertices in the tree and the number of queries.

Each of the next 𝑛−1
 lines describes an edge of the tree. Edge 𝑖
 is denoted by three integers 𝑢𝑖
, 𝑣𝑖
 and 𝑤𝑖
 — the labels of vertices it connects (1≤𝑢𝑖,𝑣𝑖≤𝑛
, 𝑢𝑖≠𝑣𝑖
) and the weight of the edge (1≤𝑤𝑖≤2⋅105
). It is guaranteed that the given edges form a tree.

The last line of the input contains 𝑚
 integers 𝑞1,𝑞2,…,𝑞𝑚
 (1≤𝑞𝑖≤2⋅105
), where 𝑞𝑖
 is the maximum weight of an edge in the 𝑖
-th query.

Output
Print 𝑚
 integers — the answers to the queries. The 𝑖
-th value should be equal to the number of pairs of vertices (𝑢,𝑣)
 (𝑢<𝑣
) such that the maximum weight of an edge on a simple path between 𝑢
 and 𝑣
 doesn't exceed 𝑞𝑖
.
https://codeforces.com/contest/1213/problem/G*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define endl "\n"
#define nl cout << endl
#define pii pair<int, int>
#define vi vector<int>
#define vvi vector<vi>
#define pb push_back
#define F first
#define S second
#define INF 1000000000000000000ll
#define sz(x) x.size()
#define vpii vector<pii>
#define vvpii vector<vector<pii>>
#define rev(x) reverse(x.begin(), x.end())
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
template <typename Arg1>
void print(Arg1 &&arg1);
template <typename Arg1>
void print(vector<Arg1> x);
template <typename Arg1, typename... Args>
void print(Arg1 &&arg1, Args &&...args);

struct DSU
{

    vector<int> par, rank;
    DSU(int n)
    {
        par.clear(), par.resize(n, -1);
        rank.clear(), rank.resize(n, 1);
    }

    int find(int x)
    {
        if (par[x] == -1)
            return x;
        return par[x] = find(par[x]);
    }

    void unite(int x, int y)
    {
        int s1 = find(x), s2 = find(y);

        if (s1 == s2)
            return;
        if (rank[s2] > rank[s1])
            swap(s1, s2);

        rank[s1] += rank[s2], par[s2] = s1;
    }
};

void solve()
{

    int n, q;
    cin >> n >> q;
    vector<vector<int>> edges;
    for (int i = 0; i < n - 1; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        edges.push_back({z, x, y});
    }

    sort(edges.begin(), edges.end());

    vector<pair<int, int>> dp;
    dp.push_back({0, 0});

    DSU d(n + 1);

    for (int i = 0; i < n - 1; i++)
    {
        int prevAns = dp[i].second;

        int s1 = d.find(edges[i][1]), s2 = d.find(edges[i][2]);

        if (s1 != s2)
        {
            dp.push_back({edges[i][0], prevAns + d.rank[s1] * d.rank[s2]});
            d.unite(edges[i][1], edges[i][2]);
        }
    }

    vector<int> ans;
    while (q--)
    {
        int x;
        cin >> x;
        auto it = upper_bound(dp.begin(), dp.end(), make_pair(x, INF));
        it--;
        ans.push_back((*(it)).second);
    }
    print(ans);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}

// Print helper
int _level = 0;
template <typename Arg1>
void print(Arg1 &&arg1)
{
    cout << arg1 << " ";
    if (!_level)
        nl;
}
template <typename Arg1>
void print(vector<Arg1> x)
{
    _level = 1;
    for (Arg1 i : x)
        print(i);
    if (_level)
        nl;
    _level = 0;
}
template <typename Arg1, typename... Args>
void print(Arg1 &&arg1, Args &&...args)
{
    cout << arg1 << " ";
    print(args...);
}
// cin does not move the input cursor to the next line, use cin.ignore() to move it to the next line
