/*
https://www.codingninjas.com/studio/problems/ninja-and-tree_3955708?leftPanelTabValue=SUBMISSION*/



#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
#define nl cout << endl
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)

template <typename Arg1>
void assign(Arg1 arg1, Arg1 &arg2)
{
    arg2 = arg1;
}
template <typename Arg1, typename Arg2>
void assign(Arg1 arg1, vector<Arg2> &arg2)
{
    for (Arg2 &i : arg2)
        assign(arg1, i);
}
template <typename Arg1, typename Arg2, typename... Args>
void assign(Arg1 arg1, Arg2 &arg2, Args &...args)
{
    assign(arg1, arg2);
    assign(arg1, args...);
}

int N = 2e5 + 2, tme = 0;
vector<vector<int>> adj;
vector<int> tin(N), tout(N), flat(N);

void dfs(int node, int par)
{
    tin[node] = ++tme;
    for (auto i : adj[node])
        if (i != par)
            dfs(i, node);
    tout[node] = tme;
}

struct SegmentTree
{
    vector<map<int, int>> tree;
    vector<int> lazy;

    SegmentTree(int n)
    {
        tree.resize(4 * n), lazy.resize(4 * n, -1); // lazy will contain the color
    }

    void makeTree(int ss, int se, int ti, vector<int> &flat)
    {
        if (ss > se)
            return;
        if (ss == se)
        {
            tree[ti][flat[ss]] = 1;
            return;
        }

        int mid = (ss + se) >> 1;
        makeTree(ss, mid, 2 * ti, flat), makeTree(mid + 1, se, 2 * ti + 1, flat);

        for (auto i : tree[ti * 2])
        {
            tree[ti][i.first] += i.second;
        }
        for (auto i : tree[ti * 2 + 1])
        {
            tree[ti][i.first] += i.second;
        }
    }

    void update(int ss, int se, int qs, int qe, int ti, int color)
    {
        if (lazy[ti] != -1)
        {
            int size = tree[ti].size();
            tree[ti].clear();
            tree[ti][lazy[ti]] = size;

            if (ss != se)
            {
                lazy[2 * ti] = lazy[2 * ti + 1] = lazy[ti];
            }
            lazy[ti] = -1;
        }

        if (qs > se || qe < ss)
            return;

        if (qs <= ss && qe >= se)
        {
            int size = tree[ti].size();
            tree[ti].clear(), tree[ti][color] = size;

            if (ss != se)
            {
                lazy[2 * ti] = lazy[2 * ti + 1] = color;
            }
            return;
        }

        int mid = (ss + se) >> 1;
        update(ss, mid, qs, qe, ti * 2, color), update(mid + 1, se, qs, qe, 2 * ti + 1, color);

        tree[ti].clear();
        for (auto i : tree[ti * 2])
        {
            tree[ti][i.first] += i.second;
        }
        for (auto i : tree[ti * 2 + 1])
        {
            tree[ti][i.first] += i.second;
        }
    }

    map<int, int> query(int ss, int se, int qs, int qe, int ti)
    {
        if (lazy[ti] != -1)
        {
            int size = tree[ti].size();
            tree[ti].clear();
            tree[ti][lazy[ti]] = size;

            if (ss != se)
            {
                lazy[2 * ti] = lazy[2 * ti + 1] = lazy[ti];
            }
            lazy[ti] = -1;
        }

        if (qs > se || qe < ss)
        {
            map<int, int> empty;
            return empty;
        }

        if (qs <= ss && qe >= se)
        {
            return tree[ti];
        }

        map<int, int> m1, m2, m3;

        int mid = (ss + se) >> 1;
        m1 = query(ss, mid, qs, qe, 2 * ti), m2 = query(mid + 1, se, qs, qe, 2 * ti + 1);

        for (auto i : m1)
        {
            m3[i.first] += i.second;
        }

        for (auto i : m2)
        {
            m3[i.first] += i.second;
        }
        return m3;
    }
};

vector<int> solve(int n, vector<int> a, vector<vector<int>> edges, vector<vector<int>> queries)
{
    assign(0, tin, tout, flat, tme);
    adj.clear(), adj.resize(n + 1);

    for (auto i : edges)
    {
        adj[i[0]].push_back(i[1]);
        adj[i[1]].push_back(i[0]);
    }

    dfs(1, 0);

    for (int node = 1; node <= n; node++)
    {
        flat[tin[node]] = a[node - 1];
    }

    SegmentTree tree(n + 1);
    tree.makeTree(1, n, 1, flat);
    vector<int> ans;

    for (auto i : queries)
    {
        if (i[0] == 1)
        {
            tree.update(1, n, tin[i[1]], tout[i[1]], 1, i[2]);
        }
        else
        {
            ans.push_back(tree.query(1, n, tin[i[1]], tout[i[1]], 1).size());
        }
    }
    return ans;
}