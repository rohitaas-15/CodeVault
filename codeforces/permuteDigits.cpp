/*You are given two positive integer numbers a and b. Permute (change order) of the digits of a to construct maximal number not exceeding b. No number in input and/or output can start with the digit 0.

It is allowed to leave a as it is.

Input
The first line contains integer a (1 ≤ a ≤ 1018). The second line contains integer b (1 ≤ b ≤ 1018). Numbers don't have leading zeroes. It is guaranteed that answer exists.

Output
Print the maximum possible number that is a permutation of digits of a and is not greater than b. The answer can't have any leading zeroes. It is guaranteed that the answer exists.

The number in the output should have exactly the same length as number a. It should be a permutation of digits of a.
https://codeforces.com/contest/915/problem/C*/
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
string a, b;
bool make(int index, int max, vector<int> &freq, string no)
{
    if (index == a.size())
    {
        if (no <= b)
        {
            print(no);
            return true;
        }
        return false;
    }
    // first try to put the same digit as b[index], if answer is possible, then return, else try less than b[index],
    // and set guarantee that the result will be less than b, so 10 as the max limit of character at the next index

    for (int i = min(9ll, max); i >= 0; i--)

        if (freq[i])
        {
            no += i + '0';
            freq[i]--;
            bool yes = make(index + 1, (i == max) ? b[index + 1] - '0' : 10, freq, no);
            if (yes)
            {
                return true;
            }
            no.pop_back();
            freq[i]++;
        }

    return false;
}
void solve()
{
    cin >> a >> b;
    if (b.size() > a.size())
    {
        sort(a.rbegin(), a.rend());
        print(a);
        return;
    }
    vector<int> freq(10, 0);
    for (auto i : a)
    {
        freq[i - '0']++;
    }
    make(0, b[0] - '0', freq, ""); //a and b are of same length
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