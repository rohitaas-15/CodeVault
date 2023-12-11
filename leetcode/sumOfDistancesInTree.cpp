/*There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.

You are given the integer n and the array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.

Return an array answer of length n where answer[i] is the sum of the distances between the ith node in the tree and all other nodes.

https://leetcode.com/problems/sum-of-distances-in-tree/description/
*/

#include <bits/stdc++.h>
using namespace std;
#define nl cout << endl

//-------------------------------------------------------------------------------

// print helper
int _nested = 0;
template <typename Primitive>
void print(Primitive &&P)
{
    cout << P << " ";
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
    _nested = 1;
    print(C);
    _nested = 0;
    print(list...);
}

// scan helper
template <typename Primitive>
void scan(Primitive &P)
{
    cin >> P;
}
template <typename Complex>
void scan(vector<Complex> Vector)
{
    for (Complex &C : Vector)
        scan(C);
}
template <typename Complex, typename... ComplexObjects>
void scan(Complex &C, ComplexObjects &...list)
{
    scan(C);
    scan(list...);
}

// fill bulk data
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
    fill(Value, C);
    fill(Value, list...);
}

//-------------------------------------------------------------------------------

int N = 3e4 + 2;
vector<vector<int>> adj;
vector<int> dp(N);
vector<int> subSize(N), ans;

void dfs(int node, int par)
{
    int ans = 0, sz = 1;

    for (auto i : adj[node])
        if (i != par)
        {
            dfs(i, node);
            ans += dp[i] + subSize[i];
            sz += subSize[i];
        }
    subSize[node] = sz, dp[node] = ans;
}

void reRoot(int node, int par)
{
    ans[node] = dp[node];

    for (auto i : adj[node])
        if (i != par)
        {
            // cut the edge

            dp[node] -= (subSize[i] + dp[i]);
            subSize[node] -= subSize[i];

            dp[i] += (dp[node] + subSize[node]);
            subSize[i] += subSize[node];

            reRoot(i, node);

            // backtrack

            dp[i] -= (dp[node] + subSize[node]);
            subSize[i] -= subSize[node];

            dp[node] += (subSize[i] + dp[i]);
            subSize[node] += subSize[i];
        }
}

class Solution
{
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>> &edges)
    {
        fill(0, dp, subSize);
        adj.clear(), adj.resize(n + 1);
        ans.clear(), ans.resize(n);
        fill(0, ans);

        for (auto i : edges)
        {
            adj[i[0]].push_back(i[1]);
            adj[i[1]].push_back(i[0]);
        }

        dfs(0, 0);
        reRoot(0, 0);

        return ans;
    }
};