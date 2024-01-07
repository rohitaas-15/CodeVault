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
        nl;
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
int power(int a, int b, int M = LLONG_MAX)
{
    if (!b)
        return 1;
    int sp = power(a, b / 2, M);
    sp = (sp * sp) % M;
    if (b & 1)
        return ((a % M) * sp) % M;
    else
        return sp;
}

int modularDivision(int a, int b, int M /*M should be prime*/)
{
    a %= M;
    return (a * power(b, M - 2, M)) % M;
}
void solve()
{
    string s, pattern;
    cin >> s >> pattern;
    int n = s.size(), len = pattern.size();
    int patHash = 0, checkHash = 0;
    vector<int> ans;
    for (int i = 0; i < len; i++)
    {
        checkHash = (checkHash + (s[i] - 'a') * (1ll << i)) % M;
        patHash = (patHash + (pattern[i] - 'a') * (1ll << i)) % M;
    }
    if (checkHash == patHash && s.substr(0, len) == pattern)
    {
        ans.push_back(0);
    }
    for (int i = len; i < n; i++)
    {
        checkHash = (checkHash + (s[i] - 'a') * (1ll << len)) % M;
        checkHash = (checkHash - (s[i - len] - 'a') + M) % M;
        checkHash = modularDivision(checkHash, 2, M);

        if (checkHash == patHash && s.substr(i - len + 1, len) == pattern)
        {
            ans.push_back(i - len + 1);
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