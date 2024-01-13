/*Majid is a 3rd-grade elementary student and quite well in mathematics. Once, Majid's teacher asked him to calculate the sum of numbers 1 through n.

Majid quickly answered, and his teacher made him another challenge. He asked Majid to calculate the sum of the digits of numbers 1 through n.

Majid did finally find the solution. Now it is your turn, can you find a solution?

Input
Two space-separated integers 0 <= a <= b <= 109.

Program terminates if a and b are -1.

Output
The sum of the digits of numbers a through b.
https://www.spoj.com/problems/CPCRC1C/*/

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

int dp[11][2][120];
int sumOfDigits(int index, int last, int sumOfprevDigits, string &s)
{
    if (index == s.size())
        return sumOfprevDigits;

    if (dp[index][last][sumOfprevDigits] != -1)
        return dp[index][last][sumOfprevDigits];

    int limit = ((last) ? (s[index] - '0') : 9ll);
    int ans = 0;
    for (int i = 0; i <= limit; i++)
    {
        ans = ans + sumOfDigits(index + 1, (last && (i == limit)), sumOfprevDigits + i, s);
    }
    return dp[index][last][sumOfprevDigits] = ans;
}

void solve()
{
    while (true)
    {
        int a, b;
        cin >> a >> b;
        if (a == -1)
            return;
        string sa = to_string(a - 1);
        string sb = to_string(b);

        memset(dp, -1ll, sizeof(dp));
        int p1 = sumOfDigits(0, 1, 0, sa);

        memset(dp, -1ll, sizeof(dp));
        int p2 = sumOfDigits(0, 1, 0, sb);
        print(p2 - p1);
    }
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