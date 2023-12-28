//https://leetcode.com/problems/maximum-sum-circular-subarray/description/
/*Given a circular integer array nums of length n, return the maximum possible sum of a non-empty subarray of nums.

A circular array means the end of the array connects to the beginning of the array. Formally, the next element of nums[i] is nums[(i + 1) % n] and the previous element of nums[i] is nums[(i - 1 + n) % n].

A subarray may only include each element of the fixed buffer nums at most once. Formally, for a subarray nums[i], nums[i + 1], ..., nums[j], there does not exist i <= k1, k2 <= j with k1 % n == k2 % n.*/


#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = nums.size();
        int preMx[n+1],sufMx[n+1];
 
        int mx =nums[0],curmax=nums[0];//Kadane's Algorithm answer
        preMx[0]=nums[0],sufMx[n-1]=nums[n-1];
        for(int i =1;i<n;i++)
        {
            curmax=max(curmax+nums[i],nums[i]);
            mx = max(curmax,mx);
            preMx[i]=preMx[i-1]+nums[i];
            sufMx[n-1-i]=sufMx[n-i]+nums[n-1-i];
        }

        for(int i =1;i<n;i++)
        {
            preMx[i]=max(preMx[i-1],preMx[i]);
            sufMx[n-1-i]=max(sufMx[n-i],sufMx[n-1-i]);
        }
        for(int i =0;i<n-1;i++)
        {
            mx = max(mx, preMx[i]+sufMx[i+1]);
        }
 
        return mx;
    }
};