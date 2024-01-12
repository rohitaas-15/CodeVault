/*Mike has a sequence A = [a1, a2, ..., an] of length n. He considers the sequence B = [b1, b2, ..., bn] beautiful if the gcd of all its elements is bigger than 1, i.e. .

Mike wants to change his sequence in order to make it beautiful. In one move he can choose an index i (1 ≤ i < n), delete numbers ai, ai + 1 and put numbers ai - ai + 1, ai + ai + 1 in their place instead, in this order. He wants perform as few operations as possible. Find the minimal number of operations to make sequence A beautiful if it's possible, or tell him that it is impossible to do so.

 is the biggest non-negative number d such that d divides bi for every i (1 ≤ i ≤ n).

Input
The first line contains a single integer n (2 ≤ n ≤ 100 000) — length of sequence A.

The second line contains n space-separated integers a1, a2, ..., an (1 ≤ ai ≤ 109) — elements of sequence A.

Output
Output on the first line "YES" (without quotes) if it is possible to make sequence A beautiful by performing operations described above, and "NO" (without quotes) otherwise.

If the answer was "YES", output the minimal number of moves needed to make sequence A beautiful.
https://codeforces.com/contest/798/problem/C*/
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

const int N = 1e5 + 2;
int GCD(int a, int b)
{
    if (!b)
        return a;
    return GCD(b, a % b);
}
void solve()
{
    int n;
    cin >> n;
    vector<int> v(n + 1);
    int iniGCD = 0;
    for (int i = 1; i <= n; i++)
        cin >> v[i], iniGCD = GCD(iniGCD, v[i]);

    if (iniGCD != 1)
    {
        print("YES");
        print(0);
        return;
    }

    vector<int> dp(N, 0); //the best answer will come when GCD is 2
    dp[1] = 2 * (v[1] % 2);
    for (int i = 2; i <= n; i++)
    {
        if (v[i] % 2 == 0 && v[i - 1] % 2 == 0)
        {
            dp[i] = min(dp[i - 2], dp[i - 1]);
        }
        else if ((v[i] + v[i - 1]) % 2 == 0)
        {
            dp[i] = min(dp[i - 2] + 1, dp[i - 1] + 2);
        }
        else if (v[i] % 2 == 0)
        {
            dp[i] = min(dp[i - 1], dp[i - 2] + 2);
        }
        else
        {
            dp[i] = min(dp[i - 1], dp[i - 2]) + 2;
        }
    }
    print("YES");
    print(dp[n]);
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