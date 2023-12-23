/*Time limit: 1.00 s

Your task is to find the k shortest flight routes from Syrjälä to Metsälä. A route can visit the same city several times.
Note that there can be several routes with the same price and each of them should be considered (see the example).
Input
The first input line has three integers n, m, and k: the number of cities, the number of flights, and the parameter k. The cities are numbered 1,2,\ldots,n. City 1 is Syrjälä, and city n is Metsälä.
After this, the input has m lines describing the flights. Each line has three integers a, b, and c: a flight begins at city a, ends at city b, and its price is c. All flights are one-way flights.
You may assume that there are at least k distinct routes from Syrjälä to Metsälä.
Output
Print k integers: the prices of the k cheapest routes sorted according to their prices.
Constraints

2 \le n \le 10^5
1 \le m \le 2 \cdot 10^5
1 \le a,b \le n
1 \le c \le 10^9
1 \le k \le 10
https://cses.fi/problemset/task/1196/*/
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
int n, m, k;
vector<vector<int>> dis(N);
vector<vector<vector<int>>> adj(N);

bool distanceUpdated(vector<int> &v, int val)
{
    int n = v.size();
    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i] > val)
        {
            flag = true;
            int replace = val, store;
            for (int j = i; j < n; j++)
            {
                store = v[j], v[j] = replace;
                replace = store;
            }
            break;
        }
    }

    return flag;
}

void solve()
{
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].push_back({y, w});
    }

    multiset<vector<int>> s; //because shortest flights can have same value

    for (int node = 1; node <= n; node++)
    {
        dis[node].resize(k, INF);
    }

    dis[1][0] = 0;

    s.insert({0, 1}); // weight,node

    while (!s.empty()) //Dijkstra to store the shortest k flights of every node
    {
        auto node = *(s.begin());
        s.erase(s.begin());
        int from = node[1], val = node[0];

        for (auto i : adj[from])
        {
            int to = i[0];
            int mx = dis[to][k - 1];
            if (distanceUpdated(dis[to], i[1] + val))
            {
                auto it = s.lower_bound({mx, to});
                if (it != s.end())
                {
                    s.erase(it);
                }
                s.insert({i[1] + val, to});
            }
        }
    }

    print(dis[n]);
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