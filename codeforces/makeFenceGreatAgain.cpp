/*outputstandard output
You have a fence consisting of 𝑛
 vertical boards. The width of each board is 1
. The height of the 𝑖
-th board is 𝑎𝑖
. You think that the fence is great if there is no pair of adjacent boards having the same height. More formally, the fence is great if and only if for all indices from 2
 to 𝑛
, the condition 𝑎𝑖−1≠𝑎𝑖
 holds.

Unfortunately, it is possible that now your fence is not great. But you can change it! You can increase the length of the 𝑖
-th board by 1
, but you have to pay 𝑏𝑖
 rubles for it. The length of each board can be increased any number of times (possibly, zero).

Calculate the minimum number of rubles you have to spend to make the fence great again!

You have to answer 𝑞
 independent queries.

Input
The first line contains one integer 𝑞
 (1≤𝑞≤3⋅105
) — the number of queries.

The first line of each query contains one integers 𝑛
 (1≤𝑛≤3⋅105
) — the number of boards in the fence.

The following 𝑛
 lines of each query contain the descriptions of the boards. The 𝑖
-th line contains two integers 𝑎𝑖
 and 𝑏𝑖
 (1≤𝑎𝑖,𝑏𝑖≤109
) — the length of the 𝑖
-th board and the price for increasing it by 1
, respectively.

It is guaranteed that sum of all 𝑛
 over all queries not exceed 3⋅105
.

It is guaranteed that answer to each query will not exceed 1018
.

Output
For each query print one integer — the minimum number of rubles you have to spend to make the fence great.
https://codeforces.com/contest/1221/problem/D*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define INF 1000000000000000000ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
#define endl "\n"

int _debug = 0;
#define nl        \
    cout << endl; \
    if (_debug)   \
        cerr << endl;

//-------------------------------------------------------------------------------
// print helper
int _nested = 0;
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
    _nested = 1;
    print(C);
    _nested = 0;
    print(list...);
}

// scan helper
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
    scan(C);
    scan(list...);
}

// fill bulk data
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
//-------------------------------------------------------------------------------

void solve()
{

    int n;
    cin >> n;
    int a[n + 1], b[n + 1], dp[n + 1][3];
    memset(a, 0, sizeof(a)), memset(b, 0, sizeof(b)), memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++)
    {
        cin >> a[i + 1] >> b[i + 1];
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            dp[i][j] = INF;
            for (int k = 0; k <= 2; k++)
            {
                if (a[i] - a[i - 1] != k - j)
                {
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + j * b[i]);
                }
            }
        }
    }
    print(min({dp[n][0], dp[n][1], dp[n][2]}));
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int _t = 1;
    cin >> _t;
    while (_t--)
        solve();
}
// cin does not move the input cursor to the next line, use cin.ignore() to move it to the next line
// use an array instead of an int whenever possible, for coding competitions