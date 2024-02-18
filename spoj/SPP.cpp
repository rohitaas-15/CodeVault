/*
Sequence (ai) of natural numbers is defined as follows:

ai = bi (for i <= k)
ai = c1ai-1 + c2ai-2 + ... + ckai-k (for i > k)

where bj and cj are given natural numbers for 1<=j<=k. Your task is to compute am + am+1 + am+2 + ... + an for given m <= n and output it modulo a given positive integer p.

Input
On the first row there is the number C of test cases (equal to about 50).
Each test contains four lines:
k - number of elements of (c) and (b) (1 <= k <= 15)
b1, ... bk - k natural numbers where 0 <= bj <= 109 separated by spaces.
c1, ... ck - k natural numbers where 0 <= cj <= 109 separated by spaces.
m, n, p - natural numbers separated by spaces (1 <= m <= n <= 1018, 1<= p <= 108).
Output
Exactly C lines, one for each test case: (am + am+1 + am+2 + ... + an) modulo p.
https://www.spoj.com/problems/SPP/*/

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
int k, M;
vector<int> b, c;
struct Matrix
{
    vector<vector<int>> mat;
    Matrix()
    {
        mat.resize(k + 1, vector<int>(k + 1, 0));
    }

    void identity()
    {
        for (int i = 0; i <= k; i++)
        {
            mat[i][i] = 1;
        }
    }

    Matrix operator*(Matrix T)
    {
        Matrix ans;
        for (int i = 0; i <= k; i++)
        {
            for (int j = 0; j <= k; j++)
            {
                for (int l = 0; l <= k; l++)
                {
                    ans.mat[i][j] = (ans.mat[i][j] + mat[i][l] * T.mat[l][j]) % M;
                }
            }
        }
        return ans;
    }
};

int S(int n)
{
    if (n == 0)
        return 0;

    vector<int> S_k(k + 1, 0);
    for (int i = 0; i < k; i++)
    {
        S_k[i + 1] = (S_k[i] + b[i]) % M;
    }

    if (n <= k)
        return S_k[n];

    Matrix shift;

    shift.mat[0][0] = 1;
    for (int i = 1; i <= k; i++)
    {
        shift.mat[0][i] = c[i - 1];
        shift.mat[1][i] = c[i - 1];
    }

    for (int i = 2; i <= k; i++)
    {
        shift.mat[i][i - 1] = 1;
    }

    Matrix ans;
    ans.identity();

    n -= k;
    while (n) //matrix exponentiation
    {
        if (n & 1)
            ans = ans * shift;
        shift = shift * shift;
        n >>= 1;
    }

    int answer = 0;

    for (int i = 0; i <= k; i++)
    {
        if (!i)
        {
            answer = (answer + (S_k[k] * ans.mat[0][i]) % M) % M;
        }
        else
            answer = (answer + (b[k - i] * ans.mat[0][i]) % M) % M;
    }

    return answer;
}

void solve()
{
    int n, m;
    cin >> k;

    b.clear(), b.resize(k + 1);
    c.clear(), c.resize(k + 1);

    for (int i = 0; i < k; i++)
    {
        cin >> b[i];
    }
    for (int i = 0; i < k; i++)
    {
        cin >> c[i];
    }

    cin >> m >> n >> M;
    print((S(n) - S(m - 1) + M) % M);
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