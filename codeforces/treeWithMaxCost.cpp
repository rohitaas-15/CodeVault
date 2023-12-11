/*You are given a tree consisting exactly of 𝑛
 vertices. Tree is a connected undirected graph with 𝑛−1
 edges. Each vertex 𝑣
 of this tree has a value 𝑎𝑣
 assigned to it.

Let 𝑑𝑖𝑠𝑡(𝑥,𝑦)
 be the distance between the vertices 𝑥
 and 𝑦
. The distance between the vertices is the number of edges on the simple path between them.

Let's define the cost of the tree as the following value: firstly, let's fix some vertex of the tree. Let it be 𝑣
. Then the cost of the tree is ∑𝑖=1𝑛𝑑𝑖𝑠𝑡(𝑖,𝑣)⋅𝑎𝑖
.

Your task is to calculate the maximum possible cost of the tree if you can choose 𝑣
 arbitrarily.

Input
The first line contains one integer 𝑛
, the number of vertices in the tree (1≤𝑛≤2⋅105
).

The second line of the input contains 𝑛
 integers 𝑎1,𝑎2,…,𝑎𝑛
 (1≤𝑎𝑖≤2⋅105
), where 𝑎𝑖
 is the value of the vertex 𝑖
.

Each of the next 𝑛−1
 lines describes an edge of the tree. Edge 𝑖
 is denoted by two integers 𝑢𝑖
 and 𝑣𝑖
, the labels of vertices it connects (1≤𝑢𝑖,𝑣𝑖≤𝑛
, 𝑢𝑖≠𝑣𝑖
).

It is guaranteed that the given edges form a tree.

Output
Print one integer — the maximum possible cost of the tree if you can choose any vertex as 𝑣
.
https://codeforces.com/problemset/problem/1092/F*/



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

const int N = 2e5 + 2;
vector<int> adj[N], dp(N), cost(N), sum(N);
int ans = 0;

void dfs(int node, int par)
{
    for (auto i : adj[node])
        if (i != par)
        {
            dfs(i, node);
            sum[node] += sum[i];
            dp[node] += (dp[i] + sum[i]);
        }
}

void reRoot(int node, int par)
{
    ans = max(ans, dp[node]);
    for (auto i : adj[node])
        if (i != par)
        {
            dp[node] -= (dp[i] + sum[i]), sum[node] -= sum[i];
            dp[i] += (dp[node] + sum[node]), sum[i] += sum[node];
            reRoot(i, node);
            sum[i] -= sum[node], dp[i] -= (dp[node] + sum[node]);
            sum[node] += sum[i], dp[node] += (dp[i] + sum[i]);
        }
}
void solve()
{
    fill(0ll, dp, sum, cost);

    int n;
    cin >> n;
    rep(i, 0, n)
    {
        cin >> cost[i + 1];
        sum[i + 1] = cost[i + 1];
    }

    rep(i, 0, n - 1)
    {
        int x, y;
        scan(x, y);
        adj[x].push_back(y), adj[y].push_back(x);
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