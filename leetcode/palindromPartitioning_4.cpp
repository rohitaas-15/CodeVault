/*Given a string s, return true if it is possible to split the string s into three non-empty palindromic substrings. Otherwise, return false.​​​​​

A string is said to be palindrome if it the same string when reversed.
https://leetcode.com/problems/palindrome-partitioning-iv/description/*/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool checkPartitioning(string s)
    {

        int n = s.size();
        bool isPalindrome[n + 1][n + 1];
        isPalindrome[1][1] = 1;

        for (int i = 2; i <= n; i++)
        {
            isPalindrome[i][i] = 1;
            isPalindrome[i - 1][i] = (s[i - 1] == s[i - 2]);
        }

        for (int len = 3; len <= n; len++)
        {
            for (int i = 1; i + len - 1 <= n; i++)
            {
                int j = i + len - 1;
                isPalindrome[i][j] = isPalindrome[i + 1][j - 1] && (s[i - 1] == s[j - 1]);
            }
        }

        bool dp[n + 1][4];
        memset(dp, 0, sizeof(dp));

        dp[0][0] = 1;
        for (int splits = 1; splits <= 3; splits++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = i; j >= 1; j--)
                {
                    dp[i][splits] = dp[i][splits] || (dp[j - 1][splits - 1] && isPalindrome[j][i]);
                }
            }
        }
        return dp[n][3];
    }
};