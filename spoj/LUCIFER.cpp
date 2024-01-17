/*Lucifer is the only human who has defeated RA-ONE in a computer game ...

RA-One is after lucifer for revenge and G-One is there to protect him ...

All thi G-One and Ra-one Nonsense has disturbed Lucifer's life ...

He wants to get Rid of Ra-One and kill him . He found that Ra-One can be killed only by throwing Lucifer number of weapons at him.

Lucifer number shares the some properties of Ra-One Numbers numbers and G-One Numbers

Any number is LUCIFER NUMBER if the difference between sum of digits at even location and sum of digits at odd location is prime number. For example, 20314210 is a Lucifer number:

digits at odd location 0, 2, 1, 0.

digits at even location 1, 4, 3, 2.

difference = (1+4+3+2)-(0+2+1+0) = 10-3 = 7 ... a prime number.

Lucifer has access to a Warehouse which has lots of weapons. He wants to know in how many ways can he kill him.

Can you help him?

Input
First line will have a number 't' denoting the number of test cases.

each of the following t lines will have 2 numbers 'a', 'b'

Output
Print single number per test case, depicting the count of Lucifer numbers in the range a, b inclusive.*/
//https://www.spoj.com/problems/LUCIFER/
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
        int no = evenSum - oddSum;
        if (no <= 1)
            return 0;
        for (int i = 2; i * i <= no; i++)
        {
            if (no % i == 0)
                return 0;
        }
        return 1;
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