/*You play a game consisting of n rooms and m tunnels. Your initial score is 0, and each tunnel increases your score by x where x may be both positive or negative. You may go through a tunnel several times.
Your task is to walk from room 1 to room n. What is the maximum score you can get?
Input
The first input line has two integers n and m: the number of rooms and tunnels. The rooms are numbered 1,2,\dots,n.
Then, there are m lines describing the tunnels. Each line has three integers a, b and x: the tunnel starts at room a, ends at room b, and it increases your score by x. All tunnels are one-way tunnels.
You can assume that it is possible to get from room 1 to room n.
Output
Print one integer: the maximum score you can get. However, if you can get an arbitrarily large score, print -1.
Constraints

1 \le n \le 2500
1 \le m \le 5000
1 \le a,b \le n
-10^9 \le x \le 10^9
https://cses.fi/problemset/task/1673/*/
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

const int N = 2502;
int n, m, destination;
vector<int> vis(N, 0), dis(N, INF);
vector<vector<int>> adj(N);
vector<vector<int>> edges;
vector<int> canReachFrom(N, 0);

bool canReachDestination(int node, int dest)
{
    if (node == dest)
        return true;

    vis[node] = 1;
    for (auto i : adj[node])
    {
        if (!vis[i])
        {
            bool yes = canReachDestination(i, dest);
            if (yes)
            {
                return yes;
            }
        }
    }

    return false;
}

void solve()
{
    cin >> n >> m;
    destination = n;

    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].push_back(y);
        edges.push_back({x, y, -w});
    }

    for (int node = 1; node <= n; node++)
    {
        fill(0ll, vis);
        canReachFrom[node] = canReachDestination(node, destination);
    }

    dis[1] = 0;
    for (int k = 1; k <= n - 1; k++)
    {
        for (auto i : edges)
        {
            if (dis[i[0]] != INF && dis[i[0]] + i[2] < dis[i[1]])
            {
                dis[i[1]] = dis[i[0]] + i[2];
            }
        }
    }

    for (auto i : edges)
    {
        if (dis[i[0]] != INF && dis[i[0]] + i[2] < dis[i[1]] && canReachFrom[i[1]])
        {
            print(-1);
            exit(0);
        }
    }
    print(-dis[n]);
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