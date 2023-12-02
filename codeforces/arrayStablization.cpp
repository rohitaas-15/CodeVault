//https://codeforces.com/contest/1547/problem/F

/*
You are given an array of positive integers 𝑎=[𝑎0,𝑎1,…,𝑎𝑛−1] (𝑛≥2).

In one step, the array 𝑎 is replaced with another array of length 𝑛, in which each element is the greatest common divisor (GCD) of two neighboring elements (the element itself and its right neighbor; consider that the right neighbor of the (𝑛−1)-th element is the 0-th element).

Formally speaking, a new array 𝑏=[𝑏0,𝑏1,…,𝑏𝑛−1] is being built from array 𝑎=[𝑎0,𝑎1,…,𝑎𝑛−1] such that 𝑏𝑖 =gcd(𝑎𝑖,𝑎(𝑖+1)mod𝑛), where gcd(𝑥,𝑦) is the greatest common divisor of 𝑥 and 𝑦, and 𝑥mod𝑦 is the remainder of 𝑥 dividing by 𝑦. In one step the array 𝑏 is built and then the array 𝑎 is replaced with 𝑏 (that is, the assignment 𝑎 := 𝑏 is taking place).

For example, if 𝑎=[16,24,10,5] then 𝑏=[gcd(16,24), gcd(24,10), gcd(10,5), gcd(5,16)] =[8,2,5,1]. Thus, after one step the array 𝑎=[16,24,10,5] will be equal to [8,2,5,1].

For a given array 𝑎, find the minimum number of steps after which all values 𝑎𝑖 become equal (that is, 𝑎0=𝑎1=⋯=𝑎𝑛−1). If the original array 𝑎 consists of identical elements then consider the number of steps is equal to 0.

Input
The first line contains an integer 𝑡 (1≤𝑡≤104). Then 𝑡 test cases follow.

Each test case contains two lines. The first line contains an integer 𝑛 (2≤𝑛≤2⋅105) — length of the sequence 𝑎. The second line contains 𝑛 integers 𝑎0,𝑎1,…,𝑎𝑛−1 (1≤𝑎𝑖≤106).

It is guaranteed that the sum of 𝑛 over all test cases doesn't exceed 2⋅105.

Output
Print 𝑡 numbers — answers for each test case.*/


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

int GCD(int a , int b)
{
  if(a<b)swap(a,b);
  if(b==0)
  {
    return a;
  }
  return GCD(b,a%b);
}

template<typename T> struct SegmentTree{
  int n;
  vector<T> st;
   T ZERO=0;

  //constructor
  SegmentTree(int N)
  {
    n = N;
    st.resize(4*n+2,ZERO);
  }

//updating the parent
  T collect(T left, T right)
  {
    return GCD(left,right) ; //variable
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
  void update(int s, int e ,int index, T val, int node)
  {
    if(s>index || e<index)
    {
      return ;
    }

    if(s==e)
    {
      st[node]=val;
      return;
    }

    int mid = (s+e)>>1ll;

    update(s,mid,index,val,2*node+1);
    update(mid+1,e,index,val,2*node+2);

    st[node]=collect(st[2*node+1],st[2*node+2]);
  }

  void update(int index, T val)
  {
    update(0ll,n-1,index,val,0ll);
  }

};


bool canDo(int mid, vi v, SegmentTree<int> &tree)
{
  int n = v.size();
  
  int k =-1;

  rep(i,0,n)
  {
    if(i + mid-1>=n)
    {
      int s1= i, s2 = n-1;
      int rem = mid-(n-1-i+1);

      int e1 = 0, e2 = rem-1;

      int g1 = tree.query(s1,s2);
      int g2 = tree.query(e1,e2);

      if(GCD(g1,g2)!=k)
      {
        return false;
      }
    }
    else
    {
      if(k==-1)
      {
          k = tree.query(i,i+mid-1);
          continue;
      }
      else if(tree.query(i,i+mid-1)!=k)
      {
        return false;
      }
    }
  }
  return true;

}
  
   
void solve()
{
  int n;cin>>n;
  vi v(n);
  rep(i,0,n)
  {
    cin>>v[i];
  }

  SegmentTree<int> tree(n);
  tree.build(v);
  int low =0,high = n-1;
  int ans = n;
  while(low<=high)
  {
    int mid = (low+high)>>1;

    if(canDo(mid+1, v,tree))
    {
      ans = mid;
      high = mid-1;
    }
    else
    {
      low = mid+1;
    }
  }
  print(ans);
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
