/*There are 𝑛
 people on the number line; the 𝑖
-th person is at point 𝑎𝑖
 and wants to go to point 𝑏𝑖
. For each person, 𝑎𝑖<𝑏𝑖
, and the starting and ending points of all people are distinct. (That is, all of the 2𝑛
 numbers 𝑎1,𝑎2,…,𝑎𝑛,𝑏1,𝑏2,…,𝑏𝑛
 are distinct.)

All the people will start moving simultaneously at a speed of 1
 unit per second until they reach their final point 𝑏𝑖
. When two people meet at the same point, they will greet each other once. How many greetings will there be?

Note that a person can still greet other people even if they have reached their final point.

Input
The first line of the input contains a single integer 𝑡
 (1≤𝑡≤104
) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer 𝑛
 (1≤𝑛≤2⋅105
) — the number of people.

Then 𝑛
 lines follow, the 𝑖
-th of which contains two integers 𝑎𝑖
 and 𝑏𝑖
 (−109≤𝑎𝑖<𝑏𝑖≤109
) — the starting and ending positions of each person.

For each test case, all of the 2𝑛
 numbers 𝑎1,𝑎2,…,𝑎𝑛,𝑏1,𝑏2,…,𝑏𝑛
 are distinct.

The sum of 𝑛
 over all test cases does not exceed 2⋅105
.

Output
For each test case, output a single integer denoting the number of greetings that will happen.*/
//https://codeforces.com/contest/1915/problem/F
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define INF 1000000000000000000ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
#define endl "\n"

int _debug = 0;
#define nl        \
    cout << endl; \
    if (_debug)   \
        cerr << endl;

//-------------------------------------------------------------------------------
// print helper
int _nested = 0;
template <typename Primitive>
void print(Primitive &&P)
{
    cout << P << " ";
    if (_debug)
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

const int N = 3e5+2;
int bit[N];
void update(int index , int val)
{
    while(index<N)
    {
        bit[index]+=val;
        index+=index&(-index);
    }
}

int query(int index )
{
    int ans =0;
    while(index>0)
    {
        ans+=bit[index];
        index-=index&(-index);
    }
    return ans;
}

void solve()
{

    memset(bit,0,sizeof(bit));
    vector<pair<int,int> > co;
    int n;cin>>n;
    map<int,int> compress;

    for(int i =0;i<n;i++)
    {
        int a,b;cin>>a>>b;
        co.push_back({a,b});
        compress[b]++;
    }

    int cnt =1;
    for(auto &i : compress)
    {
        i.second=cnt++;
    }

    sort(all(co));
    int ans =0,total=0;
    for(auto i : co)
    {
        ans += total - query(compress[i.second]);
        total++;
        update(compress[i.second],1);
    }
    print(ans);
  
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int _t = 1;
    cin >> _t;
    while (_t--)
        solve();
}
// cin does not move the input cursor to the next line, use cin.ignore() to move it to the next line
// use an array instead of an int whenever possible, for coding competitions