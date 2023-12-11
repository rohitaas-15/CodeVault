/*A tree is a connected graph that doesn't contain any cycles.

The distance between two vertices of a tree is the length (in edges) of the shortest path between these vertices.

You are given a tree with n vertices and a positive number k. Find the number of distinct pairs of the vertices which have a distance of exactly k between them. Note that pairs (v, u) and (u, v) are considered to be the same pair.

Input
The first line contains two integers n and k (1 ≤ n ≤ 50000, 1 ≤ k ≤ 500) — the number of vertices and the required distance between the vertices.

Next n - 1 lines describe the edges as "ai bi" (without the quotes) (1 ≤ ai, bi ≤ n, ai ≠ bi), where ai and bi are the vertices connected by the i-th edge. All given edges are different.

Output
Print a single integer — the number of distinct pairs of the tree's vertices which have a distance of exactly k between them.

Please do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.*/
// https://codeforces.com/problemset/problem/161/D

#include <bits/stdc++.h>
using namespace std;
#define ll unsigned long long
#define int ll
#define INF 1000000000000000000ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
#define endl "\n"
#define nl cout << endl

//-------------------------------------------------------------------------------

// print helper
int _nested = 0;
template <typename Primitive>
void print(Primitive &&P)
{
    cout << P << " ";
    if (!_nested)
        nl;
}
template <typename Complex>
void print(vector<Complex> &Vector)
{
    _nested = 1;
    for (Complex &C : Vector)
        print(C);
    nl;
    _nested = 0;
}
template <typename Complex, typename... ComplexObjects>
void print(Complex &&C, ComplexObjects &&...list)
{
    _nested = 1;
    print(C);
    _nested = 0;
    print(list...);
}

// scan helper
template <typename Primitive>
void scan(Primitive &P)
{
    cin >> P;
}
template <typename Complex>
void scan(vector<Complex> &Vector)
{
    for (Complex &C : Vector)
        scan(C);
}
template <typename Complex, typename... ComplexObjects>
void scan(Complex &C, ComplexObjects &...list)
{
    scan(C);
    scan(list...);
}

// fill bulk data
template <typename Primitive>
void fill(Primitive Value, Primitive &P)
{
    P = Value;
}
template <typename Primitive, typename Complex>
void fill(Primitive Value, vector<Complex> &Vector)
{
    for (Complex &C : Vector)
        fill(Value, C);
}
template <typename Primitive, typename Complex, typename... ComplexObjects>
void fill(Primitive Value, Complex &C, ComplexObjects &...list)
{
    fill(Value, C);
    fill(Value, list...);
}

//-------------------------------------------------------------------------------

const int N = 5e4 + 2, K = 502;
vector<int> adj[N];
vector<vector<int>> dp(N, vector<int>(K)); //distance of exactly j from i in subtree of i
int ans = 0;

void dfs(int node, int par)
{
    dp[node][0] = 1;

    for (auto i : adj[node])
        if (i != par)
        {
            dfs(i, node);
            for (int j = 1; j < K; j++)
            {
                dp[node][j] += dp[i][j - 1];
            }
        }
}

void reRoot(int node, int par, int k)
{
    ans += dp[node][k];

    for (auto i : adj[node])
    {
        if (par != i)
        {
            for (int j = 1; j < K; j++)
            {
                dp[node][j] -= dp[i][j - 1];
            }

            for (int j = 1; j < K; j++)
            {
                dp[i][j] += dp[node][j - 1];
            }

            reRoot(i, node, k);

            for (int j = 1; j < K; j++)
            {
                dp[i][j] -= dp[node][j - 1];
            }

            for (int j = 1; j < K; j++)
            {
                dp[node][j] += dp[i][j - 1];
            }
        }
    }
}

void solve()
{

    fill((ll)0, dp);
    int n, k;
    scan(n, k);
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        scan(x, y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1, 0), reRoot(1, 0, k);
    print(ans/2);
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