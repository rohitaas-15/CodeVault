//https://codeforces.com/contest/1095/problem/F

/*You are given an undirected graph consisting of 𝑛 vertices. A number is written on each vertex; the number on vertex 𝑖 is 𝑎𝑖. Initially there are no edges in the graph.

You may add some edges to this graph, but you have to pay for them. The cost of adding an edge between vertices 𝑥 and 𝑦 is 𝑎𝑥+𝑎𝑦 coins. There are also 𝑚 special offers, each of them is denoted by three numbers 𝑥, 𝑦 and 𝑤, and means that you can add an edge connecting vertices 𝑥 and 𝑦 and pay 𝑤 coins for it. You don't have to use special offers: if there is a pair of vertices 𝑥 and 𝑦 that has a special offer associated with it, you still may connect these two vertices paying 𝑎𝑥+𝑎𝑦 coins for it.

What is the minimum number of coins you have to spend to make the graph connected? Recall that a graph is connected if it's possible to get from any vertex to any other vertex using only the edges belonging to this graph.

Input
The first line contains two integers 𝑛 and 𝑚 (1≤𝑛≤2⋅105, 0≤𝑚≤2⋅105) — the number of vertices in the graph and the number of special offers, respectively.

The second line contains 𝑛 integers 𝑎1,𝑎2,…,𝑎𝑛 (1≤𝑎𝑖≤1012) — the numbers written on the vertices.

Then 𝑚 lines follow, each containing three integers 𝑥, 𝑦 and 𝑤 (1≤𝑥,𝑦≤𝑛, 1≤𝑤≤1012, 𝑥≠𝑦) denoting a special offer: you may add an edge connecting vertex 𝑥 and vertex 𝑦, and this edge will cost 𝑤 coins.

Output
Print one integer — the minimum number of coins you have to pay to make the graph connected.*/

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

struct DSU{
  int n ;

  vi parent,rank;

  DSU(int N)
  {
    n = N;
    parent.resize(n+1,0);
    rank.resize(n+1,1);
    iota(all(parent),0ll);
  }

  int find(int x)
  {
    if(parent[x]==x)return x;

    //path compression

    return parent[x]= find(parent[x]);
  }

  void join(int x, int y)
  {
    int s1 = find(x);
    int s2= find(y);

    if(s1!=s2)
    {
      //union by rank
      if(rank[s1]>rank[s2])
      {
         parent[s2]=s1;
         rank[s1]+=rank[s2];
      }
      else
      {
        parent[s1]=s2;
        rank[s2]+=rank[s1];
      }
    }
  }

};

bool compare(vi &a, vi &b)
{
  return a[2]<b[2];
}


void solve()
{
  int n,m;cin>>n>>m;

  vpii cost(n+1);
  rep(i,0,n)
  {
    cin>>cost[i+1].F;
    cost[i+1].S=i+1;
  }

  vvi special;

  rep(i,0,m)
  {
    int x,y,w;cin>>x>>y>>w;

    special.pb({x,y,w});
  }

  sort(all(cost));
  rep(i,2,n+1)
  {
    special.pb({cost[1].S,cost[i].S,cost[i].F+cost[1].F});
  }

  
  sort(all(special),compare);

  DSU g(n);
  int ans =0;
  for(auto i : special)
  {
      if(g.find(i[0])==g.find(i[1]))
      {
        con;
      }
     else
     {
      g.join(i[0],i[1]);
      ans+=i[2];
     }
  }
  print(ans);

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
