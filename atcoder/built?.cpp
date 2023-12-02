//https://atcoder.jp/contests/arc076/tasks/arc076_b
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define endl "\n"
#define pii pair<int, int>
#define vi vector<int>
#define vvi vector<vi>
#define pb push_back
#define F first
#define S second
#define sz(x) x.size()
#define vpii vector<pii>
#define vvpii vector<vector<pii>>
#define rev(x) reverse(x.begin(), x.end())
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)

void print(int x);
void print(int x, int y);
void print(int x, int y, int z);
void print(string x);
void print(char x);
void print(float x);
void print(vi x);
void print(vvi x);
void read(int &x);
void read(int &x, int &y);
void read(int &x, int &y, int &z);
void read(string &s);
void read(char &c);
void read(float &x);
void read(vi &x, int n);
void read(vvi &x, int n, int m);

#define bug(...) __f(#__VA_ARGS__, __VA_ARGS__)

template <typename Arg1>
void __f(const char *name, Arg1 &&arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f(const char *names, Arg1 &&arg1, Args &&...args)
{
#ifndef ONLINE_JUDGE

    const char *comma = strchr(names + 1, ',');
    cout.write(names, comma - names) << ":" << arg1 << "|";
    __f(comma + 1, args...);

#endif
}

struct DSU
{
    vector<int> par, rank;
    DSU(int n)
    {
        par.clear(), rank.clear(), par.resize(n, -1), rank.resize(n, 1);
    }

    int find(int x)
    {
        if (par[x] == -1)
            return x;
        return par[x] = find(par[x]);
    }

    void unite(int x, int y)
    {
        int s1 = find(x), s2 = find(y);

        if (s1 == s2)
            return;

        if (rank[s2] > rank[s1])
            swap(s1, s2);
        rank[s1] += rank[s2];
        par[s2] = s1;
    }
};

bool compare(vector<int> &a, vector<int> &b)
{
    return a[1] < b[1];
}

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> points(n);

    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        points[i] = {x, y, i};
    }

    vector<vector<int>> edges;

    sort(all(points));

    for (int i = 0; i < n - 1; i++)
    {
        int xdif = abs(points[i][0] - points[i + 1][0]);
        edges.push_back({xdif, points[i][2], points[i + 1][2]});
    }

    sort(all(points),compare);

    for (int i = 0; i < n - 1; i++)
    {
        int ydif = abs(points[i][1] - points[i + 1][1]);
        edges.push_back({ydif, points[i][2], points[i + 1][2]});
    }

    sort(all(edges));

    DSU d(n);

    int ans = 0;

    for (auto i : edges)
    {
        if (d.find(i[1]) != d.find(i[2]))
        {
            ans += i[0];
            d.unite(i[1], i[2]);
        }
    }
    print(ans);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}

// CTRL + J to convert multple line code to one line
// cin does not move the input cursor to the next line, use cin.ignore() to move it to the next line
void print(int x)
{
    cout << (x) << endl;
}
void print(int x, int y)
{
    cout << (x) << " " << (y) << endl;
}
void print(int x, int y, int z)
{
    cout << (x) << " " << (y) << " " << (z) << endl;
}
void print(string s)
{
    cout << (s) << endl;
}
void print(char c)
{
    cout << (c) << endl;
}
void print(float x)
{
    cout << (x) << endl;
}
void print(vi v)
{
    for (auto i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}
void print(vvi v)
{
    for (auto i : v)
    {
        print(i);
    }
    cout << endl;
}
void read(int &x)
{
    cin >> (x);
}
void read(int &x, int &y)
{
    cin >> (x) >> (y);
}
void read(int &x, int &y, int &z)
{
    cin >> x >> y >> z;
}
void read(string &s)
{
    cin >> s;
}
void read(char &c)
{
    cin >> c;
}
void read(float &x)
{
    cin >> x;
}
void read(vi &v, int n)
{
    vi temp(n);
    v = temp;
    int i = 0;
    while (n--)
        cin >> v[i++];
}
void read(vvi &v, int n, int m)
{
    rep(i, 0, n)
    {
        read(v[i], m);
    }
}