/*https://www.codechef.com/problems/FLIPCOIN*/

/*There are N coins kept on the table, numbered from 0 to N - 1. Initially, each coin is kept tails up. You have to perform two types of operations:

1) Flip all coins numbered between A and B inclusive. This is represented by the command "0 A B"

2) Answer how many coins numbered between A and B inclusive are heads up. This is represented by the command "1 A B".

Input :

The first line contains two integers, N and Q. Each of the next Q lines are either of the form "0 A B" or "1 A B" as mentioned above.

Output :

Output 1 line for each of the queries of the form "1 A B" containing the required answer for the corresponding query.*/

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
#define ret return;
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

template<typename T> struct SegmentTree{
  int n;
  vector<T> st;
  vector<int> lazy;
   T ZERO=0;

  //constructor
  SegmentTree(int N)
  {
    n = N;
    st.resize(4*n+2,ZERO);

    lazy.resize(4*n+2,0);
  }

//updating the parent
  T collect(T left, T right)
  {
    return left+right; //variable
  }
  //build
  void build(int s, int e , vector<T> &v, int node)
  {
     if(s>e)
    {
      return;
    }

    if(s==e)
    {
      st[node]=v[s]; 
      return ;
    }

    int mid = (s+e)>>1ll;

    build(s,mid,v,2*node+1);
    build(mid+1,e,v,2*node+2);

    st[node]=collect(st[2*node+1],st[2*node+2]);
  }

  void build(vector<T> &v)
  {
    build(0ll,v.size()-1,v,0ll);
  }

  //query
  T query(int s, int e, int qs, int qe, int node)
  {
    if(lazy[node]&1)
    {
       st[node]=(e-s+1)-st[node];
       lazy[node]=0;

      if(s!=e)
      {
        lazy[2*node+1]++;
        lazy[2*node+2]++;
      }
       
    }

    if(qs>e || qe<s)
    {
      return ZERO;
    }

    else if(s>=qs && e<=qe)
    {
      return st[node];
    }

    int mid = (s+e)>>1ll;

    return collect(query(s,mid,qs,qe,2*node+1),query(mid+1,e,qs,qe,2*node+2));
  }

  T query(int l , int r)
  {
    return query(0ll,n-1,l,r,0ll);
  }

  //update
  void update(int s, int e ,int l,int r, T val, int node)
  {

    if(lazy[node]&1)
    {
       st[node]=(e-s+1)-st[node];
       lazy[node]=0;

      if(s!=e)
      {
        lazy[2*node+1]++;
        lazy[2*node+2]++;
      }
       
    }
    if(s>r || e<l)
    {
      return ;
    }

    if(l<=s && r>=e)
    {
      st[node]=(e-s+1)-st[node];

       if(s!=e)
      {
        lazy[2*node+1]++;
        lazy[2*node+2]++;
      }
      
      return;
    }

    int mid = (s+e)>>1ll;

    update(s,mid,l,r,val,2*node+1);
    update(mid+1,e,l,r,val,2*node+2);

    st[node]=collect(st[2*node+1],st[2*node+2]);
  }

  void update(int l, int r, T val)
  {
    update(0ll,n-1,l,r,val,0ll);
  }

};




   
void solve()
{

  int n;cin>>n;
  vi v(n,0);

  SegmentTree<int> tree(n);
  tree.build(v);

  int q;cin>>q;
  vi ans;

  while(q--)
  {
    int t,a,b;cin>>t>>a>>b;
    if(t==0)
    {
      tree.update(a,b,1);
    }
    else
    {
      ans.pb(tree.query(a,b));
    }
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
