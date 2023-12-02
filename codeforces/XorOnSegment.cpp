/*https://codeforces.com/contest/242/problem/E*/

/*
You've got an array a, consisting of n integers a1, a2, ..., an. You are allowed to perform two operations on this array:

Calculate the sum of current array elements on the segment [l, r], that is, count value al + al + 1 + ... + ar.
Apply the xor operation with a given number x to each array element on the segment [l, r], that is, execute . This operation changes exactly r - l + 1 array elements.
Expression  means applying bitwise xor operation to numbers x and y. The given operation exists in all modern programming languages, for example in language C++ and Java it is marked as "^", in Pascal — as "xor".

You've got a list of m operations of the indicated type. Your task is to perform all given operations, for each sum query you should print the result you get.

Input
The first line contains integer n (1 ≤ n ≤ 105) — the size of the array. The second line contains space-separated integers a1, a2, ..., an (0 ≤ ai ≤ 106) — the original array.

The third line contains integer m (1 ≤ m ≤ 5·104) — the number of operations with the array. The i-th of the following m lines first contains an integer ti (1 ≤ ti ≤ 2) — the type of the i-th query. If ti = 1, then this is the query of the sum, if ti = 2, then this is the query to change array elements. If the i-th operation is of type 1, then next follow two integers li, ri (1 ≤ li ≤ ri ≤ n). If the i-th operation is of type 2, then next follow three integers li, ri, xi (1 ≤ li ≤ ri ≤ n, 1 ≤ xi ≤ 106). The numbers on the lines are separated by single spaces.

Output
For each query of type 1 print in a single line the sum of numbers on the given segment. Print the answers to the queries in the order in which the queries go in the input.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams, or the %I64d specifier.*/

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

int power(int a,int b , int M=LLONG_MAX)
{
  if(!b)return 1;
  int sp = power(a,b/2,M); sp = (sp*sp)%M;
  if(b&1)return ((a%M) * sp)%M;
  else return sp;
}

template<typename T> struct SegmentTree{
  int n;
  vector<T> st;
   T ZERO=0;

   vector<int> lazy;

  //constructor
  SegmentTree(int N)
  {
    n = N;
    st.resize(4*n+2,ZERO);
    lazy.resize(4*n+2,ZERO);
  }

//updating the parent
  T collect(T left, T right)
  {
    return left + right; //variable
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

  void update(int l,int r, T val)
  {
    update(0ll,n-1,l,r,val,0ll);
  }

};


   
void solve()
{

  int n;cin>>n;
  vi v(n,0);

  vector<SegmentTree<int> > trees(22,SegmentTree<int> (n));

  rep(i,0,n)
  {
    cin>>v[i];
  }

  int index =0;
  while(index<=21)
  {
    vector<int> ones;



    rep(i,0,n)
    {
      ones.push_back((v[i]&(1<<index))!=0);
    }
 
    trees[index].build(ones);
    index++;
  }

  int q;cin>>q;
  vi answer;

  while(q--)
  {
    int t;cin>>t;

    if(t==1)
    {
      int l,r;cin>>l>>r;
      int ans =0;
      l--,r--;

      rep(i,0,22)
      {
          ans += (trees[i].query(l,r))*power(2,i);
      }

      print(ans);
      answer.pb(ans);
    }
    else
    {
      int l,r,x;cin>>l>>r>>x;
      l--,r--;

      rep(i,0,22)
      {
        if((x&(1<<i)))
        {
          trees[i].update(l,r,1);
        }
      }
    }
  }

  //printv(answer);

 
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
