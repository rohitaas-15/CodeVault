/*You are given a directed graph with n nodes and m edges. The nodes are numbered from 1 to n, and node i is assigned a cost 
. The cost of a walk on the graph is defined as the greatest common divisor of the costs of the vertices used in the walk. Formally, the cost of a walk 
 is given by 
. Note that 
's need not be distinct. Find the cost of the walk with minimum cost.

The walk might consist of single vertex.

Input

The first line contains two integers, n, and m.
The next line contains n space separated integers, 
 of which is equal to 
Each of the next m lines contain two integers, u, and v, denoting a directed edge from u to v.
Output

Print one integer containing the cost of the walk with minimum cost.
https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/practice-problems/algorithm/gcd-on-directed-graph-1122228a/*/

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

vector<vector<int>> adj, radj;
int vis[100001], dp[100001], cost[100001], colorCost[100001], color[100001];
vector<int> order;

int GCD(int a, int b)
{
    if (b > a)
        swap(a, b);
    if (b == 0)
        return a;
    return GCD(b, a % b);
}

void dfsTopo(int node)
{
    vis[node] = 1;
    for (auto i : adj[node])
    {
        if (!vis[i])
            dfsTopo(i);
    }
    order.push_back(node);
}
void dfsColor(int node, int col, int &gcd)
{
    gcd = GCD(gcd, cost[node]);
    vis[node] = 1;
    color[node] = col;

    for (auto i : radj[node])
    {
        if (!vis[i])
            dfsColor(i, col, gcd);
    }
}

int dfsGCD(int node)
{
    vis[node] = 1;

    int gcd = cost[node];
    for (auto i : adj[node])
    {
        if (!vis[i])
        {
            int subGCD = dfsGCD(i);

            gcd = min(gcd, GCD(subGCD, cost[node]));
        }
        else if (dp[i] != -1)
        {
            gcd = min(gcd, GCD(dp[i], cost[node]));
        }
    }

    return dp[node] = gcd;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    adj.clear(), adj.resize(n + 1);
    radj.clear(), radj.resize(n + 1);
    memset(vis, 0, sizeof(vis));
    memset(dp, -1, sizeof(dp));

    for (int i = 0; i < n; i++)
    {
        cin >> cost[i];
    }

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        radj[y - 1].push_back(x - 1);
    }

    // assigning cycle nodes same minimum GCD
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            dfsTopo(i);
        }
    }
    reverse(all(order));
    int col = 1;
    memset(vis, 0, sizeof(vis));
    for (auto i : order)
    {
        if (!vis[i])
        {
            int gcd = 0;
            dfsColor(i, col, gcd);
            colorCost[col] = gcd;
            col++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        cost[i] = colorCost[color[i]];
    }

    int mn = 1e9;
    memset(vis, 0, sizeof(vis));
    for (auto i : order)
    {
        if (!vis[i])
        {
            mn = min(mn, dfsGCD(i));
        }
    }
    print(mn);
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