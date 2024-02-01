/*Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).
https://leetcode.com/problems/wildcard-matching/description/*/
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool isMatch(string s, string p)
    {

        int n = p.size(), m = s.size();
        int dp[n + 1][m + 1], pre[n + 1][m + 1]; //dp- stores the answer for p until i, and s until j,
                                                 //pre- stores the cumulative answer for p until i, and s from length 0 to length j(for * matching)
        memset(dp, 0, sizeof(dp));
        memset(pre, 0, sizeof(pre));

        for (int i = 0; i <= m; i++)
        {
            pre[0][i] = 1;
        }

        dp[0][0] = 1;

        for (int i = 1; i <= n; i++)
        {
            if (p[i - 1] == '*')
            {
                dp[i][0] = dp[i - 1][0];
            }

            for (int j = 1; j <= m; j++)
            {
                if (p[i - 1] == '?' || p[i - 1] == s[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else if (p[i - 1] == '*')
                {
                    dp[i][j] = pre[i - 1][j];
                }
                pre[i][j] = pre[i][j - 1] | dp[i][j];
            }
        }
        return dp[n][m];
    }
};