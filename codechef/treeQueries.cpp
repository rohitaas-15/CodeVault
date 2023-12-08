/*You are given a tree with
N vertices rooted at vertex
1, where
ith vertex having a value
You are also given Q queries where each query gives you a node u and a value
val. You need to add val to each node v such that v is in the subtree of
###Input:

First line will contain N and
Q, number of nodes and queries respectively.
Second line contains N space separated integers, the initial value of each node.
Next N−1 lines contain two integers u and v representing an edge between nodes u and v.
The next Q lines contain two integers each u and val as explained in the problem statement.
###Output: Output a single like containing
N space separated integers where the ith integer denotes the value of the ith node after all queries have been executed.
https://www.codechef.com/problems/TREEUGH*/

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

int N = 5e5 + 2;

vector<vector<int>> adj(N);
vector<int> tin(N), tout(N), flat(N), val(N);
int tme = 0;

void timeDfs(int node, int par)
{
    tin[node] = ++tme;

    for (auto i : adj[node])
    {
        if (i != par)
            timeDfs(i, node);
    }
    tout[node] = tme;
}

void solve()
{
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
    {
        cin >> val[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    timeDfs(1, 0);

    for (int node = 1; node <= n; node++)
    {
        flat[tin[node]] = val[node];
    }

    vector<int> freq(n + 2, 0);
    while (q--)
    {
        int v, val;
        cin >> v >> val;
        int start = tin[v], end = tout[v] + 1;
        freq[start] += val, freq[end] -= val;
    }

    for (int i = 1; i <= n; i++)
    {
        freq[i] = freq[i - 1] + freq[i];
    }

    for (int node = 1; node <= n; node++)
    {
        cout << flat[tin[node]] + freq[tin[node]] << " ";
    }
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
