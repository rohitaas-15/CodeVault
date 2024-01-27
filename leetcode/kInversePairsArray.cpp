/*For an integer array nums, an inverse pair is a pair of integers [i, j] where 0 <= i < j < nums.length and nums[i] > nums[j].

Given two integers n and k, return the number of different arrays consist of numbers from 1 to n such that there are exactly k inverse pairs. Since the answer can be huge, return it modulo 109 + 7.
https://leetcode.com/problems/k-inverse-pairs-array/description/?envType=daily-question&envId=2024-01-27*/
#include <bits/stdc++.h>
using namespace std;
const long long M = 1e9 + 7;
class Solution
{
public:
    int kInversePairs(int n, int k)
    {

        int dp[n + 1][k + 1]; // stores the answer for array of i elements and exactly j inverse pairs, but in Prefix Sum form
        memset(dp, 0, sizeof(dp));

        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 1;
        }

        for (int i = 1; i <= k; i++)
        {
            dp[1][i] = (dp[1][i - 1] + dp[1][i]) % M;
        }

        // the last element(the largest element) can have i places to go to and essentially will require different amount of inverse pairs from array
        // of length i-1
        for (int i = 2; i <= n; i++)
        {
            for (int j = 1; j <= k; j++)
            {
                int limit = max(0, j - i + 1);
                if (limit == 0)
                {
                    dp[i][j] = ((long long)dp[i - 1][j]) % M;
                }
                else
                    dp[i][j] = ((long long)dp[i - 1][j] - (long long)dp[i - 1][limit - 1] + M) % M;
            }

            for (int j = 1; j <= k; j++)
            {
                dp[i][j] = ((long long)dp[i][j - 1] + (long long)dp[i][j]) % M; // storing the answer for current row in prefix sum form to calculate
                                                                                //  the ansswer for next row in O(1)
            }
        }

        if (k == 0)
        {
            return dp[n][k];
        }
        else
            return ((long long)dp[n][k] - (long long)dp[n][k - 1] + M) % M;
    }
};