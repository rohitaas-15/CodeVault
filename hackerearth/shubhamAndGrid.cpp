/*You are given a grid of n rows and m columns consisting of lowercase English letters a, b, c, and d.

We say 4 cells form a "nice-quadruple" if and only if

The letters on these cells form a permutation of the set {
}.
The cell marked b is directly reachable from cell marked a.
The cell marked c is directly reachable from the cell marked b.
The cell marked d is directly reachable from the cell marked c.
A cell 
 is said to be directly reachable from cell 
 if and only if 
 is one of these 4 cells { 
, 
, 
 and 
}).

Given the constraint that each cell can be part of at most 1 "nice-quadruple", what's the maximum number of "nice-quadruples" you can select?

Input format

First line: Two space-separated integers n and m
Next n lines: Each contains m space separated lowercase letters from the set {
} denoting the grid cells.
Output format

Output the maximum number of "nice-quadruple" you can select.
https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/practice-problems/algorithm/shubham-and-grid-806c2c66/
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

int n,m;
struct Dinic{
    vector<vector<int> > adj,edges;
    vector<int> dis,vis;
    int n,src,sink,ec=0;

    Dinic(int N, int s,int t)
    {
        n = N, src = s, sink = t;
        adj.resize(n+1);
    }

    void addEdge(int x,int y, int w)
    {
        edges.push_back({x,y,w}),adj[x].push_back(ec++);
        edges.push_back({y,x,0}),adj[y].push_back(ec++);
    }

    bool level()
    {
        dis.clear(),dis.resize(n+1,-1);
        queue<int> q;
        q.push(src),dis[src]=0;
        while(!q.empty())
        {
            int node = q.front();
            q.pop();
            for(auto i : adj[node])
            {
                int to = edges[i][1],res=edges[i][2];
                if(res>0 && dis[to]==-1)
                {
                    dis[to]=dis[node]+1;
                    q.push(to);
                }
            }
        }
        return dis[sink]!=-1;
    }


    int dfs(int node,int mn)
    {
        if(node==sink)return mn;

        vis[node]=1;
        int flow=0;
        for(auto i : adj[node])
        {
            int to = edges[i][1],res=edges[i][2];
            if(res>0 && mn>0 && !vis[to] && dis[to]==dis[node]+1)
            {
                int newMn = min(mn, res);
                int pathFlow = dfs(to,newMn);
                flow+=pathFlow,edges[i][2]-=pathFlow,edges[i^1][2]+=pathFlow,mn-=pathFlow;
            }
        }
        return flow;
    }

    int max_flow()
    {
        int flow=0;
        while(level())
        {
            vis.clear(),vis.resize(n+1,0);
            if(!(flow+=dfs(src,1e9)))
            {
                break;
            }
        }
        return flow;
    }


};


int getVal(int x,int y)
{
    return x*m + y;
}


void solve()
{

    cin>>n>>m;
    vector<vector<char> > mat(n+1,vector<char> (m+1));

    int src = n*m+3,sink=n*m+4;

    Dinic g (n*m+5,src,sink);
    for(int i =0;i<n;i++)for(int j = 0;j<m;j++)cin>>mat[i][j];
    
    for(int i =0;i<n;i++)for(int j = 0;j<m;j++)
    {
        int no = mat[i][j]-'a';
        for(int k = -1;k<=1;k++)for(int l = -1;l<=1;l++)if(abs(k)!=abs(l))
        {
            int ni = i+k,nj=j+l;
            if(ni>=0 && ni<n && nj>=0 && nj<m && (mat[ni][nj]-'a')==no+1)
            {
                g.addEdge(getVal(i,j),getVal(ni,nj),1);
            }

        }

        if(no==0)
        {
            g.addEdge(src,getVal(i,j),1);
        }
        else if(no==3)
        {
            g.addEdge(getVal(i,j),sink,1);
        }    
    }
    print(g.max_flow());

    
    
    
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