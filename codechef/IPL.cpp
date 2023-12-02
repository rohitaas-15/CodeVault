//https://www.codechef.com/practice/course/dynamic-programming/INTDP01/problems/ZCO14004

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
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

void solve()
{
    int n;
    cin >> n;
    vector<int> money(n+1,0);
    read(money,n);

    vector<int > dp(n+1,0);

    dp[0]=0,dp[1]=money[0],dp[2]=money[0]+money[1];

    for(int i =3;i<=n;i++)
    {
        dp[i]=max({dp[i-1],dp[i-2]+money[i-1],dp[i-3]+money[i-1]+money[i-2]});
    }

    print(dp[n]);
}

signed main()
{
    int t = 1;
    //cin >> t;
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
