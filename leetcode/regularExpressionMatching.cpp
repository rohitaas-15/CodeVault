// https://leetcode.com/problems/regular-expression-matching/description/
/*Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:

'.' Matches any single character.​​​​
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).*/
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool isMatch(string s, string p)
    {
        int m = s.size(), n = p.size();

        int dp[n + 1][m + 1];
        memset(dp, 0, sizeof(dp));

        dp[0][0] = 1;

        for (int i = 1; i <= n; i++)
        {
            if (p[i - 1] == '*')
            {
                dp[i][0] = dp[i - 2][0]; //if no character is to be matched and length of s is 0
            }

            for (int j = 1; j <= m; j++)
            {
                if (p[i - 1] == '.' || p[i - 1] == s[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else if (p[i - 1] == '*')
                {
                    dp[i][j] = dp[i - 2][j]; //no character to be matched
                    if (p[i - 2] == s[j - 1] || p[i - 2] == '.' || p[i - 2] == '*')
                    {
                        dp[i][j] |= dp[i][j - 1]; //match one character, and dont change the index of p
                    }
                }
            }
        }
        return dp[n][m];
    }
};