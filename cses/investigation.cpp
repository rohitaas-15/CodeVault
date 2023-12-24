/*Time limit: 1.00 s
Memory limit: 512 MB



You are going to travel from Syrjälä to Lehmälä by plane. You would like to find answers to the following questions:

what is the minimum price of such a route?
how many minimum-price routes are there? (modulo 10^9+7)
what is the minimum number of flights in a minimum-price route?
what is the maximum number of flights in a minimum-price route?

Input
The first input line contains two integers n and m: the number of cities and the number of flights. The cities are numbered 1,2,\ldots,n. City 1 is Syrjälä, and city n is Lehmälä.
After this, there are m lines describing the flights. Each line has three integers a, b, and c: there is a flight from city a to city b with price c. All flights are one-way flights.
You may assume that there is a route from Syrjälä to Lehmälä.
Output
Print four integers according to the problem statement.
https://cses.fi/problemset/task/1202/*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define INF 1000000000000000000ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
#define endl "\n"
#define nl cerr << endl, cout << endl

//-------------------------------------------------------------------------------
// print helper
int _nested = 0;
template <typename Primitive>
void print(Primitive &&P)
{
    cerr << P << " ";
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

const int N = 1e5 + 2, M = 1e9 + 7;
int n, m;
vector<vector<vector<int>>> adj(N);
vector<int> minDistance(N, INF), totalRoutes(N, 0), maxFlightCnt(N, 0), minFlightCnt(N, INF);

void solve()
{

    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].push_back({y, w});
    }

    set<vector<int>> s;
    minDistance[1] = 0, totalRoutes[1] = 1, maxFlightCnt[1] = 0, minFlightCnt[1] = 0;

    s.insert({0, 1, 1, 0, 0}); // min distance, node number, totalRoutes,mxFlights,mnFlights

    while (!s.empty())
    {
        auto node = *(s.begin());
        s.erase(node);

        int from = node[1], val = node[0], noRoutes = node[2] % M, mx = node[3], mn = node[4];

        for (auto i : adj[from])
        {

            int to = i[0], w = i[1];

            if (val + w == minDistance[to])
            {
                s.erase({minDistance[to], to, totalRoutes[to], maxFlightCnt[to], minFlightCnt[to]});
                totalRoutes[to] = (totalRoutes[to] + noRoutes) % M;
                maxFlightCnt[to] = max(maxFlightCnt[to], mx + 1), minFlightCnt[to] = min(minFlightCnt[to], mn + 1);
                s.insert({minDistance[to], to, totalRoutes[to], maxFlightCnt[to], minFlightCnt[to]});
            }
            else if (val + w < minDistance[to])
            {
                s.erase({minDistance[to], to, totalRoutes[to], maxFlightCnt[to], minFlightCnt[to]});
                minDistance[to] = val + w, totalRoutes[to] = noRoutes % M;
                maxFlightCnt[to] = mx + 1, minFlightCnt[to] = mn + 1;
                s.insert({minDistance[to], to, totalRoutes[to], maxFlightCnt[to], minFlightCnt[to]});
            }
        }
    }
    print(minDistance[n], totalRoutes[n], minFlightCnt[n], maxFlightCnt[n]);
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