//https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/

/* Alice and Bob have an undirected graph of n nodes and three types of edges:

Type 1: Can be traversed by Alice only.
Type 2: Can be traversed by Bob only.
Type 3: Can be traversed by both Alice and Bob.
Given an array edges where edges[i] = [typei, ui, vi] represents a bidirectional edge of type typei between nodes ui and vi, find the maximum number of edges you can remove so that after removing the edges, the graph can still be fully traversed by both Alice and Bob. The graph is fully traversed by Alice and Bob if starting from any node, they can reach all other nodes.

Return the maximum number of edges you can remove, or return -1 if Alice and Bob cannot fully traverse the graph.

*/

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
  return a[2]>b[2];
}


class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        
        vvi e;
  for(auto i : edges)
  {
    int t,x,y;t=i[0],x=i[1],y=i[2];
      e.pb({x,y,t});

  }
        
  sort(all(e),compare);

  DSU g1(n),g2(n);
               
  int ans =0;
  for(auto i : e)
  {
    if(i[2]==1)
    {
      if(g1.find(i[0])==g1.find(i[1]))
      {
        ans++;
      
      }
      else
      {
        g1.join(i[0],i[1]);
      }
    }
    else if(i[2]==2)
    {
      if(g2.find(i[0])==g2.find(i[1]))
      {
        ans++;
      
      }
      else
      {
        g2.join(i[0],i[1]);
      }
    }
    else
    {
      if(g1.find(i[0])==g1.find(i[1]) &&  g2.find(i[0])==g2.find(i[1]))
      {
        ans++;
      }
      else
      {
         g1.join(i[0],i[1]);
         g2.join(i[0],i[1]);
      }
    }
  }
  rep(i,2,n+1)
  {
    if(g1.find(i)!=g1.find(i-1))
    {
      ans=-1;
      br;
    }

     if(g2.find(i)!=g2.find(i-1))
    {
      ans=-1;
      br;
    }
  }
  return (ans);


    }
};
