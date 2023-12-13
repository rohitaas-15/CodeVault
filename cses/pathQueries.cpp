/*You are given a rooted tree consisting of n nodes. The nodes are numbered 1,2,\ldots,n, and node 1 is the root. Each node has a value.
Your task is to process following types of queries:

change the value of node s to x
calculate the sum of values on the path from the root to node s

Input
The first input line contains two integers n and q: the number of nodes and queries. The nodes are numbered 1,2,\ldots,n.
The next line has n integers v_1,v_2,\ldots,v_n: the value of each node.
Then there are n-1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.
Finally, there are q lines describing the queries. Each query is either of the form "1 s x" or "2 s".
Output
Print the answer to each query of type 2.
Constraints

1 \le n, q \le 2 \cdot 10^5
1 \le a,b, s \le n
1 \le v_i, x \le 10^9
https://cses.fi/problemset/task/1138/
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
vector<int> adj[N], flat(N), tin(N), tout(N), pre(N), val(N);
;
int tme = 0;

void dfsTime(int node, int par)
{
    tin[node] = ++tme;
    for (auto i : adj[node])
        if (i != par)
        {
            dfsTime(i, node);
        }
    tout[node] = tme;
}

void dfsPrefix(int node, int par, int sum)
{
    pre[node] = sum + val[node];

    for (auto i : adj[node])
        if (i != par)
        {
            dfsPrefix(i, node, sum + val[node]);
        }
}

struct SegmentTree
{
    vector<int> tree, lazy; // diff between current value and new value
    SegmentTree(int N)
    {
        tree.resize(4 * N + 1, 0);
        lazy.resize(4 * N + 1, 0);
    }

    void makeTree(int ss, int se, int ti, vector<int> &flat)
    {
        if (ss > se)
            return;
        if (ss == se)
        {
            tree[ti] = flat[ss];
            return;
        }

        int mid = (ss + se) >> 1;

        makeTree(ss, mid, ti * 2, flat), makeTree(mid + 1, se, ti * 2 + 1, flat);
        tree[ti] = tree[ti * 2] + tree[ti * 2 + 1];
    }

    void update(int ss, int se, int qs, int qe, int ti, int add)
    {

        tree[ti] += (se - ss + 1) * lazy[ti];
        if (ss != se)
        {
            lazy[ti * 2] += lazy[ti];
            lazy[ti * 2 + 1] += lazy[ti];
        }
        lazy[ti] = 0;

        if (qs > se || qe < ss)
        {
            return;
        }

        if (qs <= ss && qe >= se)
        {
            tree[ti] += (add) * (se - ss + 1);
            if (ss != se)
            {
                lazy[ti * 2] += add;
                lazy[ti * 2 + 1] += add;
            }
            return;
        }

        int mid = (ss + se) >> 1;

        update(ss, mid, qs, qe, 2 * ti, add), update(mid + 1, se, qs, qe, 2 * ti + 1, add);
        return;
    }

    int query(int ss, int se, int qs, int qe, int ti)
    {
        tree[ti] += (se - ss + 1) * lazy[ti];
        if (ss != se)
        {
            lazy[ti * 2] += lazy[ti];
            lazy[ti * 2 + 1] += lazy[ti];
        }
        lazy[ti] = 0;

        if (qs > se || qe < ss)
        {
            return 0ll;
        }

        if (qs <= ss && qe >= se)
        {
            return tree[ti];
        }

        int mid = (ss + se) >> 1;
        return query(ss, mid, qs, qe, ti * 2) + query(mid + 1, se, qs, qe, 2 * ti + 1);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
    {
        cin >> val[i];
    }

    for (int i = 2; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    dfsPrefix(1, 0, 0);
    dfsTime(1, 0);

    for (int node = 1; node <= n; node++)
    {
        flat[tin[node]] = pre[node];
    }

    SegmentTree tree(n + 1);

    tree.makeTree(1, n, 1, flat);

    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int s, x;
            cin >> s >> x;
            int add = x - val[s];
            tree.update(1, n, tin[s], tout[s], 1, add);
            val[s] = x;
        }
        else
        {
            int s;
            cin >> s;
            print(tree.query(1, n, tin[s], tin[s], 1));
        }
    }
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