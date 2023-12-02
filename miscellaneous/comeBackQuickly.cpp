/* There are n towns numbered 1 through n and m roads numbered 1 through m.
roadi is a one-way road from Town ai​ to Town bi​, and it takes ci​ minutes to go through. It is possible that ai​=bi​, and there may be multiple roads connecting the same pair of towns.
Alice is thinking about taking a walk in the country. We will call a walk valid when it goes through one or more roads and returns to the town it starts at.
For each town, determine whether there is a valid walk that starts at that town. Additionally, if there is a valid walk, find the minimum time such a walk requires, otherwise return -1.

Return a vector containing answers for each town from 1 to n respectively.
Constraints:

1<= n, m <= 2000

1<= ai, bi <= n

1<= ci <= 10^5

*/

//rohitaas_beri
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// #define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

#include<bits/stdc++.h>
using namespace std;

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

struct DGraph{

  int n;
  vvi adj; 
  vvpii wadj;
  vi vis,topo;
  bool isCycle;

  DGraph(int N)
  {
     n = N;
    adj.resize(n+1);
    wadj.resize(n+1);
    vis.resize(n+1,0);
  }

   void addEdge(int u, int v,int weighted = false, int w = 0)
  {
    if(!weighted)
    {
       adj[u].pb(v);
    }
    else
    {
      wadj[u].pb({v,w});
    }
   
  }

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

  void bfs(int node)
   {
     vis.clear();vis.resize(n+1,0);
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

   //Topological Sort

  void dfsTopological(int node,vi &stack)
  {
    vis[node]=1;
    stack[node]=1;
    for(auto i : adj[node])
    {
      if(!vis[i])
      {
        dfsTopological(i,stack);
      }
      else if(stack[i])
      {
        isCycle=true;
      }
    }
    stack[node]=0;
    topo.pb(node);
  }
   void topologicalOrdering() 
   {
    vis.clear();
    vis.resize(n+1,0);
    vi stack(n+1,0);
    rep(i,1,n+1)
    {
      if(!vis[i])
      {
        dfsTopological(i,stack);
      }
      
    }
    rev(topo);
   }

   //Kosaraju's Algorithm (No. of strongly connected components)

   void dfsForKosaraju(int node, vvi &adjRev)
   {
    vis[node]=1;
    for(auto i : adjRev[node])
    {
      if(!vis[i])
      {
        dfsForKosaraju(i,adjRev);
      }
    }
   }

   int kosaraju()
   {
    topologicalOrdering();
    vvi adjRev(n+1);

    for(int i =1;i<=n;i++)
    {
      for(auto j : adj[i])
      {
        adjRev[j].pb(i);
      }
    }

    vis.clear();
    vis.resize(n+1,0);

    int comp =0;
    rep(i,0,n)
    {
      if(!vis[topo[i]])
      {
        dfsForKosaraju(topo[i],adjRev);
        comp++;
      }
    }
    return comp;
   }

   vi Dijkstra(int node)
   {
    vi dis(n+1,INT_MAX);

    set<pii> s;

    dis[node]=0;
    s.insert({dis[node],node});

    while(sz(s))
    {
      auto it = *(s.begin());
      s.erase(it);
      int check = it.S;
      int val = it.F;

      for(auto i : wadj[check])
      {
        if(dis[i.F]>val + i.S)
        {
          s.erase({dis[i.F],i.F});
          dis[i.F]=val + i.S;
          s.insert({dis[i.F],i.F});
        }
      }
    }
    return dis;
   }
};


void solve()
{

  int n,M;cin>>n>>M;
  DGraph g(n);

  map<pii,int> m;
  rep(i,0,M)
  {
    int x,y,w;cin>>x>>y>>w;

    if(!m.count({x,y}))
    {
      m[{x,y}]=w;
    }
    else
    {
      m[{x,y}]=min(m[{x,y}],w);
    }
  }

  for(auto i : m)
  {
    if(i.F.F!=i.F.S)
    g.addEdge(i.F.F,i.F.S,1,i.S);
  }

  vi ans;
  rep(i,1,n+1)
  {
    vi dis = g.Dijkstra(i);

    int mn = INT_MAX;

    rep(j,1,n+1)
    {
      if(j==i)
      {
        if(m.count({i,i}))
        {
          mn = min(mn, m[{i,i}]);
        }

        con;
      }
      if(dis[j]!=INT_MAX)
      {
        if(m.count({j,i}))
        {
          mn = min(mn, m[{j,i}]+dis[j]);
        }
      }
    }
    if(mn == INT_MAX)
    {
      mn = -1;
    }

    ans.pb(mn);
  }
  printv(ans);
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
