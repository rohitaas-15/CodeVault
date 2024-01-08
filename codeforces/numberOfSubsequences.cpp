#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
long long int _debug = 1, _nested = 0, _t = 1, INF = 1e18 + 2;
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
    {
        nl;
    }
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
const int M = 1e9 + 7;
void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<int>> dp(n + 1, vector<int>(4, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        dp[i] = dp[i - 1];
        if (s[i - 1] == 'a')
        {
            dp[i][1] = (dp[i - 1][1] + dp[i - 1][0]) % M;
        }
        else if (s[i - 1] == 'b')
        {

            dp[i][2] = (dp[i - 1][2] + dp[i - 1][1]) % M;
        }
        else if (s[i - 1] == 'c')
        {

            dp[i][3] = (dp[i - 1][3] + dp[i - 1][2]) % M;
        }
        else
        {
            dp[i][0] = (3 * dp[i - 1][0]) % M;
            dp[i][1] = (3 * dp[i - 1][1] + dp[i - 1][0]) % M;
            dp[i][2] = (3 * dp[i - 1][2] + dp[i - 1][1]) % M;
            dp[i][3] = (3 * dp[i - 1][3] + dp[i - 1][2]) % M;
        }
    }
    print(dp[n][3]);
}

signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    // cin >> _t;
    for (int tc = 1; tc <= _t; tc++)
        solve();
}

// cin does not move the input cursor to the next line, use cin.ignore() to
// move it to the next line use an array instead of an int whenever possible,
// for coding competitions