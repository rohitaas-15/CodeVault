/* https://codeforces.com/contest/86/problem/D

An array of positive integers a1, a2, ..., an is given. Let us consider its arbitrary subarray al, al + 1..., ar, where 1 ≤ l ≤ r ≤ n. For every positive integer s denote by Ks the number of occurrences of s into the subarray. We call the power of the subarray the sum of products Ks·Ks·s for every positive integer s. The sum contains only finite number of nonzero summands as the number of different values in the array is indeed finite.

You should calculate the power of t given subarrays.

Input
First line contains two integers n and t (1 ≤ n, t ≤ 200000) — the array length and the number of queries correspondingly.

Second line contains n positive integers ai (1 ≤ ai ≤ 106) — the elements of the array.

Next t lines contain two positive integers l, r (1 ≤ l ≤ r ≤ n) each — the indices of the left and the right ends of the corresponding subarray.

Output
Output t lines, the i-th line of the output should contain single positive integer — the power of the i-th query subarray.

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preferred to use cout stream (also you may use %I64d).

 */
 
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

struct query{


  int l, r, ans , block, index;
};

bool comp(query a, query b)
{
    return make_pair(a.block,a.r)<make_pair(b.block,b.r);
}

bool comp2(query a, query b)
{
    return a.index<b.index;
}

int answer=0;

vi freq(1e6+1,0);

void add(int x)
{
   answer -= freq[x]*freq[x]*x;
   freq[x]++;
   answer +=  freq[x]*freq[x]*x;
}

void remove(int x)
{
   answer -= freq[x]*freq[x]*x;
   freq[x]--;
   answer +=  freq[x]*freq[x]*x;
}

void MosAlgorithm(vector<int> &v,vector<vi> &queries )
{
    int n = v.size();
  
    int m = sqrt(n)+1;
  
    vector<query> q;
    int cnt =0;
    for(auto i : queries)
    {
      q.pb({i[0],i[1],0,i[0]/m,cnt++});
    }
  
    sort(all(q),comp);
  
    int x=0,y=0;
  
    rep(i,0,q.size())
    {
      
      //removing y
  
      while(y>q[i].r+1)
      {
        y--;
        remove(v[y]);
      }
  
      while(y<=q[i].r)
      {
        add(v[y]);
        y++;
      }
  
      while(x<q[i].l)
      {
        remove(v[x]);
        x++;
      }
  
      while(x>q[i].l)
      {
        x--;
        add(v[x]);
      }
  
      q[i].ans = answer;
    }
  
    sort(all(q),comp2);
  
    rep(i,0,q.size())
    {
      print(q[i].ans);
    }
}

void solve()
{

  int n,q;cin>>n>>q;
  vi v(n);
  rep(i,0,n)
  {
    cin>>v[i];
  }

  vector<vi> queries;
  while(q--)
  {
    int l,r;cin>>l>>r;
    queries.pb({l-1,r-1});
  }

  MosAlgorithm(v,queries);


 
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
