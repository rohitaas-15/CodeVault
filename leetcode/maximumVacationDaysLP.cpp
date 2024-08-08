//https://www.lintcode.com/problem/874/

#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
class Solution
{
public:
    /**
     * @param flights: the airline status from the city i to the city j
     * @param days: days[i][j] represents the maximum days you could take vacation in the city i in the week j
     * @return: the maximum vacation days you could take during K weeks
     */
    int maxVacationDays(vector<vector<int>> &flights, vector<vector<int>> &days)
    {
        // Write your code here

        int n = flights.size();
        int k = days[0].size();
        int dp[n + 1][k + 1];
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= k; j++)
                dp[i][j] = -INF;
        }

        for (int i = 0; i <= n; i++)
        {
            dp[i][0] = 0;
        }

        for (int week = 1; week <= k; week++)
        {
            for (int dest = 0; dest < n; dest++)
            {
                if (week == 1)
                {
                    int src = 0;
                    if (dest == src || flights[src][dest])
                        dp[dest][week] = max(dp[dest][week], dp[src][week - 1] + days[dest][week - 1]);
                }
                else
                    for (int src = 0; src < n; src++)
                    {
                        if (dest == src || flights[src][dest])
                            dp[dest][week] = max(dp[dest][week], dp[src][week - 1] + days[dest][week - 1]);
                    }
            }
        }

        int ans = -INF;
        for (int i = 0; i < n; i++)
        {
            ans = max(ans, dp[i][k]);
        }
        if (ans == INF)
            ans = 0;
        return ans;
    }
};