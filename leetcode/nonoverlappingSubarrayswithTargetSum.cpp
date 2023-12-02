//https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/submissions/

/*You are given an array of integers arr and an integer target.

You have to find two non-overlapping sub-arrays of arr each with a sum equal target. There can be multiple answers so you have to find an answer where the sum of the lengths of the two sub-arrays is minimum.

Return the minimum sum of the lengths of the two required sub-arrays, or return -1 if you cannot find such two sub-arrays.

*/


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


vi work(vi &v,int target)
{
  int n = sz(v);
  vi dp(n,1e9);

  int i = 0,j=0,sum=0;

  while(j<n)
  {
    while(j<n && sum<target)
    {
      sum+=v[j++];
    }

    while(i<j && sum>target)
    {
      sum-=v[i++];
    }
    
    if(sum==target)
    {
      dp[j-1]=min(dp[j-1],j-i);
      sum-=v[i++];
    }
  }

  while(i<j && sum>target)
  {
    sum-=v[i++];
  }
  
  if(sum==target)
  {
    dp[j-1]=min(dp[j-1],j-i);
    sum-=v[i++];
  }

  int val = 1e9;

  rep(i,0,n)
  {
    val = min(val,dp[i]);
    dp[i]=val;
  }
  return dp;


}


class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
 int n,k;n=arr.size(),k=target;

  vi v=arr;
  vi dp1= work(v,k);

  rev(v);

  vi dp2 = work(v,k);

  rev(dp2);
  
  int ans = 1e9;

  rep(i,0,n-1)
  {
    ans = min(ans, dp1[i]+dp2[i+1]);
  }
  if(ans>=1e9)
  {
    ans = -1;
  }
  return (ans);
    }
};
