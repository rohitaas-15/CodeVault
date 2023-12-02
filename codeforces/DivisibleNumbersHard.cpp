/*
https://codeforces.com/contest/1744/problem/E2


This is an hard version of the problem. The only difference between an easy and a hard version is the constraints on 𝑎, 𝑏, 𝑐 and 𝑑.

You are given 4 positive integers 𝑎, 𝑏, 𝑐, 𝑑 with 𝑎<𝑐 and 𝑏<𝑑. Find any pair of numbers 𝑥 and 𝑦 that satisfies the following conditions:

𝑎<𝑥≤𝑐, 𝑏<𝑦≤𝑑,
𝑥⋅𝑦 is divisible by 𝑎⋅𝑏.
Note that required 𝑥 and 𝑦 may not exist.

Input
The first line of the input contains a single integer 𝑡 (1≤𝑡≤10), the number of test cases.

The descriptions of the test cases follow.

The only line of each test case contains four integers 𝑎, 𝑏, 𝑐 and 𝑑 (1≤𝑎<𝑐≤109, 1≤𝑏<𝑑≤109).

Output
For each test case print a pair of numbers 𝑎<𝑥≤𝑐 and 𝑏<𝑦≤𝑑 such that 𝑥⋅𝑦 is divisible by 𝑎⋅𝑏. If there are multiple answers, print any of them. If there is no such pair of numbers, then print -1 -1.*/






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
#define rep(i,a,b) for(int i =(a);i<(b);i++)
#define all(v) v.begin(),v.end()
#define rev(v) reverse(all(v))
#define print(value)  cout<<(value)<<nl
#define print2(v1,v2) cout<<(v1)<<" "<<(v2)<<nl
#define print3(v1,v2,v3) cout<<(v1)<<" "<<(v2)<<" "<<(v3)<<nl
#define printv(v)rep(it,0,v.size()){cout<<v[it]<<" ";}cout<<"\n"
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

map<int,int> pf(int num)
{
     map<int,int> freq;

    for(int i =2;i*i<=num;i++)
    {
        while(num%i==0)
        {
            freq[i]++;
            num/=i;
        }
    }

    if(num!=1)
    {
        freq[num]++;
    }

    return freq;
}

int power(int a,int b , int M=LLONG_MAX)
{
    if(!b)return 1;
    int sp = power(a,b/2,M); sp = (sp*sp)%M;
    if(b&1)return ((a%M) * sp)%M;
    else return sp;
}



pair<int,int> makeNum(vpii &factors,int index, int a , int b, int c, int d,int ab,int num)
{
    if(index==factors.size())
    {
        int n1 = num;
        int n2 = ab/n1;

        int check1 = ((a+1)/n1)*n1;
        int check2 = ((b+1)/n2)*n2;

        //bug(n1,n2,check1,check2);

        if(check1>=a+1 && check1<=c)
        {
            if(check2>=b+1 && check2<=d)
            {
                return {check1,check2};
            }
            else if(check2+n2>=b+1 && check2+n2<=d)
            {
                return {check1,check2+n2};
            }
        }
        else if(check1+n1>=a+1 && check1+n1<=c)
        {
             if(check2>=b+1 && check2<=d)
            {
                 return {check1+n1,check2};
            }
            else if(check2+n2>=b+1 && check2+n2<=d)
            {
                 return {check1+n1,check2+n2};
            }
        }
        return {-1,-1};
    }

    for(int i =0;i<=factors[index].second;i++)
    {
        int temp1=num*power(factors[index].first,i);

        auto ans = makeNum(factors,index+1,a,b,c,d,ab,temp1);

        if(ans.first!=-1)
        {
            return ans;
        }

    }
    return {-1,-1};
}




void solve()
{
    int a,b,c,d;cin>>a>>b>>c>>d;

    int x,y;
    int flag=0;

    int num = a*b;

    map<int,int> af=pf(a);
    map<int,int> bf =pf(b);

    for(auto i : bf)
    {
        if(!af.count(i.first))
        {
            af[i.first]=i.second;
        }
        else
        {
            af[i.first]+=i.second;
        }
    }

    vpii factors;

    for(auto i : af)
    {
        factors.pb({i.first,i.second});
        //bug(i.first,i.second);
    }

    auto ans = makeNum(factors,0,a,b,c,d,a*b,1);
    print2(ans.first,ans.second);

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

4) Upper bound of number of divisors of a number is n^(1/3)

*/



/* Good Questions :

1 ) https://www.codechef.com/submit/SECPLAYER

 */
