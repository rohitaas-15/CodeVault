/*Consider the decimal presentation of an integer. Let's call a number d-magic if digit d appears in decimal presentation of the number on even positions and nowhere else.

For example, the numbers 1727374, 17, 1 are 7-magic but 77, 7, 123, 34, 71 are not 7-magic. On the other hand the number 7 is 0-magic, 123 is 2-magic, 34 is 4-magic and 71 is 1-magic.

Find the number of d-magic numbers in the segment [a, b] that are multiple of m. Because the answer can be very huge you should only find its value modulo 109 + 7 (so you should find the remainder after dividing by 109 + 7).

Input
The first line contains two integers m, d (1 ≤ m ≤ 2000, 0 ≤ d ≤ 9) — the parameters from the problem statement.

The second line contains positive integer a in decimal presentation (without leading zeroes).

The third line contains positive integer b in decimal presentation (without leading zeroes).

It is guaranteed that a ≤ b, the number of digits in a and b are the same and don't exceed 2000.

Output
Print the only integer a — the remainder after dividing by 109 + 7 of the number of d-magic numbers in segment [a, b] that are multiple of m.

https://codeforces.com/contest/628/problem/D*/
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
const int N = 2002, M = 1e9 + 7;
int dp[N][2][2][2][N], m, d;
string s;
int count(int index, int zero, int even, int last, int sum)
{
    if (index == s.size())
        return sum == 0;

    if (dp[index][zero][even][last][sum] != -1)
        return dp[index][zero][even][last][sum];

    if (even)
    {
        int limit = (last) ? s[index] - '0' : 9;
        if (d > limit)
            return 0;
        return dp[index][zero][even][last][sum] = count(index + 1, 0, 0, last && (d == limit), (10ll * sum + d) % m);
    }
    else
    {
        int ans = 0;
        int limit = (last) ? s[index] - '0' : 9;
        for (int i = 0; i <= limit; i++)
        {
            int zeroNow = zero && (i == 0);
            int evenNow = !zeroNow;
            if (i != d)
                ans = (ans + count(index + 1, zeroNow, evenNow, last && (i == limit), (sum * 10ll + i) % m)) % M;
        }
        return dp[index][zero][even][last][sum] = ans;
    }
}
bool checkDMagical(string a)
{
    bool even = 0;
    int sum = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (!even)
        {
            if (a[i] - '0' == d)
                return false;
            even = true;
        }
        else
        {
            if (a[i] - '0' != d)
                return false;
            even = false;
        }
        sum = (sum * 10ll + (a[i] - '0')) % m;
    }
    return sum == 0;
}
void solve()
{

    cin >> m >> d;
    string a, b;
    cin >> a >> b;
    memset(dp, -1, sizeof(dp));
    s = a;
    int p1 = count(0, 1, 0, 1, 0);
    memset(dp, -1, sizeof(dp));
    s = b;
    int p2 = count(0, 1, 0, 1, 0);
    print((p2 - p1 + checkDMagical(a) + M) % M);
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