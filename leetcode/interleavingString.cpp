/*
Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.

An interleaving of two strings s and t is a configuration where s and t are divided into n and m 
substrings
 respectively, such that:

s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1
The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...
Note: a + b is the concatenation of strings a and b.https://leetcode.com/problems/interleaving-string/?show=1*/
#include <bits/stdc++.h>
using namespace std;

string S1, S2, S3;
const int N = 2e2 + 2;
int dp[N][N][N][2];
bool make(int i, int j, int k, int parity)
{

    if (k == S3.size())
    {
        return true;
    }

    if (dp[i][j][k][parity] != -1)
    {
        return dp[i][j][k][parity];
    }

    if (!parity)
    {
        if (S1[i] == S3[k])
        {
            return dp[i][j][k][parity] = make(i + 1, j, k + 1, parity) || make(i + 1, j, k + 1, 1);
        }
        else
        {
            return dp[i][j][k][parity] = false;
        }
    }
    else
    {
        if (S2[j] == S3[k])
        {
            return dp[i][j][k][parity] = make(i, j + 1, k + 1, parity) || make(i, j + 1, k + 1, 0);
        }
        else
        {
            return dp[i][j][k][parity] = false;
        }
    }
}

class Solution
{
public:
    bool isInterleave(string s1, string s2, string s3)
    {

        if (s1.size() + s2.size() != s3.size())
        {
            return 0;
        }
        S1 = s1, S2 = s2, S3 = s3;
        memset(dp, -1, sizeof(dp));
        int ans = make(0, 0, 0, 0); //first s then t
        memset(dp, -1, sizeof(dp));
        ans = ans || make(0, 0, 0, 1); //first t then s
        return ans;
    }
};