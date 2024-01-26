//{ Driver Code Starts
// Initial Template for C++
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++
vector<vector<vector<int>>> dp;
string makeString(int i, int j)
{
    if (i == j)
    {
        char c = i + 'A';
        string temp(1, c);
        return temp;
    }

    string first = makeString(i, dp[i][j][3]);
    if (first.size() != 1)
    {
        first = "(" + first + ")";
    }

    string second = makeString(dp[i][j][3] + 1, j);
    if (second.size() != 1)
    {
        second = "(" + second + ")";
    }
    return first + second;
}
class Solution
{
public:
    string matrixChainOrder(int p[], int n)
    {

        dp.clear(), dp.resize(n + 1, vector<vector<int>>(n + 1, vector<int>(4))); //stores the information for matrices from i....j
                                                                                  // minimum multiplication, row, column, index k such that i...k and k+1..j gives min
        for (int i = 0; i < n - 1; i++)
        {
            dp[i][i] = {0, p[i], p[i + 1], 0};
        }

        for (int len = 2; len <= n - 1; len++)
        {
            for (int i = 0; i + len - 1 <= n - 2; i++)
            {
                int j = i + len - 1;
                int mn = 1e9, index = n;
                for (int k = i; k <= j - 1; k++)
                {
                    if (dp[i][k][0] + dp[k + 1][j][0] + dp[i][k][1] * dp[i][k][2] * dp[k + 1][j][2] < mn)
                    {
                        mn = dp[i][k][0] + dp[k + 1][j][0] + dp[i][k][1] * dp[i][k][2] * dp[k + 1][j][2];
                        index = k;
                    }
                }
                dp[i][j] = {mn, p[i], p[j + 1], index};
            }
        }

        return "(" + makeString(0, n - 2) + ")";
    }
};

//{ Driver Code Starts.

int get(int p[], int n)
{
    int m[n][n], ans = 1e9;
    for (int i = 1; i < n; i++)
        m[i][i] = 0;
    for (int L = 2; L < n; L++)
    {
        for (int i = 1; i < n - L + 1; i++)
        {
            m[i][i + L - 1] = INT_MAX;
            for (int k = i; k <= i + L - 2; k++)
            {
                int q = m[i][k] + m[k + 1][i + L - 1] + p[i - 1] * p[k] * p[i + L - 1];
                if (q < m[i][i + L - 1])
                {
                    m[i][i + L - 1] = q;
                }
            }
        }
    }
    return m[1][n - 1];
}

int find(string s, int p[])
{
    vector<pair<int, int>> arr;
    int ans = 0;
    for (auto t : s)
    {
        if (t == '(')
        {
            arr.push_back({-1, -1});
        }
        else if (t == ')')
        {
            pair<int, int> b = arr.back();
            arr.pop_back();
            pair<int, int> a = arr.back();
            arr.pop_back();
            arr.pop_back();
            arr.push_back({a.first, b.second});
            ans += a.first * a.second * b.second;
        }
        else
        {
            arr.push_back({p[int(t - 'A')], p[int(t - 'A') + 1]});
        }
    }
    return ans;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int p[n];
        for (int i = 0; i < n; i++)
        {
            cin >> p[i];
        }
        Solution ob;
        string result = ob.matrixChainOrder(p, n);
        if (find(result, p) == get(p, n))
        {
            cout << "True" << endl;
        }
        else
        {
            cout << "False" << endl;
        }
    }
    return 0;
}
// } Driver Code Ends