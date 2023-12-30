/*A scuba diver uses a special equipment for diving. He has a cylinder with two containers: one with oxygen and the other with nitrogen. Depending on the time he wants to stay under water and the depth of diving the scuba diver needs various amount of oxygen and nitrogen. The scuba diver has at his disposal a certain number of cylinders. Each cylinder can be described by its weight and the volume of gas it contains. In order to complete his task the scuba diver needs specific amount of oxygen and nitrogen. What is the minimal total weight of cylinders he has to take to complete the task?

Example
The scuba diver has at his disposal 5 cylinders described below. Each description consists of: volume of oxygen, volume of nitrogen (both values are given in litres) and weight of the cylinder (given in decagrams):

3 36 120
10 25 129
5 50 250
1 45 130
4 20 119
If the scuba diver needs 5 litres of oxygen and 60 litres of nitrogen then he has to take two cylinders of total weight 249 (for example the first and the second ones or the fourth and the fifth ones).

Task
Write a program that for each test case:

reads scuba diver's demand for oxygen and nitrogen, the number of accessible cylinders and their descriptions;
computes the minimal total weight of cylinders the scuba diver needs to complete his task;
outputs the result.
Note: the given set of cylinders always allows to complete the given task.

Input
The number of test cases c is in the first line of input, then c test cases follow separated by an empty line.

In the first line of a test case there are two integers t, a separated by a single space, 1 <= t <= 21 and 1 <= a <= 79. They denote volumes of oxygen and nitrogen respectively, needed to complete the task. The second line contains one integer n, 1 <= n <= 1000, which is the number of accessible cylinders. The following n lines contain descriptions of cylinders; i-th line contains three integers ti, ai, wi separated by single spaces, (1 <= ti <= 21, 1 <= ai <= 79, 1 <= wi <= 800). These are respectively: volume of oxygen and nitrogen in the i-th cylinder and the weight of this cylinder.

Output
For each test case your program should output one line with the minimal total weight of cylinders the scuba diver should take to complete the task.*/
//https://www.spoj.com/problems/SCUBADIV/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// macros-------------------------------------------------------------------------------
#define ll long long
#define int ll
#define INF 1000000000000000002ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
#define endl "\n"
int _debug = 0;
#define nl        \
    cout << endl; \
    if (_debug)   \
        cerr << endl;

// print
// helper-------------------------------------------------------------------------------
int _nested = 0;
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
const int N = 1002;
int cylo[N], cyln[N], weight[N];
void solve()
{
    int oxy, nit;
    cin >> oxy >> nit;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> cylo[i + 1] >> cyln[i + 1] >> weight[i + 1];
    }

    int dp[oxy + 2][nit + 2];
    for (int j = 0; j <= oxy + 1; j++)
    {
        for (int k = 0; k <= nit + 1; k++)
            dp[j][k] = INF;
    }

    dp[0][0] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int oi = oxy; oi >= 0; oi--)
        {
            for (int ni = nit; ni >= 0; ni--)
            {
                dp[oi][ni] = min({dp[oi][ni], dp[oi + 1][ni], dp[oi][ni + 1]});
                if (cylo[i] <= oi && cyln[i] <= ni)
                {
                    dp[oi][ni] = min(dp[oi][ni], weight[i] + dp[oi - cylo[i]][ni - cyln[i]]);
                }
            }
        }
    }

    print(dp[oxy][nit]);
}

signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    int _t = 1;
    cin >> _t;
    while (_t--)
        solve();
}

// cin does not move the input cursor to the next line, use cin.ignore() to
// move it to the next line use an array instead of an int whenever possible,
// for coding competitions
