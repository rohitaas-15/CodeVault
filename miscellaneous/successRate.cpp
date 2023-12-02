/*You are an experienced Coding Minutes user. Today you found out that during your activity on Coding Minutes you have made y submissions, out of which x have been successful. Thus, your current success rate on Coding Minutes is equal to x / y.

Your favorite rational number in the [0,1] range is p / q. Now you wonder: what is the smallest number of submissions you have to make if you want your success rate to be p / q.

Return the minimum number of submissions you need to make if you want your success rate to be equal to your favorite rational number or -1 if this is impossible to achieve.*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long

long long solve(int x,int y,int p, int q){
    
  ll low = 1;

  ll high = 1e9;
  ll ans =0;

  while(low<=high)
  {
    ll mid = (low+high)>>1ll;

    ll sub = mid*q-y;

    if(sub+x>=p*mid && x<=p*mid)
    {
      ans= sub;
      high = mid-1;
    }
    else
    {
      low = mid+1;
    }

  }
  return ans;

    
}
