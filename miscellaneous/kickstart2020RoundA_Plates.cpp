#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
int _t = 1, _debug = 0, _nested = 0;
// macros-------------------------------------------------------------------------------
#define ll long long
#define int ll
#define INF 1000000000000000002ll
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
signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    cin >> _t;
    for (int tc = 1; tc <= _t; tc++)
    {
        int n, k, p;
        cin >> n >> k >> p;

        vector<vector<int>> stacks(n + 1, vector<int>(k + 1, 0));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < k; j++)
            {
                cin >> stacks[i + 1][j + 1];
                stacks[i + 1][j + 1] = stacks[i + 1][j] + stacks[i + 1][j + 1];
            }
        }

        vector<vector<int>> dp(n + 2, vector<int>(p + 1, 0));
        for (int plates = 1; plates <= p; plates++)
        {
            for (int i = 1; i <= n; i++) // stack number
            {
                dp[i][plates] = dp[i - 1][plates];
                for (int j = 1; j <= k; j++)
                {
                    if (j <= plates)
                        dp[i][plates] = max(dp[i][plates], dp[i - 1][plates - j] + stacks[i][j]);
                }
            }
        }
        cout << "Case #" + to_string(tc) + ": " + to_string(dp[n][p]) << endl;
    }
}

// cin does not move the input cursor to the next line, use cin.ignore() to
// move it to the next line use an array instead of an int whenever possible,
// for coding competitions
