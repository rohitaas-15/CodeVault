/*All of Slavic's friends are planning to travel from the place where they live to a party using their bikes. And they all have a bike except Slavic. There are 𝑛
 cities through which they can travel. They all live in the city 1
 and want to go to the party located in the city 𝑛
. The map of cities can be seen as an undirected graph with 𝑛
 nodes and 𝑚
 edges. Edge 𝑖
 connects cities 𝑢𝑖
 and 𝑣𝑖
 and has a length of 𝑤𝑖
.

Slavic doesn't have a bike, but what he has is money. Every city has exactly one bike for sale. The bike in the 𝑖
-th city has a slowness factor of 𝑠𝑖
. Once Slavic buys a bike, he can use it whenever to travel from the city he is currently in to any neighboring city, by taking 𝑤𝑖⋅𝑠𝑗
 time, considering he is traversing edge 𝑖
 using a bike 𝑗
 he owns.

Slavic can buy as many bikes as he wants as money isn't a problem for him. Since Slavic hates traveling by bike, he wants to get from his place to the party in the shortest amount of time possible. And, since his informatics skills are quite rusty, he asks you for help.

What's the shortest amount of time required for Slavic to travel from city 1
 to city 𝑛
? Slavic can't travel without a bike. It is guaranteed that it is possible for Slavic to travel from city 1
 to any other city.

Input
The first line contains a single integer 𝑡
 (1≤𝑡≤100
) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two space-separated integers 𝑛
 and 𝑚
 (2≤𝑛≤1000
; 𝑛−1≤𝑚≤1000
) — the number of cities and the number of roads, respectively.

The 𝑖
-th of the following 𝑚
 lines each contain three integers 𝑢𝑖
, 𝑣𝑖
, 𝑤𝑖
 (1≤𝑢𝑖,𝑣𝑖≤𝑛
, 𝑢𝑖≠𝑣𝑖
; 1≤𝑤𝑖≤105
), denoting that there is a road between cities 𝑢𝑖
 and 𝑣𝑖
 of length 𝑤𝑖
. The same pair of cities can be connected by more than one road.

The next line contains 𝑛
 integers 𝑠1,…,𝑠𝑛
 (1≤𝑠𝑖≤1000
) — the slowness factor of each bike.

The sum of 𝑛
 over all test cases does not exceed 1000
, and the sum of 𝑚
 over all test cases does not exceed 1000
.

Additional constraint on the input: it is possible to travel from city 1
 to any other city.

Output
For each test case, output a single integer denoting the shortest amount of time Slavic can reach city 𝑛
 starting from city 1
.
https://codeforces.com/contest/1915/problem/G
*/


#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// macros-------------------------------------------------------------------------------
#define ll long long
#define int ll
// #define INF 1000000000000000002ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
#define endl "\n"
int _debug = 0;
#define nl        \
    cout << endl; \
    if (_debug)   \
        cerr << endl;

// print
// helper-------------------------------------------------------------------------------
int _nested = 0;
template <typename Primitive>
void print(Primitive &&P)
{
    cout << P << " ";
    if (_debug)
        cerr << P << " ";
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

//code----------------------------------------------------------------------------------
const int INF = 1e13;
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<vector<int>>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        adj[x].push_back({y, z});
        adj[y].push_back({x, z});
    }

    vector<vector<int>> dis(n + 1, vector<int>(n + 1, INF)); //distance coming to node i from bike j
    vector<int> slowness(n + 1, INF);
    for (int node = 1; node <= n; node++)
    {
        cin >> slowness[node];
    }

    set<vector<int>> s;
    s.insert({0, 1, 0});
    dis[1][0] = 0;

    int ans = INF;

    while (!s.empty())
    {
        auto node = *s.begin();
        s.erase(node);
        int from = node[1];
        int val = node[0];
        if (from == n)
        {
            ans = min(ans, val);
        }
        int curBike = node[2];

        for (auto i : adj[from])
        {
            int to = i[0], w = i[1], newBike = from;

            if ((val + w * slowness[curBike] < dis[to][curBike]))
            {
                s.erase({dis[to][curBike], to, curBike});
                dis[to][curBike] = val + w * slowness[curBike];
                s.insert({dis[to][curBike], to, curBike});
            }

            if ((val + w * slowness[newBike] < dis[to][newBike]))
            {
                s.erase({dis[to][newBike], to, newBike});
                dis[to][newBike] = val + w * slowness[newBike];
                s.insert({dis[to][newBike], to, newBike});
            }
        }
    }
    print(ans);
}

signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    int _t = 1;
    cin >> _t;
    while (_t--)
        solve();
}

// cin does not move the input cursor to the next line, use cin.ignore() to
// move it to the next line use an array instead of an int whenever possible,
// for coding competitions
