//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends

const long N = 5e5 + 2;
long p2[N];
long p2M2[N]; //((2^i)^(M-2))%M
int cnt = 0;
const long M = 1e9 + 7;
long power(long a, long b)
{
    if (b == 0)
        return 1;
    if (b == 1)
        return a;
    long sp = (power(a, b / 2));
    return ((sp * sp) % M * power(a, b % 2)) % M;
}

class Solution
{
public:
    vector<int> search(string pattern, string text)
    {
        vector<int> ans;

        if (!cnt)
        {
            p2[0] = p2M2[0] = 1;
            for (int i = 1; i < N; i++)
            {
                p2[i] = (p2[i - 1] * 2ll) % M;
            }

            long _2M2 = power(2, M - 2);

            for (int i = 1; i < N; i++)
            {
                p2M2[i] = (p2M2[i - 1] * _2M2) % M;
            }
            cnt++;
        }

        int m = pattern.size(), n = text.size();
        long patHash = 0;
        long textHash = 0;
        for (int i = 0; i < m; i++)
        {
            patHash = (patHash + ((pattern[i] - 'a' + 1) * p2[i]) % M) % M;
            textHash = (textHash + ((text[i] - 'a' + 1) * p2[i]) % M) % M;
        }

        if (patHash == textHash && text.substr(0, m) == pattern)
        {
            ans.push_back(1);
        }

        for (int i = m; i < n; i++)
        {
            textHash = (textHash - (((text[i - m] - 'a' + 1) * p2[i - m]) % M) + M) % M;
            textHash = (textHash + ((text[i] - 'a' + 1) * p2[i]) % M) % M;
            long thisHash = (textHash * p2M2[i - m + 1]) % M;

            if (thisHash == patHash && text.substr(i - m + 1, m) == pattern)
            {
                ans.push_back(i - m + 2);
            }
        }
        return ans;
    }
};

//{ Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        string S, pat;
        cin >> S >> pat;
        Solution ob;
        vector<int> res = ob.search(pat, S);
        for (int i : res)
            cout << i << " ";
        cout << endl;
    }
    return 0;
}

// Contributed By: Pranay Bansal

// } Driver Code Ends