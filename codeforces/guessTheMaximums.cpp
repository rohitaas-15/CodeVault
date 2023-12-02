/*https://codeforces.com/contest/1363/problem/D


This is an interactive problem.

Ayush devised a new scheme to set the password of his lock. The lock has 𝑘 slots where each slot can hold integers from 1 to 𝑛. The password 𝑃 is a sequence of 𝑘 integers each in the range [1,𝑛], 𝑖-th element of which goes into the 𝑖-th slot of the lock.

To set the password of his lock, Ayush comes up with an array 𝐴 of 𝑛 integers each in the range [1,𝑛] (not necessarily distinct). He then picks 𝑘 non-empty mutually disjoint subsets of indices 𝑆1,𝑆2,...,𝑆𝑘 (𝑆𝑖∩𝑖≠𝑗𝑆𝑗=∅) and sets his password as 𝑃𝑖=max𝑗∉𝑆𝑖𝐴[𝑗]. In other words, the 𝑖-th integer in the password is equal to the maximum over all elements of 𝐴 whose indices do not belong to 𝑆𝑖.

You are given the subsets of indices chosen by Ayush. You need to guess the password. To make a query, you can choose a non-empty subset of indices of the array and ask the maximum of all elements of the array with index in this subset. You can ask no more than 12 queries.

Input
The first line of the input contains a single integer 𝑡 (1≤𝑡≤10) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers 𝑛 and 𝑘 (2≤𝑛≤1000,1≤𝑘≤𝑛) — the size of the array and the number of subsets. 𝑘 lines follow. The 𝑖-th line contains an integer 𝑐 (1≤𝑐<𝑛) — the size of subset 𝑆𝑖, followed by 𝑐 distinct integers in the range [1,𝑛]  — indices from the subset 𝑆𝑖.

It is guaranteed that the intersection of any two subsets is empty.

Interaction
To ask a query print a single line:

In the beginning print "? c " (without quotes) where 𝑐 (1≤𝑐≤𝑛) denotes the size of the subset of indices being queried, followed by 𝑐 distinct space-separated integers in the range [1,𝑛].
For each query, you will receive an integer 𝑥 — the maximum of value in the array among all the indices queried. If the subset of indices queried is invalid or you exceeded the number of queries (for example one of the indices is greater than 𝑛) then you will get 𝑥=−1. In this case, you should terminate the program immediately.

When you have guessed the password, print a single line "! " (without quotes), followed by 𝑘 space-separated integers  — the password sequence.

Guessing the password does not count towards the number of queries asked.

After this, you should read a string. If you guess the password correctly, you will receive the string "Correct". In this case, you should continue solving the remaining test cases. If the guessed password is incorrect, you will receive the string "Incorrect". In this case, you should terminate the program immediately.

The interactor is not adaptive. The array 𝐴 does not change with queries.

After printing a query do not forget to output end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

fflush(stdout) or cout.flush() in C++;
System.out.flush() in Java;
flush(output) in Pascal;
stdout.flush() in Python;
see documentation for other languages.
*/



//rohitaas_beri
#include<bits/stdc++.h>
//#include<ext/pb_ds/assoc_container.hpp>
//#include<ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
using namespace std;
//typedef tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update> o_set;
#define ll  long long
#define int ll
#define um(a,b) unordered_map<a,b>
#define fastio() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define all(v) v.begin(),v.end()
#define f(a,b) for(int i=a;i<=b;i++)
#define pb push_back
#define mp make_pair
#define pii pair<ll,ll>
#define ff first
#define ss second
#define lb(v,x) lower_bound(v.begin(),v.end(),x)
#define ub(v,x) upper_bound(v.begin(),v.end(),x)
#define show(x) cout<<x<<"\n"
#define pv(v,x,n) f(x,n-1){cout<<v[i]<<" ";}
#define cn(v,x,n) f(x,n){cin>>v[i];}
#define vr vector<ll>
#define check() cout<<"hi"<<"\n"
#define MOD 1000000007
#define len() length()
#define con continue
#define maxv(v) *max_element(all(v));
#define minv(v) *min_element(all(v));
#define sumv(v) accumulate(all(v),0)
#define test() ll t;cin>>t;while(t--)
#define pf pop_front
#define popb pop_back
#define popf pop_front
#define br break
#define rev(x)  reverse(all(x))
#define PI 3.141592653
vr bitsrev(vr arr,ll x){while(x>0){arr.pb(x%2);x/=2;}return arr;}
void equateLen(vr &el,vr &ar){if(el.size()!=ar.size()){if(el.size()<ar.size()){while(el.size()!=ar.size()){el.pb(0);}}else{while(el.size()!=ar.size()){ar.pb(0);}}}}
ll search(vr arr, ll l, ll r, ll x){if (r >= l) {ll mid = l + (r - l) / 2;if (arr[mid] == x)return mid;if (arr[mid] > x)return search(arr, l, mid - 1, x);return search(arr, mid + 1, r, x);} return -1;}
ll gcd(ll a, ll b){if(!b)return a;return gcd(b, a % b);}
ll lcm(ll a , ll b){return (a*b)/ gcd(a,b);}
ll power(ll x, ll y, ll p){ll res = 1;x = x % p;while (y > 0){ if (y & 1) res = (res*x) % p; y = y>>1;x = (x*x) % p; } return res; }
ll modInverse(ll n, ll p){return power(n, p-2, p);}
ll CmP(ll n, ll r, ll p=MOD){if (r==0)return 1;ll fac[n+1];fac[0] = 1;for (ll i=1 ; i<=n; i++)fac[i] = fac[i-1]*i%p; return (fac[n]* modInverse(fac[r], p) % p *modInverse(fac[n-r], p) % p) % p; }
ll ask(vr v)
{
	cout<<"?"<<" "<<v.size()<<" ";
	pv(v,0,v.size());
	cout<<endl;
	ll x;
	cin>>x;
	return x;
}
signed main()
{
	fastio();///*
	/*#ifndef ONLINE_JUDGE
	 freopen("input.txt","r",stdin);
	 freopen("output.txt","w",stdout);
	 #endif
	 */



	 int t=1;
	 cin>>t;
	 int cccc=t;

	while(t--)
	 {
	 	  ll n,k;
	 	  cin>>n>>k;
	 	  vr answer(k+1);
	 	  vector<vr> subsets(k+1);
	 	  f(1,k)
	 	  {
	 	  	ll x;
	 	  	cin>>x;
	 	  	ll len=x;
	 	  	for(ll j=0;j<len;j++)
	 	  	{
	 	  		ll x;
	 	  		cin>>x;
	 	  		subsets[i].pb(x);
	 	  	}
	 	  }
	 	  vr temp;
	 	  f(1,n)
	 	  {
	 	  	temp.pb(i);
	 	  }
	 	  ll jawaab=ask(temp);
	 	  if(jawaab==-1)
	 	  {
	 	  	exit(0);
	 	  }
	 	  ll maxx=jawaab;
	 	  ll high=n;
	 	  ll low=1;
	 	  ll mid;
	 	  while(low<high)
	 	  {
	 	      //show(maxx);
	 	  	mid=(low+high)/2;
	 	  	vr temp;
	 	  	f(low,mid)
	 	  	{
	 	  		temp.pb(i);
	 	  	}
	 	  	ll jawaab=ask(temp);
              if(jawaab==-1)
		 	  {
		 	  	exit(0);
		 	  }
		 	  if(jawaab==maxx)
		 	  {
		 	  	high=mid;

		 	  }
		 	  else
		 	  {
		 	  	low=mid+1;
		 	  }
	 	  }
	 	  ll subindex;
	 	  f(1,k)
	 	  {
	 	  	ll f=0;
	 	  	for(ll j=0;j<subsets[i].size();j++)
	 	  	{
	 	  		if(subsets[i][j]==high)
	 	  		{
	 	  			subindex=i;
	 	  			f=1;
	 	  			br;
	 	  		}
	 	  	}
	 	  	if(f)
	 	  	{
	 	  		br;
	 	  	}
	 	  }
	 	  f(1,k)
	 	  {
	 	  	if(i!=subindex)
	 	  	{
	 	  		answer[i]=maxx;
	 	  	}
	 	  }
	 	  vr temp1;
	 	  f(1,n)
	 	  {
	 	  	ll f=0;
	 	  	for(ll j=0;j<subsets[subindex].size();j++)
	 	  	{
	 	  		if(i==subsets[subindex][j])
	 	  		{
	 	  			f=1;
	 	  			br;
	 	  		}
	 	  	}
	 	  	if(f)
	 	  	{
	 	  		con;
	 	  	}
	 	  	else
	 	  	{
	 	  		temp1.pb(i);
	 	  	}
	 	  }
	 	   jawaab=ask(temp1);
	 	  if(jawaab==-1)
	 	  {
	 	  	exit(0);
	 	  }
	 	  answer[subindex]=jawaab;
	 	  cout<<"!"<<" ";
	 	  pv(answer,1,k+1);
	 	  cout<<endl;
	 	  string finj;
	 	  cin>>finj;
	 	  if(finj=="Correct")
	 	  {

	 	  }
	 	  else
	 	  {
	 	  	exit(0);
	 	  }

	 }





	 	/*cout<<"Case #"<<cccc-t<<": ";*/





}
