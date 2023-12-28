/*You are given 'N' stones labeled from 1 to 'N'. The 'i-th' stone has the weight W[i]. There are 'M' colors labeled by integers from 1 to 'M'. The 'i-th' stone has the color C[i] which is an integer between 1 to 'M', both inclusive.

You have been required to fill a Knapsack with these stones. The Knapsack can hold a total weight of 'X'.

You are required to select exactly 'M' stones; one of each color. The sum of the weights of the stones must not exceed 'X'. Since you paid a premium for a Knapsack with capacity 'X', you are required to fill the Knapsack as much as possible.

Write a program to calculate the best way to fill the Knapsack - that is, the unused capacity should be minimized.*/
// https://www.codingninjas.com/studio/problems/colorful-knapsack_630415?leftPanelTabValue=PROBLEM
#include <bits/stdc++.h>
using namespace std;

int colorfulKnapsack(int w[], int c[], int n, int m, int x)
{
    int N = 102, W = 1e4 + 2;
    int dp[N][W];
    memset(dp, -1, sizeof(dp));

    vector<int> colNos[m + 1];
    for (int i = 0; i < n; i++)
    {
        colNos[c[i]].push_back(i);
    }

    for (int weight = 0; weight <= x; weight++)
    {
        dp[0][weight] = 0;
        for (int col = 1; col <= m; col++)
        {
            for (auto i : colNos[col])
            {
                if (w[i] <= weight && dp[col - 1][weight - w[i]] != -1)
                {
                    dp[col][weight] =
                        max(dp[col][weight], w[i] + dp[col - 1][weight - w[i]]);
                }
            }
        }
    }

    if (dp[m][x] == -1)
    {
        return -1;
    }
    return x - dp[m][x];
}