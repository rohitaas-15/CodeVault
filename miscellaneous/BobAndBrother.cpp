/*Bob and his Brother


Bob and his brother love each other a lot. As they are super-geeks, they only like to play with arrays. They are given two arrays a and b  by their father of size n and m respectively. The array a is given to Bob and b to his brother.

As Bob is really a naughty kid, he wants the minimum value of his array a should be at least as much as the maximum value of his brother's array b.

Now you have to help Bob in achieving this condition. You can perform multiple operations on the arrays. In a single operation, you are allowed to decrease or increase any element of any of the arrays by 1. Note that you are allowed to apply the operation on any index of the array multiple times.

You need to find the minimum number of operations required to satisfy Bob's condition so that the brothers can play peacefully without fighting.

Return the minimum number of operations required.

Constraints:

1<= n, m <= 10^5

1<= ai <= 10^9

1<= bi <= 10^9*/

#include<bits/stdc++.h>
using namespace std;

#define ll long long 



ll minOperations(int mid, vector<int> &a, vector<int> &b)
{
    ll op =0;
    for(int i =0;i<a.size();i++)
    {
        op+=max(0ll,(ll)(mid-a[i]));
    }
    
     for(int i =0;i<b.size();i++)
    {
        op+=max(0ll,(ll)(b[i]-mid));
    }
    return op;
    
}

long long solve(int n,int m,vector<int> a,vector<int> b){
    
  int left= 1;
  int right = 1e9;
  
  while(left<=right)
  {

      int mid1 = left + (right-left)/3;
      int mid2=(left + (2*(right-left))/3);
    
      
      if(mid1==mid2)
      {
          return minOperations(mid1,a,b);
      }
      
      
      if(minOperations(mid1,a,b)<minOperations(mid2,a,b))
      {
          right = mid2-1;
      }
      else
      {
          left = mid1+1;
      }
  } 

  return 0;
    
    
}

