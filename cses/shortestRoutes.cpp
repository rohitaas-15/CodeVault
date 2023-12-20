/*There are n cities and m flight connections between them. Your task is to determine the length of the shortest route from Syrjälä to every city.
Input
The first input line has two integers n and m: the number of cities and flight connections. The cities are numbered 1,2,\dots,n, and city 1 is Syrjälä.
After that, there are m lines describing the flight connections. Each line has three integers a, b and c: a flight begins at city a, ends at city b, and its length is c. Each flight is a one-way flight.
You can assume that it is possible to travel from Syrjälä to all other cities.
Output
Print n integers: the shortest route lengths from Syrjälä to cities 1,2,\dots,n.
Constraints

1 \le n \le 10^5
1 \le m \le 2 \cdot 10^5
1 \le a,b \le n
1 \le c \le 10^9
https://cses.fi/problemset/task/1671/*/
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

const int N = 1e5 + 2;
int n, m;
vector<int> dis(N, INF);
vector<vector<vector<int>>> adj(N);
void solve()
{
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].push_back({y, w});
    }

    set<pair<int, int>> s;
    s.insert({0, 1});

    dis[1] = 0;

    while (!s.empty())
    {
        auto node = *(s.begin());
        s.erase(node);

        int from = node.second;

        for (auto i : adj[from])
        {
            if (dis[i[0]] > dis[from] + i[1])
            {
                s.erase({dis[i[0]], i[0]});
                dis[i[0]] = dis[from] + i[1];
                s.insert({dis[i[0]], i[0]});
            }
        }
    }

    for (int node = 1; node <= n; node++)
    {
        cout << dis[node] << " ";
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