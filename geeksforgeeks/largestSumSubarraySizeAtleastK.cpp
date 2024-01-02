//{ Driver Code Starts
// C++ program to find largest subarray sum with
// at-least k elements in it.
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
public:
    long long int maxSumWithK(long long int a[], long long int n, long long int k)
    {
        for (int i = 1; i < n; i++)
        {
            a[i] = a[i - 1] + a[i];
        }

        vector<long long int> minPre(n + 1);
        minPre[0] = 0;
        for (int i = 0; i < n; i++)
        {
            minPre[i + 1] = min(minPre[i], a[i]);
        }

        long long int dp[n + 1];
        memset(dp, 0, sizeof(dp));
        dp[k - 1] = a[k - 1];
        for (int i = k; i < n; i++)
        {
            int start = i - k;
            dp[i] = max(dp[i - 1], a[i] - minPre[start + 1]);
        }
        return dp[n - 1];
    }
};

//{ Driver Code Starts.

// Driver code
int main()
{
    long long int t;
    cin >> t;
    while (t--)
    {
        long long int n, k, i;
        cin >> n;
        long long int a[n];
        for (i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        cin >> k;
        Solution ob;
        cout << ob.maxSumWithK(a, n, k) << endl;
    }
    return 0;
}

// } Driver Code Ends