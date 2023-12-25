/*You are given an integer array 𝑎1,𝑎2,…,𝑎𝑛
.

The array 𝑏
 is called to be a subsequence of 𝑎
 if it is possible to remove some elements from 𝑎
 to get 𝑏
.

Array 𝑏1,𝑏2,…,𝑏𝑘
 is called to be good if it is not empty and for every 𝑖
 (1≤𝑖≤𝑘
) 𝑏𝑖
 is divisible by 𝑖
.

Find the number of good subsequences in 𝑎
 modulo 109+7
.

Two subsequences are considered different if index sets of numbers included in them are different. That is, the values ​of the elements ​do not matter in the comparison of subsequences. In particular, the array 𝑎
 has exactly 2𝑛−1
 different subsequences (excluding an empty subsequence).

Input
The first line contains an integer 𝑛
 (1≤𝑛≤100000
) — the length of the array 𝑎
.

The next line contains integers 𝑎1,𝑎2,…,𝑎𝑛
 (1≤𝑎𝑖≤106
).

Output
Print exactly one integer — the number of good subsequences taken modulo 109+7
.https://codeforces.com/problemset/problem/1061/C*/

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

const int N = 1e6 + 2, M = 1e9 + 7;
int dp[N], seen[N];
vector<vector<int>> divisors(N);

void solve()
{
    int n;
    cin >> n;
    vector<int> v(n);
    scan(v);

    for (auto i : v)
    {
        for (int j = 1; j * j <= i && !seen[i]; j++)
        {
            if (i % j == 0)
            {
                divisors[i].push_back(j);
                if (j != i / j)
                {
                    divisors[i].push_back(i / j);
                }
            }
        }
        seen[i]++;
    }

    for (int div = 1; div <= 1e6; div++)
    {
        sort(divisors[div].rbegin(), divisors[div].rend()); // so that answer for a particuar divisore doesnt get changed in one iteration
    }

    // dp[i]=number of subsequences till now with length i

    dp[0] = 1;

    int ans = 0;

    for (int len = 1; len <= n; len++) // answer if last index of subsequence is len-1
    {
        for (auto j : divisors[v[len - 1]])
        {
            dp[j] = (dp[j] + dp[j - 1]) % M;
            ans = (ans + dp[j - 1]) % M;
        }
    }
    print(ans);
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