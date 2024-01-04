/*You are given a string s containing lowercase letters and an integer k. You need to :

First, change some characters of s to other lowercase English letters.
Then divide s into k non-empty disjoint substrings such that each substring is a palindrome.
Return the minimal number of characters that you need to change to divide the string.
https://leetcode.com/problems/palindrome-partitioning-iii/description/*/

#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
class Solution
{
public:
    int palindromePartition(string s, int k)
    {
        int n = s.size();
        int dp[n + 1][k + 1], min_changes[n + 1][n + 1]; // minimum changes reqd to make substring i...j palindrome

        min_changes[1][1] = 0;
        for (int i = 2; i <= n; i++)
        {
            min_changes[i][i] = 0;
            min_changes[i - 1][i] = 1 - (s[i - 1] == s[i - 2]);
        }

        for (int len = 3; len <= n; len++)
        {
            for (int i = 1; i + len - 1 <= n; i++)
            {
                int j = i + len - 1;
                min_changes[i][j] = min_changes[i + 1][j - 1] + 1 - (s[i - 1] == s[j - 1]);
            }
        }

        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= k; j++)
                dp[i][j] = INF;

        dp[0][0] = 0;
        for (int splits = 1; splits <= k; splits++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = i; j >= 1; j--)
                {
                    dp[i][splits] = min(dp[i][splits], dp[j - 1][splits - 1] + min_changes[j][i]);
                }
            }
        }
        return dp[n][k];
    }
};