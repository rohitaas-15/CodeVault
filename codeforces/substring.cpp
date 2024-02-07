/*You are given a graph with 𝑛
 nodes and 𝑚
 directed edges. One lowercase letter is assigned to each node. We define a path's value as the number of the most frequently occurring letter. For example, if letters on a path are "abaca", then the value of that path is 3
. Your task is find a path whose value is the largest.

Input
The first line contains two positive integers 𝑛,𝑚
 (1≤𝑛,𝑚≤300000
), denoting that the graph has 𝑛
 nodes and 𝑚
 directed edges.

The second line contains a string 𝑠
 with only lowercase English letters. The 𝑖
-th character is the letter assigned to the 𝑖
-th node.

Then 𝑚
 lines follow. Each line contains two integers 𝑥,𝑦
 (1≤𝑥,𝑦≤𝑛
), describing a directed edge from 𝑥
 to 𝑦
. Note that 𝑥
 can be equal to 𝑦
 and there can be multiple edges between 𝑥
 and 𝑦
. Also the graph can be not connected.

Output
Output a single line with a single integer denoting the largest value. If the value can be arbitrarily large, output -1 instead.
https://codeforces.com/contest/919/problem/D*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
long long int _debug = 0, _nested = 0, _t = 1, INF = 1e18 + 2;
// macros-------------------------------------------------------------------------------
#define ll long long
#define int ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
#define endl "\n"
#define nl        \
    cout << endl; \
    if (_debug)   \
        cerr << endl;

// print
// helper-------------------------------------------------------------------------------
template <typename Primitive>
void print(Primitive &&P)
{
    cout << P << " ";
    if (_debug)
        cerr << P << " ";
    if (!_nested)
    {
        nl;
    }
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
    _nested = 1, print(C);
    _nested = 0, print(list...);
}

// scan
// helper-------------------------------------------------------------------------------
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
    scan(C), scan(list...);
}

// fill bulk
// data--------------------------------------------------------------------------------
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
    fill(Value, C), fill(Value, list...);
}

// policy based data
// structures---------------------------------------------------------------------------
template <typename T>
using indexed_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T1, typename T2>
using indexed_map =
    tree<T1, T2, less<T1>, rb_tree_tag, tree_order_statistics_node_update>;

// code----------------------------------------------------------------------------------
const int N = 3e5 + 2;
int vis[N], val[N], dp[N];
vector<int> adj[N];
bool isCycle(int node)
{
    vis[node] = 1;
    for (auto i : adj[node])
    {
        if (!vis[i])
        {
            bool yes = isCycle(i);
            if (yes)
                return yes;
        }
        else if (vis[i] == 1)
        {
            return true;
        }
    }
    vis[node] = 2;
    return false;
}

void dfs(int node, int ch)
{
    vis[node] = 1;
    int cnt = 0;

    for (auto i : adj[node])
    {
        if (!vis[i])
        {
            dfs(i, ch);
        }
        cnt = max(cnt, dp[i]);
    }
    cnt += (val[node] == ch);
    dp[node] = cnt;
}
void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        char c;
        cin >> c;
        val[i] = c - 'a';
    }
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
    }

    for (int node = 1; node <= n; node++)
    {
        if (!vis[node])
        {
            if (isCycle(node))
            {
                print(-1);
                return;
            }
        }
    }

    int mx = 0;
    for (int c = 0; c < 26; c++)
    {
        memset(vis, 0, sizeof(vis));
        memset(dp, 0, sizeof(dp));
        for (int node = 1; node <= n; node++)
        {
            if (!vis[node])
            {
                dfs(node, c);
            }
            mx = max(mx, dp[node]);
        }
    }
    print(mx);
}

signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    // cin >> _t;
    for (int tc = 1; tc <= _t; tc++)
    {
        // cout << "Case " << tc << ":"
        //      << " ";
        solve();
    }
}

// cin does not move the input cursor to the next line, use cin.ignore() to
// move it to the next line use an array instead of an int whenever possible,
// for coding competitions