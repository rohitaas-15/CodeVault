/*You are given a tree consisting of n nodes, and m paths in the tree.
Your task is to calculate for each node the number of paths containing that node.
The first input line contains integers n and m: the number of nodes and paths. The nodes are numbered 1,2,\ldots,n.
Then there are n-1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.
Finally, there are m lines describing the paths. Each line contains two integers a and b: there is a path between nodes a and b.
Output
Print n integers: for each node 1,2,\ldots,n, the number of paths containing that node.
Constraints

1 \le n, m \le 2 \cdot 10^5
1 \le a,b \le n

https://cses.fi/problemset/task/1136/
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

const int N = 2e5 + 2, M = 21;
vector<int> adj[N], depth(N, 0), pathFreq(N, 0);
vector<vector<int>> sparse(N, vector<int>(M, 0));

void dfs(int node, int par, int dep)
{
    sparse[node][0] = par;
    for (int j = 1; j < M; j++)
    {
        sparse[node][j] = sparse[sparse[node][j - 1]][j - 1];
    }

    depth[node] = dep;
    for (auto i : adj[node])
    {
        if (i != par)
        {
            dfs(i, node, dep + 1);
        }
    }
}

int LCA(int a, int b)
{
    if (depth[b] > depth[a])
        swap(a, b);

    int diff = depth[a] - depth[b];
    for (int j = 0; j < M; j++)
    {
        if (diff & (1 << j))
        {
            a = sparse[a][j];
        }
    }

    if (a == b)
        return b;

    for (int j = M - 1; j >= 0; j--)
    {
        if (sparse[a][j] != sparse[b][j])
        {
            a = sparse[a][j], b = sparse[b][j];
        }
    }
    return sparse[a][0];
}

void dfsSuffix(int node, int par)
{
    int paths = 0;
    for (auto i : adj[node])
    {
        if (i != par)
        {
            dfsSuffix(i, node);

            paths += pathFreq[i];
        }
    }
    paths += pathFreq[node];
    pathFreq[node] = paths;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 2; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1, 0, 0);
    while (m--)
    {
        int a, b;
        scan(a, b);
        int lca = LCA(a,b);
        pathFreq[a]++, pathFreq[b]++, pathFreq[lca]--,pathFreq[sparse[lca][0]]--;
    }

    dfsSuffix(1, 0); // take suffix sum of every node from leaf nodes

    for (int i = 1; i <= n; i++)
    {
        cout << pathFreq[i] << " ";
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