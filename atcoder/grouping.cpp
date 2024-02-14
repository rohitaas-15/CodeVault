/*There are
N rabbits, numbered
1,2,…,N.

For each
i,j (
1≤i,j≤N), the compatibility of Rabbit
i and
j is described by an integer
a
i,j
​
 . Here,
a
i,i
​
 =0 for each
i (
1≤i≤N), and
a
i,j
​
 =a
j,i
​
  for each
i and
j (
1≤i,j≤N).

Taro is dividing the
N rabbits into some number of groups. Here, each rabbit must belong to exactly one group. After grouping, for each
i and
j (
1≤i<j≤N), Taro earns
a
i,j
​
  points if Rabbit
i and
j belong to the same group.

Find Taro's maximum possible total score.

Constraints
All values in input are integers.
1≤N≤16
∣a
i,j
​
 ∣≤10
9

a
i,i
​
 =0
a
i,j
​
 =a
j,i
​https://atcoder.jp/contests/dp/tasks/dp_u
*/
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

const int N = 18;
int matrix[N][N];
int score[1ll << N];
vector<int> dp(1ll << N, -INF);
int n;
void calcScore(int index, int mask, int sc)
{
    if (index == n)
    {
        score[mask] = sc;
        return;
    }

    int add = 0;
    for (int i = 0; i < n; i++)
    {
        if (mask & (1ll << i))
        {
            add += matrix[i][index];
        }
    }
    calcScore(index + 1, mask | (1ll << index), sc + add);
    calcScore(index + 1, mask, sc);
}
vector<int> subs;
void makeSubsets(int index, int mask, int make) //make subsets of remaining rabbits
{
    if (index == n)
    {
        if (make)
            subs.push_back(make);
        return;
    }

    if (((1ll << index) & mask) == 0)
    {
        makeSubsets(index + 1, mask, make | ((1ll << index)));
    }
    makeSubsets(index + 1, mask, make);
}

int answer(int mask) //calculate the answer when a particular subset of rabbits are remaining
{
    if (mask == ((1ll << n) - 1))
    {
        return 0;
    }

    if (dp[mask] != -INF)
        return dp[mask];

    int ans = 0;
    subs.clear();
    makeSubsets(0, mask, 0);
    for (auto i : subs)
    {

        ans = max(ans, score[i] + answer(mask | i));
    }
    return dp[mask] = ans;
}
void solve()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> matrix[i][j];
        }
    calcScore(0, 0, 0);
    print(answer(0));
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