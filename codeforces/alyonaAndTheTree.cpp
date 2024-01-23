/*Alyona decided to go on a diet and went to the forest to get some apples. There she unexpectedly found a magic rooted tree with root in the vertex 1, every vertex and every edge of which has a number written on.

The girl noticed that some of the tree's vertices are sad, so she decided to play with them. Let's call vertex v sad if there is a vertex u in subtree of vertex v such that dist(v, u) > au, where au is the number written on vertex u, dist(v, u) is the sum of the numbers written on the edges on the path from v to u.

Leaves of a tree are vertices connected to a single vertex by a single edge, but the root of a tree is a leaf if and only if the tree consists of a single vertex — root.

Thus Alyona decided to remove some of tree leaves until there will be no any sad vertex left in the tree. What is the minimum number of leaves Alyona needs to remove?

Input
In the first line of the input integer n (1 ≤ n ≤ 105) is given — the number of vertices in the tree.

In the second line the sequence of n integers a1, a2, ..., an (1 ≤ ai ≤ 109) is given, where ai is the number written on vertex i.

The next n - 1 lines describe tree edges: ith of them consists of two integers pi and ci (1 ≤ pi ≤ n,  - 109 ≤ ci ≤ 109), meaning that there is an edge connecting vertices i + 1 and pi with number ci written on it.

Output
Print the only integer — the minimum number of leaves Alyona needs to remove such that there will be no any sad vertex left in the tree.
https://codeforces.com/problemset/problem/682/C*/
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
const int N = 1e5 + 2;
int subtree[N], issue[N], val[N];
vector<vector<vector<int>>> adj(N);

void dfs(int node, int par, int soe)
{
    if (soe > val[node])
    {
        issue[node] = 1;
    }
    subtree[node] = 1;
    for (auto i : adj[node])
    {
        if (i[0] != par)
        {
            dfs(i[0], node, max(soe + i[1], 0ll));
            subtree[node] += subtree[i[0]];
        }
    }
}

int rem = 0;
void resolve(int node, int par)
{
    if (issue[node])
    {
        rem += subtree[node];
        return;
    }

    for (auto i : adj[node])
    {
        if (i[0] != par)
        {
            resolve(i[0], node);
        }
    }
}

void solve()
{
    memset(subtree, 0, sizeof(subtree));
    memset(issue, 0, sizeof(issue));

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> val[i];

    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back({i + 1, b});
        adj[i + 1].push_back({a, b});
    }

    dfs(1, 0, 0);
    resolve(1, 0);
    print(rem);
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
