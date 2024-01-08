/*You wrote down all integers from 0
 to 10𝑛−1
, padding them with leading zeroes so their lengths are exactly 𝑛
. For example, if 𝑛=3
 then you wrote out 000, 001, ..., 998, 999.

A block in an integer 𝑥
 is a consecutive segment of equal digits that cannot be extended to the left or to the right.

For example, in the integer 00027734000
 there are three blocks of length 1
, one block of length 2
 and two blocks of length 3
.

For all integers 𝑖
 from 1
 to 𝑛
 count the number of blocks of length 𝑖
 among the written down integers.

Since these integers may be too large, print them modulo 998244353
.

Input
The only line contains one integer 𝑛
 (1≤𝑛≤2⋅105
).

Output
In the only line print 𝑛
 integers. The 𝑖
-th integer is equal to the number of blocks of length 𝑖
.

Since these integers may be too large, print them modulo 998244353
.https://codeforces.com/problemset/problem/1327/E*/
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
const int M = 998244353;
int power(int a, int b)
{
    if (!b)
        return 1;
    if (b == 1)
        return a;
    int sp = power(a, b / 2);
    return sp * sp * power(a, b % 2);
}

void solve()
{
    int n;
    cin >> n;

    vector<int> dp(n);
    dp[0] = 10, dp[1] = 180;
    int mul = 81;
    for (int i = 2; i < n; i++)
    {
        dp[i] = ((dp[i - 1] + mul) % M * 10) % M;
        mul = (mul * 10) % M;
    }
    reverse(all(dp));
    print(dp);

    // Got the pattern by implementing brute force

    // int limit = power(10, n) - 1;
    // int len = n;
    // map<int, int> done;
    // for (int i = 0; i <= limit; i++)
    // {

    //     string temp = to_string(i);
    //     reverse(all(temp));
    //     while (temp.length() != len)
    //     {
    //         temp += '0';
    //     }
    //     reverse(all(temp));
    //     int cnt = 1;
    //     for (int j = 1; j < temp.size(); j++)
    //     {
    //         if (temp[j] == temp[j - 1])
    //         {
    //             cnt++;
    //         }
    //         else
    //         {
    //             done[cnt]++;
    //             cnt = 1;
    //         }
    //     }
    //     done[cnt]++;
    // }
    // for (auto i : done)
    // {
    //     print(i.first, i.second);
    // }
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