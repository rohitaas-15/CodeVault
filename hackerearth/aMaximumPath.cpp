/*https://www.hackerearth.com/practice/algorithms/dynamic-programming/2-dimensional/practice-problems/algorithm/path-maximum-bb1a923a/*/
/*You are given an undirected tree  with  nodes rooted at node . Every node is assigned a value denoted by .

You are given  queries of type:

: Print the maximum value of the node present on a simple path between node  and  .
Input format

The first line contains two space-separated integers  denoting the number of nodes and queries respectively.
Next line contains space-separated integers denoting array .
Next  lines contain two space-separated integers  denoting an edge between node  and .
Next  lines contain two space-separated integers  denoting the query.
Output format

For each query, print the required answer in a new line.*/









//rohitaas_beri
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// #define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define int ll
#define dd long double
#define vi vector<int> 
#define vvi vector<vi> 
#define vvvi vector<vvi>
#define vpii vector<pair<int,int> > 
#define pii pair<int,int> 
#define vvpii vector<vpii> 
#define UB upper_bound
#define LB lower_bound
#define beg(v) v.begin()
#define en(v) v.end()
#define pb push_back
#define nl "\n"
#define con continue
#define br break
#define ret return
#define F first
#define S second
#define yes print("YES")
#define no print("NO")
#define rep(i,a,b) for(int i =(a);i<(b);i++)
#define all(v) v.begin(),v.end()
#define rev(v) reverse(all(v))
#define maxv(v) *max_element(all(v));
#define minv(v) *min_element(all(v));
#define sumv(v) accumulate(all(v),0ll)
#define print(value)  cout<<(value)<<nl
#define print2(v1,v2) cout<<(v1)<<" "<<(v2)<<nl
#define print3(v1,v2,v3) cout<<(v1)<<" "<<(v2)<<" "<<(v3)<<nl
#define print4(v1,v2,v3,v4) cout<<(v1)<<" "<<(v2)<<" "<<(v3)<<" "<<(v4)<<nl
#define printv(v)rep(it,0,v.size()){cout<<v[it]<<" ";}cout<<"\n"
#define printvv(v)rep(it,0,v.size()){rep(it2,0,v[0].size()){cout<<v[it][it2]<<" ";}cout<<"\n";}
#define sz(v) ((int)v.size())

//unweighted Graph 

 struct Graph{
   
   int n;
   vector<vector<int> > adj;
   vector<int> vis;
   vi a;
   //for trees
 
   //Storing the 2^(j)th parent of i
   int m;
   vvi sparse,sparsemx;
 
   vi depth, parent;
 
 
 
   Graph(int N)
   {
     n = N;
     m = 23;
     adj.resize(n+1);
     vis.resize(n+1,0);
     a.resize(n+1,0);
     //for trees
     depth.resize(n+1,0);
     parent.resize(n+1,0);

     sparse.resize(n+1,vi(m,0));

     sparsemx.resize(n+1,vi(m,0));
   }
 
   //adding edges
 
   void addEdge(int x, int y, int undir = true)
   {
     adj[x].pb(y);
 
     if(undir)
     {
       adj[y].pb(x);
     }
   }
 
 
   //Depth First Search template
   void dfs(int node)
   {
     vis[node]=1;
 
     //variable
 
     for(auto i : adj[node])
     {
       if(!vis[i])
       {
         dfs(i);
       }
     }
   }
 
   //Breadth First Search template
 
   void bfs(int node)
   {
     queue<int> q;
 
     q.push(node);
     vis[node]=1;
 
     //variable
 
     while(!q.empty())
     {
       int check = q.front(); q.pop();
       for(auto i : adj[check])
       {
         if(!vis[i])
         {
           vis[i]=1;
           q.push(i);
         }
       }
     }
   }
   //For Trees
 
   //DFS for storing information about the tree, depth starts from 1
 
   void dfsInfo(int node, int par,int fillSparse = 0)
   {
     parent[node]=par;
     depth[node]=depth[par]+1;
 
     if(fillSparse)
     {
       sparse[node][0]=par;
       sparsemx[node][0]=max(a[node],a[par]);
       rep(j,1,m)
       {
         sparse[node][j]=sparse[sparse[node][j-1]][j-1];
         sparsemx[node][j]=max(sparsemx[node][j-1],sparsemx[sparse[node][j-1]][j-1]);
       }
     }
 
     for(auto i : adj[node])
     {
       if(i!=par)
       {
         dfsInfo(i,node,fillSparse);
       }
     }
   }
  
   int LCA(int x, int y)
   {
     if(x==y)return x;
     if(depth[x]<depth[y])
     {
       swap(x,y);
     }
     
     int diff = depth[x]-depth[y];
 
     for(int j = m-1;j>=0;j--)
     {
       if((diff>>j) &1)
       {
         x= sparse[x][j];
       }
     }
     if(x==y)return x;
 
     for(int j = m-1;j>=0;j--)
     {
       if(sparse[x][j]!=sparse[y][j])
       {
         x = sparse[x][j],y= sparse[y][j];
       }
     }
     return parent[x];

   }
    int maxPath(int x, int y)
   {
   
     if(x==y)return a[x];

     int lca = LCA(x,y);
     int diff1 = -depth[lca]+depth[y];
     int diff2 = -depth[lca]+depth[x];
     int mx =0;



     for(int j = m-1;j>=0;j--)
     {
       if((1ll<<j)<=diff1)
       {
         mx = max(mx, sparsemx[y][j]);
		     y = sparse[y][j];
         diff1-=(1ll<<j);
       }
     }
     for(int j = m-1;j>=0;j--)
     {
       if((1ll<<j)<=diff2)
       {
         mx = max(mx, sparsemx[x][j]);
		     x= sparse[x][j];
         diff2-=(1ll<<j);
       }
     }
     return mx;

   }
 };

void solve()
{
  int n,q;cin>>n>>q;
  vi v(n);
  Graph g(n);
  rep(i,0,n)
  {
    cin>>v[i];
    g.a[i+1]=v[i];
  }
  rep(i,0,n-1)
  {
    int x,y;cin>>x>>y;
    g.addEdge(x,y);
  }
  g.dfsInfo(1,0,1);


  while(q--)
  {
    int x,y;cin>>x>>y;
    print(g.maxPath(x,y));
  }
  
 
}

signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(0);
    clock_t printClock = clock();

    int T=1;
    //cin>>T;

   
    while(T--) solve();

    cerr<< "RUNTIME : "<<((double)clock()-printClock)/CLOCKS_PER_SEC<<"s";
}




/* notes:

1) Dont use vector.resize() without vector.clear() .

2) Range of long long is -2^63 to 2^63-1 , range of unsigned long long 
   is 0 to 2^64-1 .

3) Expected number of coin throws to get N consecutive heads is 2^(n+1) - 2 .

4) Upper bound of number of divisors of a number n is n^(1/3) .

5) GCD(x,y)=GCD(x-y,y) , The same applies for multiple arguments .

6) To meet the constraints int the question,  we can sometimes kick out one state of our dp.
  We can achieve that by a relatively common trick: turn the removed state into the value of the dp.


7) If we have N elements out of which we want to choose K elements and it is allowed
  to choose one element more than once, then number of ways are given by: nCr(n+k-1,k) .


*/


/* Good Questions :

1 ) https://www.codechef.com/submit/SECPLAYER

 */
