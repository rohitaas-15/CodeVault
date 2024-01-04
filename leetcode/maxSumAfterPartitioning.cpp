/*Given an integer array arr, partition the array into (contiguous) subarrays of length at most k. After partitioning, each subarray has their values changed to become the maximum value of that subarray.

Return the largest sum of the given array after partitioning. Test cases are generated so that the answer fits in a 32-bit integer.
https://leetcode.com/problems/partition-array-for-maximum-sum/description/*/
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxSumAfterPartitioning(vector<int> &arr, int k)
    {
        int n = arr.size();
        arr.insert(arr.begin(), 0);
        int dp[n + 1];
        memset(dp, 0, sizeof(dp));
        dp[1] = arr[1];
        for (int i = 2; i <= n; i++)
        {
            int mx = arr[i];
            for (int j = i - 1; i - j <= k && j >= 0; j--)
            {
                dp[i] = max(dp[i], dp[j] + (i - j) * mx);
                mx = max(mx, arr[j]);
            }
        }
        return dp[n];
    }
};