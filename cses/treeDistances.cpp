/*You are given a tree consisting of n nodes.
Your task is to determine for each node the maximum distance to another node.
Input
The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,\ldots,n.
Then there are n-1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.
Output
Print n integers: for each node 1,2,\ldots,n, the maximum distance to another node.
Constraints

1 \le n \le 2 \cdot 10^5
1 \le a,b \le n
https://cses.fi/problemset/task/1132/
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
vector<pair<int, int>> Max(N, {0ll, 0ll});

int dfs(int node, int par)
{
    int mx = -1, smx = -1;
    for (auto i : adj[node])
    {
        if (i != par)
        {
            int h = dfs(i, node);
            if (h >= mx)
                smx = mx, mx = h;
            else if (h >= smx)
                smx = h;
        }
    }
    Max[node] = {mx + 1, smx + 1};
    return mx + 1;
}

vector<int> ans;

void reRoot(int node, int par)
{
    ans[node - 1] = Max[node].first;
    for (auto i : adj[node])
    {
        if (i != par)
        {
            auto temp = Max[i];
            int mx = Max[i].first, smx = Max[i].second, h;
            if (Max[node].first == Max[i].first + 1)
                h = Max[node].second + 1;
            else
                h = Max[node].first + 1;

            if (h >= mx)
                smx = mx, mx = h;
            else if (h >= smx)
                smx = h;

            Max[i] = {mx, smx};
            reRoot(i, node);
            Max[i] = temp;
        }
    }
}
void solve()
{
    int n;
    cin >> n;
    ans.resize(n, 0);

    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
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