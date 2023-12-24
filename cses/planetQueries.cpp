/*You are playing a game consisting of n planets. Each planet has a teleporter to another planet (or the planet itself).
Your task is to process q queries of the form: when you begin on planet x and travel through k teleporters, which planet will you reach?
Input
The first input line has two integers n and q: the number of planets and queries. The planets are numbered 1,2,\dots,n.
The second line has n integers t_1,t_2,\dots,t_n: for each planet, the destination of the teleporter. It is possible that t_i=i.
Finally, there are q lines describing the queries. Each line has two integers x and k: you start on planet x and travel through k teleporters.
https://cses.fi/problemset/task/1750*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define INF 1000000000000000000ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
#define endl "\n"

int _DEBUG = 0;
#define nl        \
    cout << endl; \
    if (_DEBUG)   \
        cerr << endl;

//-------------------------------------------------------------------------------

// print helper
int _nested = 0;
template <typename Primitive>
void print(Primitive &&P)
{
    cout << P << " ";
    if (_DEBUG)
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
void scan(vector<Complex> &Vector)
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
    fill(Value, C), fill(Value, list...);
}

//-------------------------------------------------------------------------------

const int N = 2e5 + 2, M = 19;
int n, q;
vector<vector<int>> adj(N), cycles, Child(N, vector<int>(M, 0));
vector<int> heightFromCycle(N, INF), isCycle(N, 0), cycleIndex(N, -1), vis(N, 0), indexInCycle(N, -1), connectionToCycle(N, 0), parent(N, 0);

void makeCycles(int node, int p)
{

    if (isCycle[node])
        return;

    vis[node] = 1, parent[node] = p;

    for (auto i : adj[node])
    {
        if (!vis[i])
        {
            makeCycles(i, node);
        }
        else if (isCycle[i])
        {
            vis[node] = 2;
            return;
        }
        else if (vis[i] == 1)
        {
            // cycle

            int temp = node;
            vector<int> path;
            path.push_back(i);

            while (temp != i)
            {
                path.push_back(temp);
                temp = parent[temp];
            }

            reverse(all(path));

            int index = cycles.size();
            cycles.push_back(path);

            int cnt = 0;
            for (auto i : path)
            {
                isCycle[i] = true;
                cycleIndex[i] = index;
                indexInCycle[i] = cnt++;
            }
        }
    }
    vis[node] = 2;
}

void distanceFromCycle(int node)
{
    if (isCycle[node])
    {
        heightFromCycle[node] = 0;
        connectionToCycle[node] = node;
        return;
    }
    vis[node] = 1;

    for (auto i : adj[node])
    {
        if (!vis[i])
        {
            distanceFromCycle(i);
            heightFromCycle[node] = 1 + heightFromCycle[i];
            connectionToCycle[node] = connectionToCycle[i];
        }
        else
        {
            heightFromCycle[node] = 1 + heightFromCycle[i];
            connectionToCycle[node] = connectionToCycle[i];
        }
    }
}

int goToChild(int node, int levels)
{

    if (!levels)
        return node;

    for (int j = 0; j < M; j++)
    {
        if (levels & (1ll << j))
        {
            node = Child[node][j];
        }
    }
    return node;
}

void solve()
{
    // each connected component will contain a cycle

    cin >> n >> q;
    for (int i = 0; i < n; i++)
    {
        int tele;
        cin >> tele;
        adj[i + 1].push_back(tele);
        Child[i + 1][0] = tele;
    }

    for (int node = 1; node <= n; node++)
    {
        if (!vis[node])
            makeCycles(node, 0);
    }

    fill(0ll, vis);
    for (int node = 1; node <= n; node++)
    {
        if (!vis[node])
            distanceFromCycle(node);
    }


    vector<vector<int>> disMap(n + 1);
    for (int node = 1; node <= n; node++)
    {
        disMap[heightFromCycle[node]].push_back(node);
    }

    //reverse binary lifting to make child sparse table
    for (int height = 1; height <= n; height++)
    {
        for (auto node : disMap[height])
        {
            for (int j = 1; j < M; j++)
            {
                Child[node][j] = Child[Child[node][j - 1]][j - 1];
            }
        }
    }

    while (q--)
    {
        int x, k;
        cin >> x >> k;

        if (k <= heightFromCycle[x]) // no need to go to cycle
        {

            print(goToChild(x, k));
        }
        else // kth teleporter in cycle
        {
            int cycleStart = goToChild(x, heightFromCycle[x]);
            k -= heightFromCycle[x];
            x = cycleStart;
            int ci = cycleIndex[x], is = indexInCycle[x];
            int location = cycles[ci][(is + k) % cycles[ci].size()];
            print(location);
        }
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int _t = 1;
    // cin >> _t;
    while (_t--)
        solve();
}
// cin does not move the input cursor to the next line, use cin.ignore() to move it to the next line