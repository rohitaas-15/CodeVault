//https://atcoder.jp/contests/abc110/tasks/abc110_d

#include<bits/stdc++.h>
using namespace std;


#define ll long long
ll M = 1e9+7;

map<int,int> pf(ll num)
{
  map<int,int> freq;
  for(ll i =2;i*i<=num;i++)
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


vector<vector<ll> > dp;


int cflag=0;
void calculate(int n , int m)
{
    
    if(cflag)return ;
    
  
    
    for(int i = 0;i<=n;i++)
    {
        dp[i][1]=1;
    }
    
    for(int boxes = 2;boxes<=m;boxes++)
    {
      for(int apples = 0;apples<=n;apples++)
      {
        for(int last = 0;last<=apples;last++)
        {
            dp[apples][boxes]=(dp[apples][boxes]+dp[apples-last][boxes-1])%M;
        }
      }
        
    }
    cflag=1;
    
}

int solve(int n,int m){
    
    map<int,int> ans = pf(m);
    dp.resize(31,vector<ll>(1e5+1,0));
    
    calculate(30,1e5);
    
    ll a = 1;
    
    for(auto i : ans)
    {
        
        a= (a*dp[i.second][n])%M;
        
    }
    
    return a;
    
}

