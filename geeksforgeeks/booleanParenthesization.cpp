//{ Driver Code Starts
// Initial Template for C++

// https://www.geeksforgeeks.org/problems/boolean-parenthesization5610/1
/*Given a boolean expression s of length n with following symbols.
Symbols
    'T' ---> true
    'F' ---> false
and following operators filled between symbols
Operators
    &   ---> boolean AND
    |   ---> boolean OR
    ^   ---> boolean XOR
Count the number of ways we can parenthesize the expression so that the value of expression evaluates to true.

Note: The answer can be large, so return it with modulo 1003*/

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++
const long M = 1e3 + 3;
string S;
vector<vector<pair<long, long>>> dp;
pair<long, long> count(int start, int end)
{
    if (start == end)
    {
        if (S[start] == 'T')
        {
            return {0, 1};
        }
        else
            return {1, 0};
    }

    if (dp[start][end] != make_pair(-1l, -1l))
    {
        return dp[start][end];
    }

    long one = 0, zero = 0;

    for (int i = start + 1; i <= end - 1; i += 2)
    {
        if (S[i] == '&')
        {
            auto left = count(start, i - 1);
            auto right = count(i + 1, end);

            zero = (zero + left.first * right.second + left.second * right.first + left.first * right.first) % M;
            one = (one + left.second * right.second) % M;
        }
        else if (S[i] == '^')
        {
            auto left = count(start, i - 1);
            auto right = count(i + 1, end);

            zero = (zero + left.first * right.first + left.second * right.second) % M;
            one = (one + left.second * right.first + left.first * right.second) % M;
        }
        else if (S[i] == '|')
        {
            auto left = count(start, i - 1);
            auto right = count(i + 1, end);

            one = (one + left.first * right.second + left.second * right.first + left.second * right.second) % M;
            zero = (zero + left.first * right.first) % M;
        }
    }
    return dp[start][end] = {zero, one};
}
class Solution
{
public:
    int countWays(int n, string s)
    {
        dp.clear();
        dp.resize(n + 1, vector<pair<long, long>>(n + 1, {-1ll, -1ll}));
        S = s;
        return count(0, n - 1).second;
    }
};

//{ Driver Code Starts.

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;

        Solution ob;
        cout << ob.countWays(n, s) << "\n";
    }
    return 0;
}
// } Driver Code Ends