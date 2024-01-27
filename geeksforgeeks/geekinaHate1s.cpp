/*It is a universal fact that Geekina hates 1s however it is also known that Geekina loves the integers having atmost k 1s (set-bits) in their binary representation. 

Geekina demanded nth such non-negative number from Geek, and being a good friend of Geek, now it's your responsibility to tell him that number.

Note: The test cases are generated such that the answer always exists and will fit in the 64-bit data type.*/

//https://www.geeksforgeeks.org/problems/geekina-hate-1s/1
//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends

long long dp[64][64];
long long countNumbers(int i, int k)
{
    if (i == 64)
    {
        return 1ll;
    }

    if (dp[i][k] != -1ll)
    {
        return dp[i][k];
    }

    if (k == 0)
    {
        return dp[i][k] = countNumbers(i + 1, k);
    }

    return dp[i][k] = countNumbers(i + 1, k) + countNumbers(i + 1, k - 1);
}

long long answer;
void Find(int i, int k, long long n)
{
    if (n == 1ll)
    {
        return;
    }

    long long count = countNumbers(i + 1, k); // put 0 at the (63-i)th place
    if (count >= (long long)n)
    {
        Find(i + 1, k, n);
    }
    else
    {
        answer += (1ll << (63ll - (long long)i)); // put 1
        Find(i + 1, k - 1, n - count);
    }
}
class Solution
{
public:
    long long findNthNumber(int n, int k)
    {
        if (k >= 32) //as n is <=1e9
        {
            return n - 1;
        }
        memset(dp, -1ll, sizeof(dp));
        answer = 0ll;
        Find(0, k, (long long)n);
        return answer;
    }
};

//{ Driver Code Starts.

int main()
{
    int t;
    scanf("%d ", &t);
    while (t--)
    {

        int n;
        scanf("%d", &n);

        int k;
        scanf("%d", &k);

        Solution obj;
        long long res = obj.findNthNumber(n, k);

        cout << res << endl;
    }
}

// } Driver Code Ends