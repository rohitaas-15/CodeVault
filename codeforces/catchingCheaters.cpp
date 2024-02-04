/*You are given two strings 𝐴
 and 𝐵
 representing essays of two students who are suspected cheaters. For any two strings 𝐶
, 𝐷
 we define their similarity score 𝑆(𝐶,𝐷)
 as 4⋅𝐿𝐶𝑆(𝐶,𝐷)−|𝐶|−|𝐷|
, where 𝐿𝐶𝑆(𝐶,𝐷)
 denotes the length of the Longest Common Subsequence of strings 𝐶
 and 𝐷
.

You believe that only some part of the essays could have been copied, therefore you're interested in their substrings.

Calculate the maximal similarity score over all pairs of substrings. More formally, output maximal 𝑆(𝐶,𝐷)
 over all pairs (𝐶,𝐷)
, where 𝐶
 is some substring of 𝐴
, and 𝐷
 is some substring of 𝐵
.

If 𝑋
 is a string, |𝑋|
 denotes its length.

A string 𝑎
 is a substring of a string 𝑏
 if 𝑎
 can be obtained from 𝑏
 by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

A string 𝑎
 is a subsequence of a string 𝑏
 if 𝑎
 can be obtained from 𝑏
 by deletion of several (possibly, zero or all) characters.

Pay attention to the difference between the substring and subsequence, as they both appear in the problem statement.

You may wish to read the Wikipedia page about the Longest Common Subsequence problem.

Input
The first line contains two positive integers 𝑛
 and 𝑚
 (1≤𝑛,𝑚≤5000
) — lengths of the two strings 𝐴
 and 𝐵
.

The second line contains a string consisting of 𝑛
 lowercase Latin letters — string 𝐴
.

The third line contains a string consisting of 𝑚
 lowercase Latin letters — string 𝐵
.

Output
Output maximal 𝑆(𝐶,𝐷)
 over all pairs (𝐶,𝐷)
, where 𝐶
 is some substring of 𝐴
, and 𝐷
 is some substring of 𝐵
.
https://codeforces.com/contest/1446/problem/B
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
long long int _debug = 0, _nested = 0, _t = 1, INF = 1e18 + 2;
// macros-------------------------------------------------------------------------------
// #define ll long long
// #define int ll
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
void solve()
{
    int n, m;
    cin >> n >> m;
    string a, b;
    cin >> a >> b;

    int dp[n + 1][m + 1];
    memset(dp, 0, sizeof(dp)); // stores the answer until a[0]...a[i] && b[0]....b[i] +i+j(for space optimization)
    int ans = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (a[i - 1] == b[j - 1])
            {
                dp[i][j] = max(2 + i + j, dp[i - 1][j - 1] + 4);
                ans = max(ans, dp[i][j] - i - j);
            }
            else if (dp[i][j - 1] > dp[i - 1][j])
            {
                dp[i][j] = dp[i][j - 1];
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    print(ans);
}

signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    // cin >> _t;
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