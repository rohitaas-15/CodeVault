/*https://codeforces.com/problemset/problem/597/C*/

/*For the given sequence with n different elements find the number of increasing subsequences with k + 1 elements. It is guaranteed that the answer is not greater than 8·1018.

Input
First line contain two integer values n and k (1 ≤ n ≤ 105, 0 ≤ k ≤ 10) — the length of sequence and the number of elements in increasing subsequences.

Next n lines contains one integer ai (1 ≤ ai ≤ n) each — elements of sequence. All values ai are different.

Output
Print one integer — the answer to the problem.*/

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

struct fenwickTree{
  vector<int> ft;
  int n;

  fenwickTree(int N)
  {
    n = N+1;
    ft.resize(n,0);
  }

  void update(int index, int val)
  {
    int temp = index+1;

    while(temp<n)
    {
      ft[temp]+=val;
      temp+=(temp&(-temp));
    }
  }

  int query(int index)
  {
      int temp =index+1;
      int ans =0;

      while(temp)
      {
        ans = (ans + ft[temp]);
        temp-=(temp &(-temp));
      }
      return ans;
  }

  int query(int l ,int r)
  {
    return query(r)-query(l-1);
  }
};

void solve()
{

  int n,k;cin>>n>>k;
  vi v(n+1);
  rep(i,0,n)
  {
    cin>>v[i+1];
  }

  vvi dp(k+2,vi(n+1,0));

  fenwickTree tree(1e5+1);

  dp[0][0]=1;
  tree.update(0,1);

  rep(i,1,k+2)
  {
    rep(j,1,n+1)
    {
      dp[i][j]=tree.query(v[j]-1);
      int val = tree.query(v[j],v[j]);
      tree.update(v[j],-val);
      tree.update(v[j],dp[i-1][j]);
    }

    rep(j,0,n+1)
    {
      int val = tree.query(v[j],v[j]);
      tree.update(v[j],-val);
    }
  }

  print(sumv(dp[k+1]));

 
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
