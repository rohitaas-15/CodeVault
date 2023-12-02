/* 

https://cses.fi/problemset/task/1681/

A game has n levels, connected by m teleporters, and your task is to get from level 1 to level n. The game has been designed so that there are no directed cycles in the underlying graph. In how many ways can you complete the game?

Input

The first input line has two integers n and m: the number of levels and teleporters. The levels are numbered 1,2,…,n.

After this, there are m lines describing the teleporters. Each line has two integers a and b: there is a teleporter from level a to level b.

Output

Print one integer: the number of ways you can complete the game. Since the result may be large, print it modulo 109+7.

Constraints
1≤n≤105
1≤m≤2⋅105
1≤a,b≤n */

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

#define bug(...)  __f (#__VA_ARGS__, __VA_ARGS__)

template <typename Arg1>
void __f (const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f (const char* names, Arg1&& arg1, Args&&... args)
{
     #ifndef ONLINE_JUDGE 

     	const char* comma = strchr (names + 1, ',');
	    cout.write (names, comma - names) << ":" << arg1 << "|"; __f (comma + 1, args...);
                    
    #endif 
}
//unweighted Graph 

 struct Graph{
   
   int n;
   vvi adj;
   vi vis;
   bool undir=true,isCycle=false;
   long long ans =1,M = 1e9+7;
   vi dp;

   //for trees
   int m;
   vvi sparse;  //Storing the 2^(j)th parent of i
   vi depth, parent;

   //for DAG

   vi topo; //topological ordering
 
 
 
   Graph(int N)
   {
     n = N;
     m = (int)log2(n) + 2;
     adj.resize(n+1);
     vis.resize(n+1,0);
     depth.resize(n+1,0);
     parent.resize(n+1,0);
     sparse.resize(n+1,vi(m,0));
     dp.resize(n+1,0);
   }
 
   //adding edges
 
   void addEdge(int x, int y, int undir = true)
   {
     this->undir=undir;
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

   // 1. TREES
 
   void dfsData(int node, int par,int fillSparse = 0)  //DFS for storing information about the tree, depth starts from 1
   {
     parent[node]=par;
     depth[node]=depth[par]+1;
 
     if(fillSparse)
     {
       sparse[node][0]=par;
       rep(j,1,m)
       {
         sparse[node][j]=sparse[sparse[node][j-1]][j-1];
       }
     }
 
     for(auto i : adj[node])
     {
       if(i!=par)
       {
         dfsData(i,node,fillSparse);
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
 
    //LCA using two pointers
 
   int LCABrute(int x, int y)
   {
     if(x==y)return x;
     if(depth[x]<depth[y])
     {
       swap(x,y);
     }
     while(depth[x]!=depth[y])
     {
       x= parent[x];
     }
 
     while(x!=y)
     {
       x= parent[x],y=parent[y];
     }
     return x;
   }

   // 2. DAG

  void dfsTopological(int node)
  {
    vis[node]=1;
    
    if(node==n)
    {
      dp[node]=1;
      return ;
    }
    int sum=0;
    for(auto i : adj[node])
    {
      if(!vis[i])
      {
        dfsTopological(i);
      }
      sum=(sum+dp[i])%M;
    }
    dp[node]=sum;
  }

   void topologicalOrdering() //undir should be false
   {
    vis.clear();
    vis.resize(n+1,0);
    dfsTopological(1);
   }
 
 };
void solve()
{
  int n,m;cin>>n>>m;
  Graph g(n);
  rep(i,0,m)
  {
    int x,y;cin>>x>>y;
    g.addEdge(x,y,0);
  }
  g.topologicalOrdering();
  print(g.dp[1]);
 
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

