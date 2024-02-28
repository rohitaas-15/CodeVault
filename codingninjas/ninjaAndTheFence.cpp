/*Ninja has given a fence, and he gave a task to paint this fence. The fence has 'N' posts, and Ninja has 'K' colors. Ninja wants to paint the fence so that not more than two adjacent posts have the same color.

Ninja wonders how many ways are there to do the above task, so he asked for your help.

Your task is to find the number of ways Ninja can paint the fence. Print the answer modulo 10^9 + 7.

Example:
Input: 'N' = 3, 'K' = 2
Output: 6

Say we have the colors with the numbers 1 and 0. We can paint the fence with 3 posts with the following different combinations.

110
001
101
100
010
011
https://www.codingninjas.com/studio/problem-of-the-day/hard?leftPanelTabValue=PROBLEM*/
#include <bits/stdc++.h>
using namespace std;
const long M = 1e9 + 7;
#include <bits/stdc++.h>
int numberOfWays(int n, int k)
{
    vector<vector<long>> dp(n + 1, vector<long>(2)); // last 2 are same, last 2 are different === [0][1]

    if (n == 1)
        return k;
    dp[1][0] = 0;
    dp[1][1] = k;
    for (int i = 2; i <= n; i++)
    {
        dp[i][0] = (dp[i - 1][1]) % M;
        dp[i][1] = ((long)(k - 1) * ((dp[i - 1][0] + dp[i - 1][1]) % M)) % M;
    }
    return (dp[n][0] + dp[n][1]) % M;
}
