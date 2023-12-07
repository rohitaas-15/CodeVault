/*Time limit: 1.00 s
Memory limit: 512 MB



You are given a rooted tree consisting of n nodes. The nodes are numbered 1,2,\ldots,n, and node 1 is the root. Each node has a value.
Your task is to process following types of queries:

change the value of node s to x
calculate the sum of values in the subtree of node s

Input
The first input line contains two integers n and q: the number of nodes and queries. The nodes are numbered 1,2,\ldots,n.
The next line has n integers v_1,v_2,\ldots,v_n: the value of each node.
Then there are n-1 lines describing the edges. Each line contans two integers a and b: there is an edge between nodes a and b.
Finally, there are q lines describing the queries. Each query is either of the form "1 s x" or "2 s".
https://cses.fi/problemset/task/1137/*/

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

int N = 2e5 + 2;

vector<vector<int>> adj;
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

struct SegmentTree
{

    vector<int> tree;
    SegmentTree(int n)
    {
        tree.resize(4 * n + 1);
    }

    // query type (sum query in this case)
    void makeTree(int ss, int se, int tindex, vector<int> &flat)
    {
        if (ss > se)
            return;
        if (ss == se)
        {
            tree[tindex] = flat[ss];
            return;
        }

        int mid = (ss + se) >> 1ll;

        makeTree(ss, mid, tindex * 2, flat);
        makeTree(mid + 1, se, tindex * 2 + 1, flat);

        tree[tindex] = tree[2 * tindex] + tree[2 * tindex + 1];
    }

    void update(int ss, int se, int tindex, int index, int value)
    {
        if (ss > index || se < index)
        {
            return;
        }
        if (ss == se && ss == index)
        {
            tree[tindex] = value;
            return;
        }

        int mid = (ss + se) >> 1ll;

        update(ss, mid, tindex * 2, index, value);
        update(mid + 1, se, tindex * 2 + 1, index, value);

        tree[tindex] = tree[2 * tindex] + tree[2 * tindex + 1];
    }

    int query(int ss, int se, int qs, int qe, int tindex)
    {
        if (qs <= ss && qe >= se)
        {
            return tree[tindex];
        }

        if (qs > se || qe < ss)
            return 0;

        int mid = (ss + se) >> 1ll;

        return query(ss, mid, qs, qe, tindex * 2) + query(mid + 1, se, qs, qe, tindex * 2 + 1);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    adj.resize(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> val[i];
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

    SegmentTree Tree(n + 1);
    Tree.makeTree(1, n, 1, flat);
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int s, x;
            cin >> s >> x;
            Tree.update(1, n, 1, tin[s], x);
        }
        else
        {
            int s;
            cin >> s;

            int qs = tin[s], qe = tout[s];
            print(Tree.query(1, n, qs, qe, 1));
        }
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
