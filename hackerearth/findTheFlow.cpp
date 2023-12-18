/*Given a directed flow network where each edge has a capacity of flow it could allow, find the maximum flow over the network from source(S) to sink(T).

Network will follow these rules:

Only one source(S) and only one sink(T).
Other than source and sink, nodes are represented with alphabets 
.
There are no self loops.
There will be no initial dead ends other than T.
For any pair of nodes, direction of edges between them will be in single direction.
Input Format:
First line has an integer E- number of edges.
Next E lines have three values 
 which implies there is a node from 
 to 
 with capacity 
.

Output Format:
Print a single integer which is the maximum flow from source to sink.

Constraints:

Network includes S, T, a maximum of 
 other nodes.
 https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/practice-problems/algorithm/find-the-flow/
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

struct Dinic{

    vector<vector<int> > adj,edges;
    vector<int> dis, vis;
    int n,src,sink,ec=0;
    Dinic(int n,int s, int t)
    {
        this->n=n,src=s,sink=t;
        adj.resize(n+1);
    }

    void addEdge(int a,int b, int w)
    {
        edges.push_back({a,b,w});
        adj[a].push_back(ec++);
        edges.push_back({b,a,0});
        adj[b].push_back(ec++);
    }

    bool level()
    {
        dis.clear(),dis.resize(n+1,-1);
        queue<int> q;
        q.push(src),dis[src]=0;
        while(!q.empty())
        {
            int node = q.front();q.pop();
            for(auto i : adj[node])
            {
                int to = edges[i][1],res=edges[i][2];
                if(res && dis[to]==-1)
                {
                    dis[to]=dis[node]+1;
                    q.push(to);
                }
            }
        }
        return dis[sink]!=-1;
    }

    int augmentPath(int node,int mn)
    {
        if(node==sink)return mn;

        vis[node]=1;
        int flow=0;
        for(auto i : adj[node])
        {
            int to =edges[i][1],res=edges[i][2];
            if(res && mn && !vis[to] && dis[to]==dis[node]+1)
            {
                int newMn = min(mn, res);
                int pathFlow = augmentPath(to,newMn);
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
            if(!(flow+=augmentPath(src,1e9)))
            {
                break;
            }
        }
        return flow;
    }

};


void solve()
{
    int m;cin>>m;

    Dinic g(30,'S'-'A','T'-'A');
    while(m--)
    {
        char to,from;int w;cin>>to>>from>>w;
        g.addEdge(to-'A',from-'A',w);
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