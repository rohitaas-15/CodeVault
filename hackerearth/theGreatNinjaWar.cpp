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
int dp[13][2][2521][4][3][2][2], powerDp[11][11]; // making LCM by prime factors, as lcm of all subsets of numbers from 1...9 have cycle 2520, sum%2520 can be taken
int commonLCM = 2520;
int power(int a, int b, int M = LLONG_MAX)
{
    if (!b)
        return 1;
    int sp = power(a, b / 2, M);
    sp = (sp * sp) % M;
    if (b & 1)
        return ((a % M) * sp) % M;
    else
        return sp;
}
vector<int> primes = {2, 3, 5, 7}, primeCnt(4, 0);
 
int count(int index, int last, int sumModulo, int two, int three, int five, int seven)
{
    if (index == s.size())
    {
        if (sumModulo % powerDp[2][two])
        {
            return 0;
        }
 
        if (sumModulo % powerDp[3][three])
        {
            return 0;
        }
 
        if (sumModulo % powerDp[5][five])
        {
            return 0;
        }
 
        if (sumModulo % powerDp[7][seven])
        {
            return 0;
        }
        return 1;
    }
 
    if (dp[index][last][sumModulo][two][three][five][seven] != -1)
    {
        return dp[index][last][sumModulo][two][three][five][seven];
    }
 
    int limit = (last) ? s[index] - '0' : 9;
    int ans = 0;
    for (int i = 0; i <= limit; i++)
    {
        if (i == 0)
        {
            ans += count(index + 1, last && i == limit, sumModulo, two, three, five, seven);
            continue;
        }
 
        int cnt2 = 0;
        int temp = i;
        while (temp % 2 == 0)
        {
            cnt2++, temp /= 2;
        }
        cnt2 = max(two, cnt2);
 
        int cnt3 = 0;
        temp = i;
        while (temp % 3 == 0)
        {
            cnt3++, temp /= 3;
        }
        cnt3 = max(three, cnt3);
 
        int cnt5 = 0;
        temp = i;
        while (temp % 5 == 0)
        {
            cnt5++, temp /= 5;
        }
        cnt5 = max(five, cnt5);
 
        int cnt7 = 0;
        temp = i;
        while (temp % 7 == 0)
        {
            cnt7++, temp /= 7;
        }
        cnt7 = max(seven, cnt7);
 
        ans += count(index + 1, last && i == limit, (sumModulo + powerDp[i][i]) % commonLCM, cnt2, cnt3, cnt5, cnt7);
    }
    return dp[index][last][sumModulo][two][three][five][seven] = ans;
}
 
int countSpecial(int _n)
{
    s = to_string(_n);
    memset(dp, -1ll, sizeof(dp));
    return count(0, 1, 0, 0, 0, 0, 0);
}
void solve()
{
    int a, b;
    cin >> a >> b;
 
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 0; j <= 10; j++)
        {
            powerDp[i][j] = power(i, j);
        }
    }
    print(countSpecial(b) - countSpecial(a - 1));
}
 
signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    cin >> _t;
    for (int tc = 1; tc <= _t; tc++)
    {
        // cout << "Case " << tc << ":"
        //      << " ";
        solve();
    }
}
 
// cin does not move the input cursor to the next line, use cin.ignore() to
// move it to the next line use an array instead of an int whenever possible,
// for coding competitions
