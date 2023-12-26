/*You are given a sequence of numbers a1, a2, ..., an, and a number m.

Check if it is possible to choose a non-empty subsequence aij such that the sum of numbers in this subsequence is divisible by m.

Input
The first line contains two numbers, n and m (1 ≤ n ≤ 106, 2 ≤ m ≤ 103) — the size of the original sequence and the number such that sum should be divisible by it.

The second line contains n integers a1, a2, ..., an (0 ≤ ai ≤ 109).

Output
In the single line print either "YES" (without the quotes) if there exists the sought subsequence, or "NO" (without the quotes), if such subsequence doesn't exist.
https://codeforces.com/contest/577/problem/B*/
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
const int N = 1e3 + 2;
int dp[N][N], val[N];
void solve()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
        cin >> val[i];

    if (n >= m)
    {
        print("YES");
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        dp[i][val[i-1]%m]=1;    
        for (int j = 0; j < m; j++)
        {
            dp[i][j] |= dp[i - 1][j];
            dp[i][j] |= dp[i - 1][((j - val[i - 1])%m + m) % m];
        }
    }
    print((dp[n][0]) ? "YES" : "NO");
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int _t = 1;
    // cin >> _t;
    while (_t--)
        solve();
}
// cin does not move the input cursor to the next line, use cin.ignore() to move it to the next line
// use an array instead of an int whenever possible, for coding competitions