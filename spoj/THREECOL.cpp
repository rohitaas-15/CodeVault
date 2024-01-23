/*A tree consists of a node and some (zero, one or two) subtrees connected to it. These subtrees are called children.

A specification of the tree is a sequence of digits. If the number of children in the tree is:

zero, then the specification is a sequence with only one element '0';
one, the specification begins with '1' followed by the specification of the child;
two, the specification begins with '2' followed by the specification of the first child, and then by the specification of the second child.
Each of the vertices in the tree must be painted either red or green or blue.
However, we need to obey the following rules:

the vertex and its child cannot have the same color,
if a vertex has two children, then they must have different colors.
How many vertices may be painted green?

Task

Write a program which:

reads the specification of the tree from the standard input,
computes the maximal and the minimal number of vertices that may be painted green,
writes the results in the standard output.
Input

The number of test cases t is in the first line of input, then t test cases follow in separate lines. Each test case consists of one word (no longer then 10000 characters), which is a specification of a tree.

Output

Your program should write for each test case exactly two integers separated by a single space, which respectively denote the maximal and the minimal number of vertices that may be painted green.
https://www.spoj.com/problems/THREECOL/*/
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
const int N = 1e5 + 2;
vector<vector<int>> adj;
string s;
void makeTree(int &counter, int parent)
{
    if (counter == s.size())
        return;
    if (s[counter] == '0')
    {
        adj[parent].push_back(counter + 1);
        counter++;
        return;
    }

    if (s[counter] == '1')
    {
        adj[parent].push_back(counter + 1);
        int curNode = counter + 1;
        counter++;
        makeTree(counter, curNode);
    }
    else
    {
        adj[parent].push_back(counter + 1);
        int curNode = counter + 1;
        counter++;
        makeTree(counter, curNode); // leftSubstree
        makeTree(counter, curNode); // right subtree
    }
}
int dp[N][3];
int dfsMax(int node, int color)
{
    int ans = (color == 1);

    if (adj[node].size() == 0)
    {
        return ans;
    }

    if (dp[node][color] != -1)
    {
        return dp[node][color];
    }

    if (adj[node].size() == 1)
    {
        int sans = 0;
        for (int i = 0; i < 3; i++)
        {
            if (i != color)
            {
                sans = max(sans, dfsMax(adj[node][0], i));
            }
        }
        return dp[node][color] = ans + sans;
    }

    if (adj[node].size() == 2)
    {
        vector<int> colors;
        for (int i = 0; i < 3; i++)
            if (i != color)
                colors.push_back(i);

        int sans = 0;
        sans = max(sans, dfsMax(adj[node][0], colors[0]) + dfsMax(adj[node][1], colors[1]));
        sans = max(sans, dfsMax(adj[node][0], colors[1]) + dfsMax(adj[node][1], colors[0]));
        return dp[node][color] = sans + ans;
    }
}

int dfsMin(int node, int color)
{
    int ans = (color == 1);

    if (adj[node].size() == 0)
    {
        return ans;
    }

    if (dp[node][color] != -1)
    {
        return dp[node][color];
    }

    if (adj[node].size() == 1)
    {
        int sans = INF;
        for (int i = 0; i < 3; i++)
        {
            if (i != color)
            {
                sans = min(sans, dfsMin(adj[node][0], i));
            }
        }
        return dp[node][color] = ans + sans;
    }

    if (adj[node].size() == 2)
    {
        vector<int> colors;
        for (int i = 0; i < 3; i++)
            if (i != color)
                colors.push_back(i);

        int sans = INF;
        sans = min(sans, dfsMin(adj[node][0], colors[0]) + dfsMin(adj[node][1], colors[1]));
        sans = min(sans, dfsMin(adj[node][0], colors[1]) + dfsMin(adj[node][1], colors[0]));
        return dp[node][color] = sans + ans;
    }
}

void solve()
{
    cin >> s;
    adj.clear();
    adj.resize(N);
    int counter = 0;
    makeTree(counter, 0);

    memset(dp, -1, sizeof(dp));
    int mx = 0;
    for (int i = 0; i < 3; i++)
    {
        mx = max(mx, dfsMax(1, i));
    }

    memset(dp, -1, sizeof(dp));
    int mn = INF;
    for (int i = 0; i < 3; i++)
    {
        mn = min(mx, dfsMin(1, i));
    }

    print(mx, mn);
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
