/*

There is a toy building consisting of 𝑛 towers. Each tower consists of several cubes standing on each other. The 𝑖-th tower consists of ℎ𝑖 cubes, so it has height ℎ𝑖.

Let's define operation slice on some height 𝐻 as following: for each tower 𝑖, if its height is greater than 𝐻, then remove some top cubes to make tower's height equal to 𝐻. Cost of one "slice" equals to the total number of removed cubes from all towers.

Let's name slice as good one if its cost is lower or equal to 𝑘 (𝑘≥𝑛).


Calculate the minimum number of good slices you have to do to make all towers have the same height. Of course, it is always possible to make it so.

Input
The first line contains two integers 𝑛 and 𝑘 (1≤𝑛≤2⋅105, 𝑛≤𝑘≤109) — the number of towers and the restriction on slices, respectively.

The second line contains 𝑛 space separated integers ℎ1,ℎ2,…,ℎ𝑛 (1≤ℎ𝑖≤2⋅105) — the initial heights of towers.

Output
Print one integer — the minimum number of good slices you have to do to make all towers have the same heigth.
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
#define ub upper_bound
#define lb lower_bound
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



void solve()
{
  int n,k;cin>>n>>k;

  vi cnt(2e5+1,0);


  vi h(n);

   rep(i,0,n)
  {
    cin>>h[i];
  }
 
  rep(i,0,n)
  {
    cnt[h[i]]++;
  }


  int mn = minv(h);

  
  int ans =0;

  for(int i =2e5-1;i>=0;i--)
  {
    cnt[i]=cnt[i+1]+cnt[i];
  }

  int prev =0;
 
  for(int i =2e5;i>=mn;i--)
  {
 
    if(prev+cnt[i]>k)
    {
      ans++;
      prev=cnt[i];

    }
    else
    prev+=cnt[i];
    
  }

  if(prev!=n)
  {
    ans++;
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


 
