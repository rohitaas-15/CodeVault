/*For the lab assignment of this week , Shil got N numbers A1 , A2, ... AN. He must assign each of these numbers a unique integer value from 1 to M. Let Ci be the integer assigned to Ai . Shil must assign numbers in such a way that maximum number of Ai are divisible by their Ci . You must print maximum numbers of Ai that could be made divisible by Ci in optimal assignment.

Input:
First Line of input consists of integer N and M.
Next N lines consists of N integers with ith line containing integer Ai.

Output:
Output maximum number of Ai that can be made divisible by Ci in optimal assignment.

Constraints:

1 ≤ N ≤ 103
1 ≤ Ai ≤ 105
N ≤ M ≤ 105
https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/practice-problems/algorithm/shil-and-lab-assignment-14/*/
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
void scan(Primitive &P) { cin >> P; }
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
void fill(Primitive Value, Primitive &P) { P = Value; }
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
//-------------------------------------------------------------------------------

struct Dinic
{
    vector<vector<int>> adj;
    vector<int> level, vis;
    int n, src, sink, ec = 0;
    vector<vector<int>> edges;
    Dinic(int n, int src, int sink)
    {
        this->n = n, this->src = src, this->sink = sink;
        adj.resize(n + 1);
    }
    void addEdge(int x, int y, int w)
    {
        edges.push_back({x, y, w});
        adj[x].push_back(ec++);
        edges.push_back({y, x, 0});
        adj[y].push_back(ec++);
    }

    bool levelGraph()
    {
        level.clear(), level.resize(n + 1, -1);
        level[src] = 0;
        queue<int> q;
        q.push(src);
        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (auto i : adj[node])
            {
                int to = edges[i][1];
                int res = edges[i][2];

                if (res && level[to] == -1)
                {
                    level[to] = level[node] + 1;
                    q.push(to);
                }
            }
        }
        return level[sink] != -1;
    }

    int augmentPath(int node, int mn)
    {
        //print(node);
        if (node == sink)
            return mn;
        vis[node] = 1;
        int flow = 0;
        for (auto i : adj[node])
        {
            int to = edges[i][1], res = edges[i][2];
            if (res && mn && !vis[to] && level[to] == level[node] + 1)
            {
                int newMn = min(mn, res);
                int cFlow = augmentPath(to, newMn);
                flow += cFlow, edges[i][2] -= cFlow, edges[i ^ 1][2] += cFlow, mn -= cFlow;
            }
        }
        return flow;
    }

    int max_flow()
    {
        int flow = 0;

        while (levelGraph())
        {
            vis.clear(), vis.resize(n + 1, 0);
            if(!(flow+=augmentPath(src,1e9)))
            {
                break;
            }
        }
        return flow;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    int src = n + m + 3, sink = n + m + 4;
    Dinic g(n + m + 5, src, sink);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        g.addEdge(src, i, 1);
        for (int j = 1; j * j <= x; j++)
        {
            if (x % j == 0)
            {
                if (j <= m)
                    g.addEdge(i, n + j, 1);

                if (x / j != j)
                {
                    if (x / j <= m)
                        g.addEdge(i, n + x / j, 1);
                }
            }
        }
    }

    for (int i = 1; i <= m; i++)
    {
        g.addEdge(n + i, sink, 1);
    }

    print(g.max_flow());
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