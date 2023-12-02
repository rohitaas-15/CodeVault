/*https://codeforces.com/contest/1249/problem/D2

You are given 𝑛 segments on the coordinate axis 𝑂𝑋. Segments can intersect, lie inside each other and even coincide. The 𝑖-th segment is [𝑙𝑖;𝑟𝑖] (𝑙𝑖≤𝑟𝑖) and it covers all integer points 𝑗 such that 𝑙𝑖≤𝑗≤𝑟𝑖.

The integer point is called bad if it is covered by strictly more than 𝑘 segments.

Your task is to remove the minimum number of segments so that there are no bad points at all.

Input
The first line of the input contains two integers 𝑛 and 𝑘 (1≤𝑘≤𝑛≤2⋅105) — the number of segments and the maximum number of segments by which each integer point can be covered.

The next 𝑛 lines contain segments. The 𝑖-th line contains two integers 𝑙𝑖 and 𝑟𝑖 (1≤𝑙𝑖≤𝑟𝑖≤2⋅105) — the endpoints of the 𝑖-th segment.

Output
In the first line print one integer 𝑚 (0≤𝑚≤𝑛) — the minimum number of segments you need to remove so that there are no bad points.

In the second line print 𝑚 distinct integers 𝑝1,𝑝2,…,𝑝𝑚 (1≤𝑝𝑖≤𝑛) — indices of segments you remove in any order. If there are multiple answers, you can print any of them.*/


#include<bits/stdc++.h>
using namespace std;


bool compare(vector<int> &a, vector<int> &b)
{
    return a[1]<b[1];
}
int solve(int n,int k, vector<vector<int>> segments){
    
    
    vector<int> badPoints;
    
    vector<int> bptimes;
    
    vector<int> cnt(1e5+2,0);
    
    for(auto i : segments)
    {
        cnt[i[0]]++;
        cnt[i[1]+1]--;
    }
    
    for(int i =1;i<cnt.size();i++)
    {
        cnt[i]=cnt[i-1]+cnt[i];
        
    }
    badPoints.push_back(-1);
    bptimes.push_back(-1);
    for(int i =0;i<cnt.size();i++)
    {
        if(cnt[i]>k)
        {
            badPoints.push_back(i);
            bptimes.push_back(cnt[i]-k);
        }
    }
    vector<int> additional(badPoints.size()+1,0);
    
    sort(segments.begin(),segments.end(),compare);
    
    int segi=segments.size()-1;
    
    int prevsum=0;
    
    int ans =0;
    
    for(int i =badPoints.size()-1;i>=1;i--)
    {
        set<int> starting;
        while(segi>=0 && segments[segi][1]>=badPoints[i])
        {
           starting.insert(segments[segi][0]);
           segi--;
            
        }
        
        prevsum+=additional[i];
        
        int times = bptimes[i]-prevsum;
        
        for(auto j : starting)
        {
            if(!times)
            {
                break;
            }
            
            additional[i-1]++;
            
            auto it = lower_bound(badPoints.begin(),badPoints.begin()+i,j)-badPoints.begin();
            additional[it-1]--;
            
            ans++;
            times--;
        }
        
    }
    
    return ans;
    
    
    
    
    
    
}
