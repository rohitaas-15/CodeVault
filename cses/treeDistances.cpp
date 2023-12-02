/* https://cses.fi/problemset/task/1132/

You are given a tree consisting of n nodes.

Your task is to determine for each node the maximum distance to another node.

Input

The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,…,n.

Then there are n−1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.

Output

Print n integers: for each node 1,2,…,n, the maximum distance to another node.

Constraints
1≤n≤2⋅105
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
  vector<vector<int> > adj;

  vector<int> vis;
  vvpii top2;
  vi ans;

  Graph(int N)
  {
    n = N;
    adj.resize(n+1);
    vis.resize(n+1,0);
    top2.resize(n+1);
    ans.resize(n+1);
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
  int cnt =0;


  //max 2 depths in every subtree
  pii dfs(int node, int branch,int par)
  {
    vis[node]=1;
    vpii depths;

    for(auto i : adj[node])
    {
      if(!vis[i])
      {
          depths.pb(dfs(i, cnt++,node));
      }
    }

    if(depths.size()==0)
    {
      top2[node]={{0,branch}};
      return {1,branch};
    }

    sort(all(depths));
    rev(depths);

    top2[node]=depths;

    return {top2[node][0].F+1,top2[node][0].S};

  }

  //calculating the answer

  void dfs2(int node,int par, int prevans)
  {
    vis[node]=1;

    //variable
    for(auto i : adj[node])
    {
      if(!vis[i])
      {
        if(top2[i][0].S==top2[node][0].S)
        {
           dfs2(i,node,max(((top2[node].size()>1)?top2[node][1].F : 0),prevans+1));
        }
        else
        {
          dfs2(i,node, max((top2[node][0].F),prevans+1));
        }
      }
    }
    ans[node]=max(top2[node][0].F,prevans+1);
  }

  //Breadth First Search

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
};

void solve()
{
  int n;cin>>n;

  Graph tree(n);
  rep(i,0,n-1)
  {
    int x, y;cin>>x>>y;
    tree.addEdge(x,y);
  }

  tree.dfs(1,0,0);
  tree.vis.clear();
  tree.vis.resize(n+1,0);

  tree.dfs2(1,0,-1);

  rev(tree.ans);
  tree.ans.pop_back();
  rev(tree.ans);

  printv(tree.ans);


  
   
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
