/*https://www.geeksforgeeks.org/problems/longest-repeating-and-non-overlapping-substring3421/1
Given a string s of length n, find the longest repeating non-overlapping substring in it. In other words find 2 identical substrings of maximum length which do not overlap. Return the longest non-overlapping substring. Return "-1" if no such string exists.

Note: Multiple Answers are possible but you have to return the substring whose first occurrence is earlier.

For Example: "abhihiab", here both "ab" and "hi" are possible answers. But you will have to return "ab" because it's first occurrence appears before the first occurrence of "hi".*/


//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends

class Solution
{
public:
    string longestSubstring(string s, int n)
    {
        int dp[n + 1][n + 1];

        memset(dp, 0, sizeof(dp));

        int index = n, len = 0;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (s[i - 1] == s[j - 1] && i < j)
                {
                    dp[i][j] = min(j - i, dp[i - 1][j - 1] + 1);
                }
                else
                    dp[i][j] = 0;

                if (dp[i][j] > len)
                {
                    len = dp[i][j];
                }
            }
        }
        if (len == 0)
            return "-1";

        map<string, int> m;
        for (int i = 0; i + len - 1 < n; i++)
        {
            string check = s.substr(i, len);

            if (!m.count(check))
            {
                m[check] = i;
            }
            else if (m.count(check) && m[check] + len - 1 < i)
            {
                index = min(index, m[check]);
            }
        }
        return s.substr(index, len);
    }
};

//{ Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int N;
        string S;

        cin >> N;
        cin >> S;

        Solution ob;
        cout << ob.longestSubstring(S, N) << endl;
    }
    return 0;
}
// } Driver Code Ends