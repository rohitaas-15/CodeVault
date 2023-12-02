//https://codeforces.com/problemset/problem/300/C

#include<bits/stdc++.h>
using namespace std;
#define ll long long


ll M = 1e9+7;

ll N = 1e6;

vector<ll> fact(N+1,1);

ll power(ll a,ll b , ll M=LLONG_MAX)
{
  if(!b)return 1;
  ll sp = power(a,b/2,M); sp = (sp*sp)%M;
  if(b&1)return ((a%M) * sp)%M;
  else return sp;
}


ll nCr(ll n, ll r)
{
    return(((fact[n]*(power(fact[n-r],M-2,M)))%M)*power(fact[r],M-2,M))%M;
}

bool good(ll n, ll a, ll b)
{
    while(n)
    {
        ll num = n%10;
        
        if(num==a || num==b)
        {
            n/=10;
        }
        else return false;
    }
    return true;
}




int solve(int a,int b,int n){
    
    
    fact.clear();
    fact.resize(1e6+1,1);
    
    for(ll i =2;i<=N;i++)
    {
        fact[i]=(fact[i-1]*i)%M;
    }
    
    
    
    ll ans =0;
    
    for(ll i =0;i<=n;i++ )
    {
        ll sum = a*i;
        ll rsum = (n-i)*b;
        
        if(good(sum+rsum,a,b))
        {
            ans = (ans+ nCr(n,i))%M;
        }
    }
    return ans;
    
}
