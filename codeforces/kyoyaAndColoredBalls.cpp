/*Kyoya Ootori has a bag with n colored balls that are colored with k different colors. The colors are labeled from 1 to k. Balls of the same color are indistinguishable. He draws balls from the bag one by one until the bag is empty. He noticed that he drew the last ball of color i before drawing the last ball of color i + 1 for all i from 1 to k - 1. Now he wonders how many different ways this can happen.

Input
The first line of input will have one integer k (1 ≤ k ≤ 1000) the number of colors.

Then, k lines will follow. The i-th line will contain ci, the number of balls of the i-th color (1 ≤ ci ≤ 1000).

The total number of balls doesn't exceed 1000.

Output
A single integer, the number of ways that Kyoya can draw the balls from the bag as described in the statement, modulo 1 000 000 007
https://codeforces.com/problemset/problem/553/A*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
long long int _debug = 0, _nested = 0, _t = 1, INF = 1e18 + 2;
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
const int M = 1e9 + 7, N = 2001;

void solve()
{
    vector<vector<int>> NCR(N, vector<int>(N, 0));
    NCR[0][0] = 1;
    for (int i = 1; i < N; i++)
    {
        NCR[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            NCR[i][j] = (NCR[i - 1][j] + NCR[i - 1][j - 1]) % M;
        }
    }

    int k;
    cin >> k;
    int balls = 0;
    int ans = 1;
    for (int i = 1; i <= k; i++)
    {
        int x;
        cin >> x;
        int sn = x - 1, sk = balls + 1;
        ans = (ans * NCR[sn + sk - 1][sk - 1]) % M;
        balls += x;
    }
    print(ans);
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