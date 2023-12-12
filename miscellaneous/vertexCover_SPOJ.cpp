/*You are given an unweighted, undirected tree. Write a program to find a vertex set of minimum size in this tree such that each edge has as least one of its end-points in that set.

Input
The first line of the input file contains one integer N --- number of nodes in the tree (0 < N <= 100000). Next N-1 lines contain N-1 edges of that tree --- Each line contains a pair (u, v) means there is an edge between node u and node v (1 <= u,v <= N).

Output
Print number of nodes in the satisfied vertex set on one line.

https://www.spoj.com/problems/PT07X/*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
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

const int N = 1e5 + 2;
vector<int> adj[N];
vector<vector<int>> dp(N, {0, 1}); // node i taken(dp[i][1]), not taken(dp[i][0])

void dfs(int node, int par)
{
    for (auto i : adj[node])
        if (i != par)
        {
            dfs(i, node);
            dp[node][0] += dp[i][1];
            dp[node][1] += min(dp[i][0], dp[i][1]);
        }
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        scan(x, y);
        adj[x].push_back(y), adj[y].push_back(x);
    }

    dfs(1, 0);
    print(min(dp[1][0], dp[1][1]));
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