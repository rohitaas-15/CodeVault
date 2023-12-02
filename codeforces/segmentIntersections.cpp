/*https://codeforces.com/contest/1389/problem/D

You are given two lists of segments [𝑎𝑙1,𝑎𝑟1],[𝑎𝑙2,𝑎𝑟2],…,[𝑎𝑙𝑛,𝑎𝑟𝑛] and [𝑏𝑙1,𝑏𝑟1],[𝑏𝑙2,𝑏𝑟2],…,[𝑏𝑙𝑛,𝑏𝑟𝑛].

Initially, all segments [𝑎𝑙𝑖,𝑎𝑟𝑖] are equal to [𝑙1,𝑟1] and all segments [𝑏𝑙𝑖,𝑏𝑟𝑖] are equal to [𝑙2,𝑟2].

In one step, you can choose one segment (either from the first or from the second list) and extend it by 1. In other words, suppose you've chosen segment [𝑥,𝑦] then you can transform it either into [𝑥−1,𝑦] or into [𝑥,𝑦+1].

Let's define a total intersection 𝐼 as the sum of lengths of intersections of the corresponding pairs of segments, i.e. ∑𝑖=1𝑛intersection_length([𝑎𝑙𝑖,𝑎𝑟𝑖],[𝑏𝑙𝑖,𝑏𝑟𝑖]). Empty intersection has length 0 and length of a segment [𝑥,𝑦] is equal to 𝑦−𝑥.

What is the minimum number of steps you need to make 𝐼 greater or equal to 𝑘?

Input
The first line contains the single integer 𝑡 (1≤𝑡≤1000) — the number of test cases.

The first line of each test case contains two integers 𝑛 and 𝑘 (1≤𝑛≤2⋅105; 1≤𝑘≤109) — the length of lists and the minimum required total intersection.

The second line of each test case contains two integers 𝑙1 and 𝑟1 (1≤𝑙1≤𝑟1≤109) — the segment all [𝑎𝑙𝑖,𝑎𝑟𝑖] are equal to initially.

The third line of each test case contains two integers 𝑙2 and 𝑟2 (1≤𝑙2≤𝑟2≤109) — the segment all [𝑏𝑙𝑖,𝑏𝑟𝑖] are equal to initially.

It's guaranteed that the sum of 𝑛 doesn't exceed 2⋅105.

Output
Print 𝑡 integers — one per test case. For each test case, print the minimum number of step you need to make 𝐼 greater or equal to 𝑘.

brute force/greedy/implementation/math/2100
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

int SI(int n,int k, int l1,int r1,int l2,int r2){
    int work =0;
    
    if(r1<=l2  || r2<=l1)
    {
        if(r1<=l2)
        {
            work = l2-r1;
            
        }
        else
        {
            work = l1-r2;
        }
        
        int steps = max(r1,r2)-min(l1,l2);
        
        if(steps>=k)
        {
            return work + k;
        }

    
        int gw=0;
        k-=steps;
        gw +=steps;
        int times2=1;

      while(2*min(steps,k)>work+min(steps,k) && times2<=n-1)
      {
        times2++;
        gw+=min(k,steps);
        k-=min(k,steps);
      }

       return times2*work + 2*k + gw;
        
       
        
    }
    else
    {
        int steps =n*abs(( abs(l1-l2)+abs(r1-r2)));
        
        int inter = n*(max(r1,r2)-min(l1,l2));
        
        int ini = (max(r1,r2)-min(l1,l2))- abs(( abs(l1-l2)+abs(r1-r2)));
        
        if(ini *n >=k)
        {
            return 0;
        }
        
        
        if(inter>=k)
        {
            return k-n*ini;
        }
        else
        {
            return steps + 2*(k-inter);
        }
    }
    
}
void solve()
{

  int n,k,l1,r1,l2,r2;
  cin>>n>>k>>l1>>r1>>l2>>r2;
  print(SI(n,k,l1,r1,l2,r2));
  
}

signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(0);
    clock_t printClock = clock();

    int T=1;
    cin>>T;

   
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
