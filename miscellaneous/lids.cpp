/*We all know about LIS (Longest Increasing Sub sequence). The task to find the length of the longest increasing sub sequence in a given array of integers is very easy. For example, the length of the LIS for 
{
15
,
27
,
14
,
38
,
26
,
55
,
46
,
65
,
85
}
{15,27,14,38,26,55,46,65,85} is 6 and the longest increasing sub sequence is 
{
15
,
27
,
38
,
55
,
65
,
85
}
{15,27,38,55,65,85}.

But, do we all know about LIDS? The task to find the length of the longest increasing digit sub sequence within an integer is known as LIDS. For example, length of LIDS for 1234 is 4, length of LIDS for 12234 is 4, length of LIDS for 456123 is 3. 
{
7
}
{7}, 
{
1
,
4
,
9
}
{1,4,9}, 
{
5
,
9
}
{5,9} are some valid increasing digit sequence while 
{
3
,
2
}
{3,2}, 
{
1
,
1
}
{1,1}, 
{
4
,
9
,
1
}
{4,9,1} are invalid.

You are given two integers x and y. You have to answer maximum length of LIDS between x and y inclusive and the number of different ways maximum LIDS can be formed. Two ways are considered different if the longest increasing digit sequence are not same or they are chosen from different position in an integer.

Input
Input starts with an integer 
�
T (
�
≤
10000
T≤10000), denoting the number of test cases. Each of the test cases consists of two space separated integers 
�
x and 
�
y denoting the range.

Easy subtask: 
1
≤
�
≤
�
<
1000
1≤x≤y<1000

Medium subtask: 
1
≤
�
≤
�
≤
1000
,
000
,
000
1≤x≤y≤1000,000,000 and 
(
�
−
�
)
≤
1000
(y−x)≤1000

Hard subtask: 
1
≤
�
≤
�
≤
1000
,
000
,
000
1≤x≤y≤1000,000,000

Digits are: 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9.

Output
For each of the test cases, you need to print one line of output. The output for each test case starts with the test case number, followed by Maximum Length of LIDS and the number of ways LIDS can be formed. You must output as it is given in the sample output section.
https://toph.co/p/lids*/
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

string s1, s2;
int dp[11][2][2][2][11], dpCount[11][2][2][2][11][11];
int calculate(int index, int zero, int left, int right, int prev)
{
    if (index == s2.size())
    {
        return 0;
    }

    if (dp[index][left][zero][right][prev + 1] != -1)
    {
        return dp[index][left][zero][right][prev + 1];
    }

    int ans = 0;
    int start = (left) ? s1[index] - '0' : 0;
    int end = (right) ? s2[index] - '0' : 9;

    for (int i = start; i <= end; i++)
    {
        ans = max(ans, calculate(index + 1, zero && i == 0, left && i == start, right && i == end, prev));
        if ((i == 0 && !zero && i > prev) || (i > 0 && i > prev))
        {
            ans = max(ans, 1 + calculate(index + 1, zero && i == 0, left && i == start, right && i == end, i));
        }
    }
    return dp[index][left][zero][right][prev + 1] = ans;
}
int calculate(int _a, int _b)
{
    s1 = to_string(_a), s2 = to_string(_b);
    reverse(all(s1));
    while (s1.size() != s2.size())
    {
        s1 += '0';
    }
    reverse(all(s1));

    memset(dp, -1ll, sizeof(dp));
    return calculate(0, 1, 1, 1, -1);
}

int count(int index, int zero, int left, int right, int prev, int rem)
{
    if (index == s2.size())
    {
        return rem == 0;
    }

    if (dpCount[index][zero][left][right][prev + 1][rem] != -1)
    {
        return dpCount[index][zero][left][right][prev + 1][rem];
    }

    int ans = 0, nans = 0;
    int start = (left) ? s1[index] - '0' : 0;
    int end = (right) ? s2[index] - '0' : 9;

    for (int i = start; i <= end; i++)
    {
        ans += count(index + 1, zero && i == 0, left && i == start, right && i == end, prev, rem);
        if ((i == 0 && !zero && i > prev) || (i > 0 && i > prev))
        {
            ans += count(index + 1, 0, left && i == start, right && i == end, i, rem - 1);
        }
    }
    return dpCount[index][zero][left][right][prev + 1][rem] = ans;
}

int count(int _a, int _b, int lids)
{
    s1 = to_string(_a), s2 = to_string(_b);
    reverse(all(s1));
    while (s1.size() != s2.size())
    {
        s1 += '0';
    }
    reverse(all(s1));

    memset(dpCount, -1ll, sizeof(dpCount));
    return count(0, 1, 1, 1, -1, lids);
}

void solve()
{
    int a, b;
    cin >> a >> b;
    int lids = calculate(a, b);
    cout << lids << " " << count(a, b, lids) << endl;
}

signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    cin >> _t;
    for (int tc = 1; tc <= _t; tc++)
    {
        cout << "Case " << tc << ":"
             << " ";
        solve();
    }
}

// cin does not move the input cursor to the next line, use cin.ignore() to
// move it to the next line use an array instead of an int whenever possible,
// for coding competitions