#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxSumAfterPartitioning(vector<int> &arr, int k)
    {
        int n = arr.size();
        arr.insert(arr.begin(), 0);

        int Max[n + 1][n + 1];
        memset(Max, 0, sizeof(Max));
        for (int i = 1; i <= n; i++)
            Max[i][i] = arr[i];

        for (int len = 2; len <= k; len++)
        {
            for (int i = 1; i + len - 1 <= n; i++)
            {
                Max[i][i + len - 1] = max(Max[i + 1][i + len - 1], arr[i]);
            }
        }

        int dp[n + 1];
        memset(dp, 0, sizeof(dp));
        dp[1] = arr[1];
        for (int i = 2; i <= n; i++)
        {
            for (int j = i - 1; i - j <= k && j >= 0; j--)
            {
                dp[i] = max(dp[i], dp[j] + (i - j) * Max[j + 1][i]);
            }
        }
        return dp[n];
    }
};
