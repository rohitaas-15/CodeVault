/*Given a string str consisting of digits, you can divide it into sub-groups by separating the string into substrings. For example, "112" can be divided as {"1", "1", "2"}, {"11", "2"}, {"1", "12"}, and {"112"}.

A valid grouping can be done if you are able to divide sub-groups where the sum of digits in a sub-group is less than the sum of the digits of the sub-group immediately right to it. Your task is to determine the total number of valid groupings that could be done for a given string.
https://www.geeksforgeeks.org/problems/count-digit-groupings-of-a-number1520/1*/
//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends

class Solution
{
public:
    int TotalCount(string str)
    {
        int n = str.size();
        int limit = 10 * n;
        int dp[n + 1][limit + 1];
        memset(dp, 0, sizeof(dp));

        for (int i = 0; i <= limit; i++)
        {
            dp[0][i] = 1;
        }

        for (int i = 1; i <= n; i++)
        {
            for (int threshold = 0; threshold <= limit; threshold++)
            {
                int sum = 0;
                for (int j = i; j >= 1; j--)
                {
                    sum += str[j - 1] - '0';
                    if (sum <= threshold)
                    {
                        dp[i][threshold] += dp[j - 1][sum];
                    }
                }
            }
        }

        return dp[n][limit];
    }
};

//{ Driver Code Starts.
int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        string str;
        cin >> str;
        Solution ob;
        int ans = ob.TotalCount(str);
        cout << ans << "\n";
    }
    return 0;
}
// } Driver Code Ends