/*Time limit: 1.00 s
Memory limit: 512 MB



Uolevi has won a contest, and the prize is a free flight trip that can consist of one or more flights through cities. Of course, Uolevi wants to choose a trip that has as many cities as possible.
Uolevi wants to fly from Syrjälä to Lehmälä so that he visits the maximum number of cities. You are given the list of possible flights, and you know that there are no directed cycles in the flight network.
Input
The first input line has two integers n and m: the number of cities and flights. The cities are numbered 1,2,\dots,n. City 1 is Syrjälä, and city n is Lehmälä.
After this, there are m lines describing the flights. Each line has two integers a and b: there is a flight from city a to city b. Each flight is a one-way flight.
Output
First print the maximum number of cities on the route. After this, print the cities in the order they will be visited. You can print any valid solution.
If there are no solutions, print "IMPOSSIBLE".
Constraints

2 \le n \le 10^5
1 \le m \le 2 \cdot 10^5
1 \le a,b \le n
https://cses.fi/problemset/task/1680/*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define INF 1000000000000000000ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
#define endl "\n"
#define nl cerr << endl, cout << endl

//-------------------------------------------------------------------------------
// print helper
int _nested = 0;
template <typename Primitive>
void print(Primitive &&P)
{
    cerr << P << " ";
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
void scan(Primitive &P) { cin >> P; }
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
void fill(Primitive Value, Primitive &P) { P = Value; }
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

const int N = 1e5 + 2;
int n, m;
vector<vector<int>> adj(N);
vector<int> vis(N, 0), canReach(N, 0); //store if can reach n from i
vector<pair<int, int>> height(N, {1, -1}); //store the max height and child from which max height is coming

int mx = 0;

bool canReachFrom(int node)
{
    if (node == n)
    {
        canReach[n] = 1;
        return true;
    }
    vis[node] = 1;

    int h = 1, child = -1, yes = 0;
    for (auto i : adj[node])
    {
        if (!vis[i])
        {
            if (canReachFrom(i) && 1 + height[i].first > h)
            {
                h = 1 + height[i].first;
                child = i;
            }
        }
        else
        {
            if (canReach[i] && 1 + height[i].first > h)
            {
                h = 1 + height[i].first;
                child = i;
            }
        }
        yes = yes || canReach[i];
    }
    height[node] = {h, child};
    canReach[node] = yes;
    return canReach[node];
}

void solve()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
    }

    if (canReachFrom(1) && mx < height[1].first)
    {
        mx = height[1].first;
    }

    if (!mx)
        print("IMPOSSIBLE"), exit(0);

    int temp = 1;
    vector<int> path;
    while (temp != -1)
    {
        path.push_back(temp);
        temp = height[temp].second;
    }
    print(path.size());
    print(path);
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