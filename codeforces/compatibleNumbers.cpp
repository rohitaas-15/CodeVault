/*Two integers x and y are compatible, if the result of their bitwise "AND" equals zero, that is, a & b = 0. For example, numbers 90 (10110102) and 36 (1001002) are compatible, as 10110102 & 1001002 = 02, and numbers 3 (112) and 6 (1102) are not compatible, as 112 & 1102 = 102.

You are given an array of integers a1, a2, ..., an. Your task is to find the following for each array element: is this element compatible with some other element from the given array? If the answer to this question is positive, then you also should find any suitable element.

Input
The first line contains an integer n (1 ≤ n ≤ 106) — the number of elements in the given array. The second line contains n space-separated integers a1, a2, ..., an (1 ≤ ai ≤ 4·106) — the elements of the given array. The numbers in the array can coincide.

Output
Print n integers ansi. If ai isn't compatible with any other element of the given array a1, a2, ..., an, then ansi should be equal to -1. Otherwise ansi is any such number, that ai & ansi = 0, and also ansi occurs in the array a1, a2, ..., an.*/
// https://codeforces.com/contest/165/problem/E

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

vector<int> dpMask;

void fillAns(int mask,int &compatible,int maskIndex)
{
    if(maskIndex<0)
    {
        dpMask[mask]=compatible;
        return ;
    }

    if(dpMask[mask]!=-1)
    {
        return ;
    }

    while(maskIndex>=0 && ((1ll<<maskIndex) & mask) ==0ll)
    {
        maskIndex--;
    }

    if(maskIndex==-1)
    {
        dpMask[mask]=compatible;
        return ;
    }

    int p2= 1ll<<maskIndex;
    fillAns(mask-p2,compatible,maskIndex-1);
    fillAns(mask,compatible,maskIndex-1);

}

void solve()
{
    int n;
    cin >> n;
    vi v(n);
    read(v, n);

    dpMask.resize(8e6+1,-1);
    vector<int> ans(n);

    int raise=22;

    for(auto i : v)
    {
        int mask = ((1ll<<(raise))-1) ^(i);
        fillAns(mask,i,raise-1);
    }

    rep(i,0,n)
    {
        ans[i]=dpMask[v[i]];
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
