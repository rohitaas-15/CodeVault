

/*You are given a tree consisting of 𝑛
 vertices. A tree is a connected undirected graph with 𝑛−1
 edges. Each vertex 𝑣
 of this tree has a color assigned to it (𝑎𝑣=1
 if the vertex 𝑣
 is white and 0
 if the vertex 𝑣
 is black).

You have to solve the following problem for each vertex 𝑣
: what is the maximum difference between the number of white and the number of black vertices you can obtain if you choose some subtree of the given tree that contains the vertex 𝑣
? The subtree of the tree is the connected subgraph of the given tree. More formally, if you choose the subtree that contains 𝑐𝑛𝑡𝑤
 white vertices and 𝑐𝑛𝑡𝑏
 black vertices, you have to maximize 𝑐𝑛𝑡𝑤−𝑐𝑛𝑡𝑏
.

Input
The first line of the input contains one integer 𝑛
 (2≤𝑛≤2⋅105
) — the number of vertices in the tree.

The second line of the input contains 𝑛
 integers 𝑎1,𝑎2,…,𝑎𝑛
 (0≤𝑎𝑖≤1
), where 𝑎𝑖
 is the color of the 𝑖
-th vertex.

Each of the next 𝑛−1
 lines describes an edge of the tree. Edge 𝑖
 is denoted by two integers 𝑢𝑖
 and 𝑣𝑖
, the labels of vertices it connects (1≤𝑢𝑖,𝑣𝑖≤𝑛,𝑢𝑖≠𝑣𝑖
).

It is guaranteed that the given edges form a tree.
https://codeforces.com/problemset/problem/1324/F
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
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

int N = 2e5 + 2;
vector<vector<int>> adj(N);
vector<int> dp(N, 0), // max prefix answer of subtree of i
    color, ans;

void dfs(int node, int par)
{
    int ans = 0;
    for (auto i : adj[node])
    {
        if (i != par)
        {
            dfs(i, node);
            if (dp[i] > 0)
            {
                ans += dp[i];
            }
        }
    }

    if (color[node - 1] == 1)
        ans++;
    else
        ans--;

    dp[node] = ans;
}

void reRoot(int node, int par)
{
    ans[node - 1] = dp[node];

    for (auto i : adj[node])
        if (i != par)
        {
            if (dp[i] > 0)
                dp[node] -= dp[i];
            if (dp[node] > 0)
                dp[i] += dp[node];
            reRoot(i, node);

            if (dp[node] > 0)
            {
                dp[i] -= dp[node];
            }

            if (dp[i] > 0)
            {
                dp[node] += dp[i];
            }
        }
}
void solve()
{
    int n;
    cin >> n;
    color.clear(), color.resize(n), ans.clear(), ans.resize(n);
    scan(color);

    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        scan(x, y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1, 0), reRoot(1, 0);
    print(ans);
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