/*There are n cities and m roads between them. Your task is to process q queries where you have to determine the length of the shortest route between two given cities.
Input
The first input line has three integers n, m and q: the number of cities, roads, and queries.
Then, there are m lines describing the roads. Each line has three integers a, b and c: there is a road between cities a and b whose length is c. All roads are two-way roads.
Finally, there are q lines describing the queries. Each line has two integers a and b: determine the length of the shortest route between cities a and b.
Output
Print the length of the shortest route for each query. If there is no route, print -1 instead.
https://cses.fi/problemset/task/1672/*/
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

const int N = 502;
int n, m, q;
vector<vector<int>> dp(N, vector<int>(N, INF));
void solve()
{
    cin >> n >> m >> q;

    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        dp[x][y] = dp[y][x] = min(dp[x][y], w);
    }

    for (int node = 1; node <= n; node++)
    {
        dp[node][node] = 0;
    }

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (dp[i][k] + dp[k][j] < dp[i][j])
                {
                    dp[i][j] = dp[i][k] + dp[k][j];
                }
            }
        }
    }

    while (q--)
    {
        int a, b;
        cin >> a >> b;

        if (dp[a][b] == INF)
        {
            print(-1);
        }
        else
            print(dp[a][b]);
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