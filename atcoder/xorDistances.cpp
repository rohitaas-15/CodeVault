/*https://atcoder.jp/contests/abc201/tasks/abc201_e*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define INF 1000000000000000000ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
#define endl "\n"
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

int N = 2e5 + 2, M = 1e9 + 7;

int twoInverse;

int power(int a, int b)
{
    if (!b)
        return 1;
    if (b == 1)
        return a % M;

    int sp = power(a, b / 2);
    return (((sp * sp) % M) * power(a, b % 2)) % M;
}

vector<vector<pair<int, int>>> adj(N);
pair<int, int> dfs(int node, int par, int &ans)
{
    int even = 0, odd = 0;
    vector<pair<int, int>> paths;

    for (auto i : adj[node])
    {
        if (i.first != par)
        {
            auto p = dfs(i.first, node, ans);

            if (i.second == 1)
            {
                swap(p.second, p.first);
            }
            paths.push_back(p);
            ans = (ans + p.second) % M;
            even = (even + p.first) % M, odd = (odd + p.second) % M;
        }
    }

    int sans = 0;

    for (auto i : paths)
    {
        sans = (sans + (i.first * (odd - i.second + M) % M) % M + (i.second * (even - i.first + M) % M) % M) % M;
    }
    sans = (sans * twoInverse) % M;
    ans = (ans + sans) % M;
    return {even + 1, odd};
}

void solve()
{

    twoInverse = power(2, M - 2);
    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++)
    {
        int x, y, z;
        scan(x, y, z);
        adj[x].push_back({y, z});
        adj[y].push_back({x, z});
    }

    auto temp = adj;
    int mans = 0;
    for (int p2 = 0; p2 <= 61; p2++)
    {
        int mask = 1ll << p2;
        adj = temp;

        for (auto &i : adj)
        {
            for (auto &j : i)
            {
                j.second = ((j.second & mask) > 0ll);
            }
        }
        int tempans = 0;
        dfs(1, 0, tempans);
        mans = (mans + (((1ll << p2) % M) * tempans) % M) % M;
    }

    print(mans);
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
