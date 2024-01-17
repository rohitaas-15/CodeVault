/*A number is said to be a 369 number if

The count of 3s is equal to count of 6s and the count of 6s is equal to count of 9s.
The count of 3s is at least 1.
For Example 12369, 383676989, 396 all are 369 numbers whereas 213, 342143, 111 are not.

Given A and B find how many 369 numbers are there in the interval [A, B]. Print the answer modulo 1000000007.

Input

The first line contains the number of test cases (T) followed by T lines each containing 2 integers A and B.

Output

For each test case output the number of 369 numbers between A and B inclusive.

Constraints

T<=100

1<=A<=B<=10^50

Sample Input

3

121 4325

432 4356

4234 4325667

Sample Output

60

58

207159

*/
//https://www.spoj.com/problems/NUMTSN/
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
const int M = 1e9 + 7;
string s;
int dp[51][17][17][17][2];
int count369(int index, int last, int three, int six, int nine)
{
    int mx = max({three, six, nine}), mn = min({three, six, nine});

    if (max({three, six, nine}) >= 17 || mx - mn > (s.size() - index))
    {
        return 0;
    }
    if (index == s.size())
    {
        return three == six && six == nine && three > 0;
    }

    if (dp[index][three][six][nine][last] != -1)
    {
        return dp[index][three][six][nine][last];
    }
    int limit = (last) ? s[index] - '0' : 9;

    int ans = 0;

    if (limit <= 3)
    {
        ans = (ans + (limit)*count369(index + 1, 0, three, six, nine)) % M;
        ans = (ans + count369(index + 1, last && 1, three + (limit == 3), six, nine)) % M;
    }

    if (limit > 3 && limit <= 6)
    {
        ans = (ans + (limit - 1) * count369(index + 1, 0, three, six, nine)) % M;
        ans = (ans + count369(index + 1, 0, three + 1, six, nine)) % M;
        ans = (ans + count369(index + 1, last && 1, three, six + (limit == 6), nine)) % M;
    }

    if (limit > 6 && limit <= 9)
    {
        ans = (ans + (limit - 2) * count369(index + 1, 0, three, six, nine)) % M;
        ans = (ans + count369(index + 1, 0, three + 1, six, nine)) % M;
        ans = (ans + count369(index + 1, 0, three, six + 1, nine)) % M;
        ans = (ans + count369(index + 1, last && 1, three, six, nine + (limit == 9))) % M;
    }

    return dp[index][three][six][nine][last] = ans;
}
bool check369(string s)
{
    vector<int> freq(11, 0);
    for (auto i : s)
    {
        freq[i - '0']++;
    }
    return freq[3] == freq[6] && freq[6] == freq[9] && freq[3] > 0;
}
void solve()
{
    string a, b;
    cin >> a >> b;
    memset(dp, -1ll, sizeof(dp));
    s = a;
    int p1 = count369(0, 1, 0, 0, 0);
    s = b;
    memset(dp, -1ll, sizeof(dp));
    int p2 = count369(0, 1, 0, 0, 0);
    print((p2 - p1 + check369(a) + M) % M);
}

signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    cin >> _t;
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