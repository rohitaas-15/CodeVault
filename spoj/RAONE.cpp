/*In the War between good and evil . Ra-One is on the evil side and G-One on the good side.

Ra-One is fond of destroying cities and its G-one's duty to protect them..

 

Ra-One loves to destroy cities whose Zip Code has special properties. He says he loves to destroy cities which have Ra-One numbers as their Zip Code.

Any number is Ra-one if the Difference between Sum of digits at even location and Sum of digits at odd location is One (1).. For eg... for 234563 is Ra-One number

digits at odd location are 3,5,3 (unit place is location 1 )

digits at even location are 2,4,6

Diff = (2+4+6)-(3+5+3)=12-11 = 1.

And 123456 is not Ra-One number

diff = (5+3+1) - (2+4+6) = -4

 

G-One knows this about Ra-one and wants to deploy his Army members in those cities. 1 army member will be deployed in each city.

G-one knows the range of ZIP-Codes where Ra-One might attack & needs your help to find out how many army members he needs.

Can you help Him ?

Input
First line will have only one integer 't' number of Zip-Code ranges. it is followed by t lines

Each line from 2nd line contains 2 integer 'from'  and 'to'. These indicate the range of Zip codes where Ra-one might attack. ('From' and 'to' are included in the range)

NOTE:'t' will be less than 100. 'from' and 'to' will be between 0 and 10^8 inclusive.

Output
A single number for each test case telling how many army members G-One needs to deploy.

each number should be on separate lines
https://www.spoj.com/problems/RAONE/*/
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
string s;
int dp[10][2][2][50][50];
int count(int index, int last, int isEven, int evenSum, int oddSum)
{
    if (index == s.size())
    {
        return evenSum - oddSum == 1;
    }

    if (dp[index][last][isEven][evenSum][oddSum] != -1)
        return dp[index][last][isEven][evenSum][oddSum];

    int limit = (last) ? s[index] - '0' : 9;
    int ans = 0;
    for (int i = 0; i <= limit; i++)
    {
        ans += count(index + 1, last && i == limit, 1 - isEven, evenSum + isEven * i, oddSum + (1 - isEven) * i);
    }
    return dp[index][last][isEven][evenSum][oddSum] = ans;
}

int countSum(int _n)
{
    s = to_string(_n);
    memset(dp, -1ll, sizeof(dp));
    return count(0, 1, (s.size() % 2 == 0), 0, 0);
}

void solve()
{
    int a, b;
    cin >> a >> b;
    if (a == 0)
        print(countSum(b));
    else
        print(countSum(b) - countSum(a - 1));
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