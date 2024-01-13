/*ZS the Coder and Chris the Baboon has arrived at Udayland! They walked in the park where n trees grow. They decided to be naughty and color the trees in the park. The trees are numbered with integers from 1 to n from left to right.

Initially, tree i has color ci. ZS the Coder and Chris the Baboon recognizes only m different colors, so 0 ≤ ci ≤ m, where ci = 0 means that tree i is uncolored.

ZS the Coder and Chris the Baboon decides to color only the uncolored trees, i.e. the trees with ci = 0. They can color each of them them in any of the m colors from 1 to m. Coloring the i-th tree with color j requires exactly pi, j litres of paint.

The two friends define the beauty of a coloring of the trees as the minimum number of contiguous groups (each group contains some subsegment of trees) you can split all the n trees into so that each group contains trees of the same color. For example, if the colors of the trees from left to right are 2, 1, 1, 1, 3, 2, 2, 3, 1, 3, the beauty of the coloring is 7, since we can partition the trees into 7 contiguous groups of the same color : {2}, {1, 1, 1}, {3}, {2, 2}, {3}, {1}, {3}.

ZS the Coder and Chris the Baboon wants to color all uncolored trees so that the beauty of the coloring is exactly k. They need your help to determine the minimum amount of paint (in litres) needed to finish the job.

Please note that the friends can't color the trees that are already colored.

Input
The first line contains three integers, n, m and k (1 ≤ k ≤ n ≤ 100, 1 ≤ m ≤ 100) — the number of trees, number of colors and beauty of the resulting coloring respectively.

The second line contains n integers c1, c2, ..., cn (0 ≤ ci ≤ m), the initial colors of the trees. ci equals to 0 if the tree number i is uncolored, otherwise the i-th tree has color ci.

Then n lines follow. Each of them contains m integers. The j-th number on the i-th of them line denotes pi, j (1 ≤ pi, j ≤ 109) — the amount of litres the friends need to color i-th tree with color j. pi, j's are specified even for the initially colored trees, but such trees still can't be colored.

Output
Print a single integer, the minimum amount of paint needed to color the trees. If there are no valid tree colorings of beauty k, print  - 1.
https://codeforces.com/contest/711/problem/C*/
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

void solve()
{
    int n, K, m;
    cin >> n >> m >> K;

    vector<int> color(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> color[i];

    vector<vector<int>> paint(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> paint[i][j];

    int dp[n + 1][K + 1][m + 1];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= K; j++)
            for (int l = 0; l <= m; l++)
                dp[i][j][l] = INF;

    for (int i = 0; i <= m; i++)
    {
        dp[0][0][i] = 0;
    }

    for (int j = 1; j <= K; j++) //number of splits
    {
        for (int i = 1; i <= n; i++) //treeNo.
        {
            if (!color[i])
            {
                for (int k = 1; k <= m; k++) //current tree's color
                {
                    for (int l = 0; l <= m; l++) //previous tree's color
                    {
                        if (l == k)
                        {
                            dp[i][j][k] = min(dp[i][j][k], paint[i][k] + dp[i - 1][j][l]);
                        }
                        else
                        {
                            dp[i][j][k] = min(dp[i][j][k], paint[i][k] + dp[i - 1][j - 1][l]);
                        }
                    }
                }
            }
            else
            {
                for (int l = 0; l <= m; l++) //previous tree's color
                {
                    if (l == color[i])
                    {
                        dp[i][j][color[i]] = min(dp[i][j][color[i]], dp[i - 1][j][l]);
                    }
                    else
                    {
                        dp[i][j][color[i]] = min(dp[i][j][color[i]], dp[i - 1][j - 1][l]);
                    }
                }
            }
        }
    }

    int ans = INF;
    for (int i = 1; i <= m; i++)
    {
        ans = min(ans, dp[n][K][i]);
    }
    if (ans == INF)
        ans = -1;
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