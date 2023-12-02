// https://leetcode.com/problems/find-the-shortest-superstring/description/

#include <bits/stdc++.h>
using namespace std;

string makeSuffix(string s1, string s2)
{
    // s1+s2

    int common = 0;

    for (int len = 1; len <= min((int)s1.size(), (int)s2.size()); len++)
    {
        string t1 = s1.substr(s1.size() - len, s1.size());
        string t2 = s2.substr(0, len);

        if (t1 == t2)
        {
            common = len;
        }
    }
    string suffix = s2.substr(common, s2.size());
    return suffix;
}

vector<vector<string>> dp;

string TSP(vector<vector<string>> &cost, int mask, int index)
{
    int addedEmptySize = cost.size();

    if (mask == ((1ll << addedEmptySize) - 1))
    {
        return "";
    }

    if (dp[index][mask] != "")
    {
        return dp[index][mask];
    }

    int makelen = 1e9;
    string make;
    for (int i = 1; i <= addedEmptySize - 1; i++)
    {
        if ((mask & (1 << i)) == 0)
        {
            string suffix = cost[index][i];

            auto p = TSP(cost, mask | (1 << i), i);

            if (p.size() + suffix.size() < makelen)
            {
                makelen = p.size() + suffix.size();
                make = suffix + p;
            }
        }
    }

    return dp[index][mask] = make;
}

class Solution
{
public:
    string shortestSuperstring(vector<string> &words)
    {

        dp.clear(), dp.resize(13, vector<string>(1 << 13, ""));
        int n = words.size();

        vector<vector<string>> cost(n + 1, vector<string>(n + 1));

        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                if (i != j)
                {
                    string s1, s2;
                    if (i == 0)
                        s1 = "";
                    else
                        s1 = words[i - 1];

                    if (j == 0)
                        s2 = "";
                    else
                        s2 = words[j - 1];

                    cost[i][j] = makeSuffix(s1, s2);
                }
            }
        }

        // implement TSP from 0 ("")
        return (TSP(cost, 1, 0));
    }
};