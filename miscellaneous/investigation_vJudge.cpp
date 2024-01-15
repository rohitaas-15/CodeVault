/*An integer is divisible by 3 if the sum of its digits is also divisible by 3. For example, 3702 is divisible by 3 and 12 (3+7+0+2) is also divisible by 3. This property also holds for the integer 9.

In this problem, we will investigate this property for other integers.

Input
Input starts with an integer T (≤ 200), denoting the number of test cases.

Each case contains three positive integers A, B and K (1 ≤ A ≤ B < 231 and 0 < K < 10000)>.

Output
For each case, output the case number and the number of integers in the range [A, B] which are divisible by K and the sum of its digits is also divisible by K.*/
//https://vjudge.net/problem/LightOJ-1068
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
string s;
int dp[11][2][91][91], k;
int count(int index, int last, int sumModulo, int digitModulo)
{
    if (index == s.size())
    {
        return sumModulo == 0 && digitModulo == 0;
    }

    if (dp[index][last][sumModulo][digitModulo] != -1)
        return dp[index][last][sumModulo][digitModulo];

    int limit = (last) ? s[index] - '0' : 9;
    int ans = 0;
    for (int i = 0; i <= limit; i++)
    {
        ans = ans + count(index + 1, last && i == limit, (sumModulo * 10 + i) % k, (digitModulo + i) % k);
    }
    return dp[index][last][sumModulo][digitModulo] = ans;
}
int giveCount(int _n)
{
    memset(dp, -1ll, sizeof(dp));
    s = to_string(_n);
    return count(0, 1, 0, 0);
}

void solve()
{
    int a, b;
    cin >> a >> b >> k;
    if (k > 90) // as the sum of digits would at max be 90, and mod k will never be 0
    {
        print(0);
        return;
    }
    print(giveCount(b) - giveCount(a - 1));
}

signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    cin >> _t;
    for (int tc = 1; tc <= _t; tc++)
    {
        cout << "Case " << tc << ":"
             << " ";
        solve();
    }
}

// cin does not move the input cursor to the next line, use cin.ignore() to
// move it to the next line use an array instead of an int whenever possible,
// for coding competitions