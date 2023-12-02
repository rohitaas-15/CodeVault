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

map<int,int> bracketMap;

string makeString(int i , int n , string &s)
{
    if(i==n)
    {
        return "";
    }

    string make;

    if(s[i]>='0' && s[i]<='9')
    {
        int k =i;

        string number;

        while(s[k]!='{')
        {
            number+=s[k++];
        }

        int times = stoi(number,nullptr,10);

        int start = k+1,end = bracketMap[k]-1;

        string subString = makeString(start,end+1,s);

        while(times--)
        {
            make+=subString;
        }

        return make + makeString(end+2,n,s);
    }
    else
    {
        return s[i]+makeString(i+1,n,s);
    }
}

void solve()
{
    string s;cin>>s;

    int n = s.size();

    stack<pair<char,int > > st;


    int i =0;

    while(i<n)
    {
        if(s[i]=='{')
        {
            st.push({'{',i});
        }
        else if(s[i]=='}')
        {
            auto p = st.top();
            bracketMap[p.second]=i;
            st.pop();
        }
        i++;
    }

    print(makeString(0,n,s));
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
