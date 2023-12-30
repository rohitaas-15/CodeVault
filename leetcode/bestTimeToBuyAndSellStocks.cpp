/*You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

Find the maximum profit you can achieve. You may complete at most k transactions: i.e. you may buy at most k times and sell at most k times.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).*/
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/description/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size();
        int dp[n + 1][k + 1][3]; // max profit if elements till index i are considered, with max j transactions allowed and if\
                                 the current index is // 0-Not doing anything, 1- Buying, 2- Selling
        memset(dp, 0, sizeof(dp));
        for (int txn = 1; txn <= k; txn++)
        {
            dp[0][txn][2] = dp[0][txn][1] = -1e9;
            int maxBuy = -1e9;
            for (int i = 1; i <= n; i++)
            {
                dp[i][txn][0] = max(dp[i - 1][txn][2], dp[i - 1][txn][0]);
                dp[i][txn][1] = -prices[i - 1] + max({dp[i - 1][txn - 1][0], dp[i - 1][txn - 1][2]});
                dp[i][txn][2] = prices[i - 1] + maxBuy;
                maxBuy = max(maxBuy, dp[i][txn][1]);
            }
        }
        return max({dp[n][k][0], dp[n][k][1], dp[n][k][2]});
    }
};
