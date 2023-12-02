//https://atcoder.jp/contests/abc203/tasks/abc203_d


#include<bits/stdc++.h>
using namespace std;


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


vvi makeSum(vvi &bin, vvi &nz)
{
  int n = bin.size();
  vvi sumGrid;
  sumGrid = bin;

  sumGrid[0][0]=bin[0][0];

  nz[0][0]=(bin[0][0]==0);

  rep(i,1,n)
  {
    sumGrid[0][i]=sumGrid[0][i-1]+bin[0][i];
    sumGrid[i][0]=sumGrid[i-1][0]+bin[i][0];

    nz[0][i]=nz[0][i-1]+(bin[0][i]==0);
    nz[i][0]=nz[i-1][0]+(bin[i][0]==0);

  }


  rep(i,1,n)
  {
    rep(j,1,n)
    {
      sumGrid[i][j]=sumGrid[i][j-1]+sumGrid[i-1][j]-sumGrid[i-1][j-1]+sumGrid[i][j];

      nz[i][j]=nz[i][j-1]+nz[i-1][j]-nz[i-1][j-1]+(bin[i][j]==0);
    }
  }


  return sumGrid;
}


bool can(int mid, vvi &grid,int k)
{
  int n = grid.size();

  vvi bin;bin = grid;

  rep(i,0,n)
  {
    rep(j,0,n)
    {
      if(grid[i][j]<mid)
      {
        bin[i][j]=-1;
      }
      else if(grid[i][j]>mid)
      {
        bin[i][j]=1;
      }
      else bin[i][j]=0;

    }
  }


  vvi nz;
  nz=bin;

  bin = makeSum(bin,nz);

  rep(i,0,n)
  {
    rep(j,0,n)
    {
      int starti=i,startj=j;

      int endi= i+k-1,endj=j+k-1;



      if(endi>n-1 || endj>n-1)
      {
        continue;
      }

      int subsum=0;
      int same=0;

      if(starti==0 && startj==0)
      {
        subsum = bin[endi][endj];

        same = nz[endi][endj];
      }
      else if(starti==0)
      {
        subsum = bin[endi][endj]-bin[endi][startj-1];

        same = nz[endi][endj]-nz[endi][startj-1];
      }
      else if(startj==0)
      {
        subsum = bin[endi][endj]-bin[starti-1][endj];
        same= nz[endi][endj]-nz[starti-1][endj];
      }
      else
      {
        subsum= bin[endi][endj]-bin[endi][startj-1]-bin[starti-1][endj]+bin[starti-1][startj-1];
        same= nz[endi][endj]-nz[endi][startj-1]-nz[starti-1][endj]+nz[starti-1][startj-1];
      }


      if(subsum<0 && same>subsum)
      {
        return true;
      }
      else if(same>=subsum)
      {
        return true;
      }
    }
  }
  return false;


}




int solve(int n,int k, vector<vector<int>> grid){
    vi nums;
    
    
 rep(i,0,n)
 {
  rep(j,0,n)
  {
 
    nums.pb(grid[i][j]);
  }
 }

 sort(all(nums));

 int high = nums.size()-1;
 int low = 0;
 int ans = 1e9;

 while(high>=low)
 {
  int mid= (low+high)>>1ll;

  if(can(nums[mid], grid,k))
  {
    ans =nums[mid];
    high = mid-1;
  }
  else
  {
    low = mid+1;
  }
 }
 return (ans);


}
