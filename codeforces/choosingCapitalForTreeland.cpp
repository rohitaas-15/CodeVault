/*The country Treeland consists of n cities, some pairs of them are connected with unidirectional roads. Overall there are n - 1 roads in the country. We know that if we don't take the direction of the roads into consideration, we can get from any city to any other one.

The council of the elders has recently decided to choose the capital of Treeland. Of course it should be a city of this country. The council is supposed to meet in the capital and regularly move from the capital to other cities (at this stage nobody is thinking about getting back to the capital from these cities). For that reason if city a is chosen a capital, then all roads must be oriented so that if we move along them, we can get from city a to any other city. For that some roads may have to be inversed.

Help the elders to choose the capital so that they have to inverse the minimum number of roads in the country.

Input
The first input line contains integer n (2 ≤ n ≤ 2·105) — the number of cities in Treeland. Next n - 1 lines contain the descriptions of the roads, one road per line. A road is described by a pair of integers si, ti (1 ≤ si, ti ≤ n; si ≠ ti) — the numbers of cities, connected by that road. The i-th road is oriented from city si to city ti. You can consider cities in Treeland indexed from 1 to n.

Output
In the first line print the minimum number of roads to be inversed if the capital is chosen optimally. In the second line print all possible ways to choose the capital — a sequence of indexes of cities in the increasing order.
https://codeforces.com/problemset/problem/219/D*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
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
vector<int> adj[N], dp(N);
map<pair<int, int>, int> isRoad;

void dfs(int node, int par)
{
    int inv = 0;

    for (auto i : adj[node])
        if (i != par)
        {
            dfs(i, node);
            inv += dp[i] + (1 - isRoad[{node, i}]);
        }

    dp[node] = inv;
}

int ans = 1e9;
vector<pair<int, int>> cities;
void reRoot(int node, int par)
{
    cities.push_back({node, dp[node]});
    ans = min(ans, dp[node]);

    for (auto i : adj[node])
    {
        if (i != par)
        {
            dp[node] -= (dp[i] + (1 - isRoad[{node, i}]));
            dp[i] += (dp[node] + (1 - isRoad[{i, node}]));
            reRoot(i, node);
            dp[i] -= (dp[node] + (1 - isRoad[{i, node}]));
            dp[node] += (dp[i] + (1 - isRoad[{node, i}]));
        }
    }
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        scan(x, y);
        adj[x].push_back(y);
        adj[y].push_back(x);
        isRoad[{x, y}]++;
    }
    dfs(1, 0), reRoot(1, 0);

    vector<int> potential;

    for (auto i : cities)
    {
        if (i.second == ans)
        {
            potential.push_back(i.first);
        }
    }

    sort(all(potential));

    print(ans);
    print(potential);
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