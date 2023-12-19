/*You are given a rooted tree consisting of n nodes. The nodes are numbered 1,2,\ldots,n, and node 1 is the root. Each node has a color.
Your task is to determine for each node the number of distinct colors in the subtree of the node.
Input
The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,\ldots,n.
The next line consists of n integers c_1,c_2,\ldots,c_n: the color of each node.
Then there are n-1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.
Output
Print n integers: for each node 1,2,\ldots,n, the number of distinct colors.
https://cses.fi/problemset/task/1139/
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
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

const int N = 2e5 + 2;
vector<vector<int>> adj(N);
vector<int> tin(N),tout(N),flat(N),BIT(N,0),color(N);
int tme=0;

void dfs(int node, int par)
{
    tin[node]=++tme;

    for(auto i : adj[node])if(i!=par)
    {
        dfs(i,node);
    }
    tout[node]=tme;
}

void update(int index,int val)
{
    int i =index;
    while(i<N) BIT[i]+=val, i+=i&(-i);
}

int query(int index)
{
    int i = index,ans=0;
    while(i>0)  ans += BIT[i],i-=i&(-i);
    return ans;
}


void solve()
{

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> color[i + 1];

    for (int i = 0; i< n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    dfs(1,0);

    vector<vector<pair<int,int> > > queryLeft(n+1);
    for(int node = 1;node<=n;node++)
    {
        flat[tin[node]]=color[node];

        int l=tin[node],r=tout[node];
        queryLeft[r].push_back({l,node});
    }

    map<int,int> latest; //keep the last occurence of a color to store the answer for a prefix index, and use prefix(r)-prefix(l-1) to get the answer for a range

    vector<int> ans(n,0);

    for(int right = 1;right<=n;right++)
    {
        int col=flat[right];

        if(!latest.count(col))
        {
            update(right,1);
            latest[col]=right;
        }
        else
        {
            update(latest[col],-1);
            update(right,1);
            latest[col]=right;
        }

        for(auto i : queryLeft[right])
        {
            int left = i.first;
            ans[i.second-1]=query(right)-query(left-1);
        }
    }

    print(ans);



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