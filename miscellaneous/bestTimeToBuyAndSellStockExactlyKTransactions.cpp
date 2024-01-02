#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
long long _t = 1, _debug = 0, _nested = 0, INF = 1e18 + 2;
// macros-------------------------------------------------------------------------------
#define ll long long
#define int ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
#define endl "\n"
#define nl        \
    cout << endl; \
    if (_debug)   \
        cerr << endl;

// print
// helper-------------------------------------------------------------------------------
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

// code----------------------------------------------------------------------------------

const int N = 3e5 + 2;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> prices(n);
    scan(prices);
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(k + 1, vector<int>(3, -INF)));
    for (int i = 0; i <= n; i++)
    {
        dp[i][0][0] = 0;
        dp[i][0][1] = dp[i][0][2] = -INF;
    }
    for (int txn = 1; txn <= k; txn++)
    {
        int maxBuy = -INF;
        for (int i = 1; i <= n; i++)
        {
            dp[i][txn][0] = max(dp[i - 1][txn][2], dp[i - 1][txn][0]);
            if (n - i + 1 >= 2)
                dp[i][txn][1] = -prices[i - 1] + max({dp[i - 1][txn - 1][0], dp[i - 1][txn - 1][2]});
            dp[i][txn][2] = prices[i - 1] + maxBuy;
            maxBuy = max(maxBuy, dp[i][txn][1]);
        }
    }

    print(max({dp[n][k][0], dp[n][k][1], dp[n][k][2]}));
}

signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    // cin >> _t;
    for (int tc = 1; tc <= _t; tc++)
    {
        solve();
    }
}

// 1. cin does not move the input cursor to the next line, use cin.ignore() to
// move it to the next line
// 2.use an array instead of an int whenever possible,
// for coding competitions, memset only works for values 0 and -1
