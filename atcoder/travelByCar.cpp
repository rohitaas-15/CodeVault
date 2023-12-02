// https://atcoder.jp/contests/abc143/tasks/abc143_e

/*There are n towns numbered 1 to n, you are  given  an array of edges where edges[i] = [ui, vi, ci] is a bidirectional road of length ci connecting town ui and town vi .

Alice will travel between these towns by car, passing through these roads. The fuel tank of his car can contain at most L liters of fuel and one liter of fuel is consumed for each unit distance traveled. When visiting a town while traveling, he can full the tank (or choose not to do so). Travel that results in the tank becoming empty halfway on the road cannot be done.

So, you are given an array of queries where query[i] = [si, ti] , you have to find the minimum number of times he needs to full his tank while traveling from town si to ti , if town  ti is unreachable return -1.

Return an array containing the answer of each query respectively.

Constraints:

2<= n <= 300

0<= edges.length <= n*(n-1)/2

1<= L <= 10^6

1<= ui, vi <= n

ui != vi

(ui , vi) != (uj, vj) (if i!=j)

1<= ci <= 10^6

0<= queries.length <= n*(n-1)

1<= si, ti <= n

si != ti

(si, ti) != (sj, tj) (if i!=j)
*/

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

void solve()
{
  int n, m, l;
  cin >> n >> m >> l;

  vector<vector<int>> fuel(n + 1, vector<int>(n + 1, 1e18)), rounds;
  rounds = fuel;

  for (int i = 0; i <= n; i++)
  {
    fuel[i][i] = rounds[i][i] = 0ll;
  }

  for (int i = 0; i < m; i++)
  {
    int x, y, z;
    cin >> x >> y >> z;

    if (z <= l)
      fuel[x][y] = fuel[y][x] = z;
  }

  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
      {
        if (fuel[i][j] > fuel[i][k] + fuel[k][j])
        {
          fuel[i][j] = fuel[i][k] + fuel[k][j];
        }
      }

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      if (i == j)
        continue;

      if (fuel[i][j] <= l)
      {
        rounds[i][j] = 1ll;
        rounds[j][i] = 1ll;
      }
    }
  }

  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
      {
        if (rounds[i][j] > rounds[i][k] + rounds[k][j])
        {
          rounds[i][j] = rounds[i][k] + rounds[k][j];
        }
      }

  int q;
  cin >> q;
  while (q--)
  {
    int a, b;
    cin >> a >> b;

    if (fuel[a][b] == 1e18)
      print(-1ll);
    else
      print(rounds[a][b] - 1);
  }
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