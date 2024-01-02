#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 3;

class Solution
{
public:
    int splitArray(vector<int> &nums, int k)
    {

        int n = nums.size();
        int dp[n + 1][k + 1];
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= k; j++)
                dp[i][j] = INF;
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            sum += nums[i - 1];
            dp[i][1] = sum;
        }
        for (int splits = 2; splits <= k; splits++)
        {
            for (int i = 1; i <= n; i++)
            {
                int sum = nums[i - 1];
                for (int j = i - 1; j >= 1; j--)
                {
                    dp[i][splits] = min(dp[i][splits], max(dp[j][splits - 1], sum));
                    sum += nums[j - 1];
                }
            }
        }
        return dp[n][k];
    }
};