/*Innokenty works at a flea market and sells some random stuff rare items. Recently he found an old rectangular blanket. It turned out that the blanket is split in 𝑛⋅𝑚
 colored pieces that form a rectangle with 𝑛
 rows and 𝑚
 columns.

The colored pieces attracted Innokenty's attention so he immediately came up with the following business plan. If he cuts out a subrectangle consisting of three colored stripes, he can sell it as a flag of some country. Innokenty decided that a subrectangle is similar enough to a flag of some country if it consists of three stripes of equal heights placed one above another, where each stripe consists of cells of equal color. Of course, the color of the top stripe must be different from the color of the middle stripe; and the color of the middle stripe must be different from the color of the bottom stripe.

Innokenty has not yet decided what part he will cut out, but he is sure that the flag's boundaries should go along grid lines. Also, Innokenty won't rotate the blanket. Please help Innokenty and count the number of different subrectangles Innokenty can cut out and sell as a flag. Two subrectangles located in different places but forming the same flag are still considered different.
https://codeforces.com/contest/1181/problem/C*/
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
const int N = 1001;
char mat[N][N];
void solve()
{
    int n, m;
    cin >> n >> m;

    int col[n + 1][m + 1], upper_col[n + 1][m + 1], end_of_upper_col[n + 1][m + 1]; //color of current cell, upper color of this cell, last index of upper color
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> mat[i][j];
            col[i][j] = mat[i][j] - 'a' + 1;
        }
    }

    memset(upper_col, 0, sizeof(upper_col));
    memset(end_of_upper_col, 0, sizeof(end_of_upper_col));

    for (int j = 1; j <= m; j++)
    {
        int index = 0, prev = 0;
        for (int i = 1; i <= n - 1; i++)
        {
            upper_col[i][j] = prev, end_of_upper_col[i][j] = index;
            if (col[i][j] != col[i + 1][j])
            {
                prev = col[i][j], index = i;
            }
        }
        upper_col[n][j] = prev, end_of_upper_col[n][j] = index;
    }

    int dp[n + 1][m + 1];
    memset(dp, 0, sizeof(dp));
    int ans = 0;
    for (int j = 1; j <= m; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            int problem = 0, len, ci = i, range = 0;
            for (int cnt = 0; cnt <= 1; cnt++)
            {
                len = ci - end_of_upper_col[ci][j];
                int ni = end_of_upper_col[ci][j], newLen = ni - end_of_upper_col[ni][j];
                if (!cnt) //comparing bottom 2 flag colors
                {
                    if (newLen == len && col[ci][j] != col[ni][j])
                    {
                        ci = ni;
                    }
                    else
                    {
                        problem = 1;
                        break;
                    }
                }
                else //comparing upper 2 flag colors
                {
                    if (newLen >= len && col[ci][j] != col[ni][j])
                    {
                        ci = ni;
                    }
                    else
                    {
                        problem = 1;
                        break;
                    }
                }
            }
            if (!problem)
            {
                dp[i][j] = 1;
            }

            ci = i;
            for (int cnt = 0; cnt <= 1; cnt++)
            {
                //comparing current column and previous column
                if (col[ci][j] == col[ci][j - 1] && upper_col[ci][j] == upper_col[ci][j - 1] && end_of_upper_col[ci][j] == end_of_upper_col[ci][j - 1])
                {
                    ci = end_of_upper_col[ci][j];
                }
                else
                {
                    problem = 1;
                    break;
                }
            }
            if (!problem)
            {
                dp[i][j] += dp[i][j - 1];
            }
            ans += dp[i][j];
        }
    }
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