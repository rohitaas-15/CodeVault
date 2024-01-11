/*You are given an integer array of length 𝑛
.

You have to choose some subsequence of this array of maximum length such that this subsequence forms a increasing sequence of consecutive integers. In other words the required sequence should be equal to [𝑥,𝑥+1,…,𝑥+𝑘−1]
 for some value 𝑥
 and length 𝑘
.

Subsequence of an array can be obtained by erasing some (possibly zero) elements from the array. You can erase any elements, not necessarily going successively. The remaining elements preserve their order. For example, for the array [5,3,1,2,4]
 the following arrays are subsequences: [3]
, [5,3,1,2,4]
, [5,1,4]
, but the array [1,3]
 is not.

Input
The first line of the input containing integer number 𝑛
 (1≤𝑛≤2⋅105
) — the length of the array. The second line of the input containing 𝑛
 integer numbers 𝑎1,𝑎2,…,𝑎𝑛
 (1≤𝑎𝑖≤109
) — the array itself.

Output
On the first line print 𝑘
 — the maximum length of the subsequence of the given array that forms an increasing sequence of consecutive integers.

On the second line print the sequence of the indices of the any maximum length subsequence of the given array that forms an increasing sequence of consecutive integers.*/
//https://codeforces.com/contest/977/problem/F
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
const int N = 2e5 + 2;

void solve()
{
    int n;
    cin >> n;
    vector<int> v(n);
    scan(v);

    int dp[N], optimal[N];
    memset(dp, 0, sizeof(dp));
    memset(optimal, 0, sizeof(optimal));
    map<int, int> bestAns; // stores the indices of best answer till a particular number
    for (int i = 1; i <= n; i++)
    {
        int no = v[i - 1];
        dp[i] = dp[bestAns[no - 1]] + 1;
        optimal[i] = bestAns[no - 1];
        bestAns[no] = i;
    }

    int mx = 0, index = 0;
    for (int i = 1; i <= n; i++)
    {
        if (mx < dp[i])
        {
            index = i, mx = dp[i];
        }
    }

    vector<int> ans;
    while (index != 0)
    {
        ans.push_back(index);
        index = optimal[index];
    }
    reverse(all(ans));
    print(mx);
    print(ans);
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