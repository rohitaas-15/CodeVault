/*You are given a tree consisting of n nodes.
A matching is a set of edges where each node is an endpoint of at most one edge. What is the maximum number of edges in a matching?
Input
The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,\ldots,n.
Then there are n-1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.
Output
Print one integer: the maximum number of pairs.
Constraints

1 \le n \le 2 \cdot 10^5
1 \le a,b \le n
https://cses.fi/problemset/task/1130/
*/
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
vector<int> adj[N];
vector<vector<int>> dp(N, vector<int>(2, 0));

void dfs(int node, int par)
{
    int taken = 0, nTaken = 0;

    // first calculate the answer if no edge connected to node is taken
    for (auto i : adj[node])
    {
        if (i != par)
        {
            dfs(i, node);
            nTaken += max(dp[i][1], dp[i][0]);
        }
    }

    // then calculate the answer if at max 1 edge connecting to node is taken
    for (auto i : adj[node])
    {
        if (i != par)
        {
            taken = max(taken, (nTaken - max(dp[i][0], dp[i][1])) + (1 + dp[i][0]));
        }
    }

    dp[node] = {nTaken, taken};
}

void solve()
{
    int n;
    cin >> n;

    for (int i = 2; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1, 0);
    print(max(dp[1][0], dp[1][1]));
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