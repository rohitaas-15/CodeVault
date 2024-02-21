/*The only difference between easy and hard versions is the constraints.

Vova likes pictures with kittens. The news feed in the social network he uses can be represented as an array of 𝑛
 consecutive pictures (with kittens, of course). Vova likes all these pictures, but some are more beautiful than the others: the 𝑖
-th picture has beauty 𝑎𝑖
.

Vova wants to repost exactly 𝑥
 pictures in such a way that:

each segment of the news feed of at least 𝑘
 consecutive pictures has at least one picture reposted by Vova;
the sum of beauty values of reposted pictures is maximum possible.
For example, if 𝑘=1
 then Vova has to repost all the pictures in the news feed. If 𝑘=2
 then Vova can skip some pictures, but between every pair of consecutive pictures Vova has to repost at least one of them.

Your task is to calculate the maximum possible sum of values of reposted pictures if Vova follows conditions described above, or say that there is no way to satisfy all conditions.

Input
The first line of the input contains three integers 𝑛,𝑘
 and 𝑥
 (1≤𝑘,𝑥≤𝑛≤5000
) — the number of pictures in the news feed, the minimum length of segment with at least one repost in it and the number of pictures Vova is ready to repost.

The second line of the input contains 𝑛
 integers 𝑎1,𝑎2,…,𝑎𝑛
 (1≤𝑎𝑖≤109
), where 𝑎𝑖
 is the beauty of the 𝑖
-th picture.

Output
Print -1 if there is no way to repost some pictures to satisfy all the conditions in the problem statement.

Otherwise print one integer — the maximum sum of values of reposted pictures if Vova follows conditions described in the problem statement.


https://codeforces.com/contest/1077/problem/F2*/
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

struct SegmentTree
{
    vector<int> tree;
    SegmentTree(int n)
    {
        tree.clear(), tree.resize(4 * n, 0ll);
    }

    void build(int ss, int se, int ti, vector<int> &dp)
    {
        if (ss == se)
        {
            tree[ti] = dp[ss];
            return;
        }

        int mid = (ss + se) / 2;
        build(ss, mid, ti * 2 + 1, dp), build(mid + 1, se, ti * 2 + 2, dp);
        tree[ti] = max(tree[ti * 2 + 1], tree[ti * 2 + 2]);
    }

    void update(int ss, int se, int ti, int index, int val)
    {
        if (ss > index || se < index)
        {
            return;
        }

        if (ss == se && ss == index)
        {
            tree[ti] = val;
            return;
        }

        int mid = (ss + se) / 2;
        update(ss, mid, ti * 2 + 1, index, val), update(mid + 1, se, ti * 2 + 2, index, val);
        tree[ti] = max(tree[ti * 2 + 1], tree[ti * 2 + 2]);
    }
    int query(int ss, int se, int qs, int qe, int ti)
    {
        if (qs > qe)
            return 0;
        if (qs > se || qe < ss)
        {
            return -1;
        }

        if (qs <= ss && qe >= se)
        {
            return tree[ti];
        }

        int mid = (ss + se) / 2;
        return max(query(ss, mid, qs, qe, ti * 2 + 1), query(mid + 1, se, qs, qe, ti * 2 + 2));
    }
};

void solve()
{
    int n, k, x;
    cin >> n >> k >> x;

    vector<vector<int>> dp(x + 1, vector<int>(n + 1, -1));
    int beauty[n + 1];
    for (int i = 0; i < n; i++)
    {
        cin >> beauty[i];
    }

    dp[0][0] = 0;

    SegmentTree prev(n + 1);
    prev.build(0, n, 0, dp[0]);
    for (int pic = 1; pic <= x; pic++)
    {
        for (int i = n; i >= pic; i--) // segment tree 0....i-1 will contain dp values from previous x
        {
            // take the current picture
            int start = max(0ll, i - k);
            int end = i - 1;
            int query = prev.query(0, n, start, end, 0); //max query for dp[x-1][i-k]......dp[x-1][i-1]
            if (query != -1)
            {
                dp[pic][i] = beauty[i - 1] + query;
            }
            prev.update(0, n, 0, i, dp[pic][i]);
        }
    }

    int ans = -1;
    for (int i = n - k + 1; i <= n; i++)
    {
        if (dp[x][i] != -1)
            ans = max(ans, dp[x][i]);
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