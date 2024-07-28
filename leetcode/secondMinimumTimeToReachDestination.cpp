#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
class Solution
{
public:
    int secondMinimum(int n, vector<vector<int>> &edges, int time, int change)
    {
        vector<vector<int>> adj(n + 1);
        for (auto i : edges)
        {
            adj[i[0]].push_back(i[1]);
            adj[i[1]].push_back(i[0]);
        }

        function<void(int, pair<int, int> &)> updateMinimums =
            [&](int no, pair<int, int> &mins)
        {
            int mn = mins.first, smn = mins.second;
            if (no < mn)
            {
                smn = mn, mn = no;
            }
            else if (no < smn && no > mn)
            {
                smn = no;
            }
            mins = {mn, smn};
        };

        vector<pair<int, int>> dis(n + 1, {INF, INF});
        function<void()> BFS = [&]()
        {
            dis[1] = {0, INF};
            queue<pair<int, int>> q;
            q.push({1, 0});

            while (!q.empty())
            {
                auto node = q.front();
                q.pop();
                for (auto i : adj[node.first])
                {
                    if (node.second + 1 < dis[i].second)
                    {
                        updateMinimums(node.second + 1, dis[i]);
                        q.push({i, node.second + 1});
                    }
                }
            }
        };

        function<int(int)> getTime = [&](int edgeCnt)
        {
            int curTime = 0;
            int cnt = 0;
            while (cnt < edgeCnt)
            {
                int currentNodeStatus =
                    (curTime / change) % 2; // 0 is green, 1 is red
                if (currentNodeStatus == 0)
                {
                    curTime += time;
                    cnt++;
                }
                else
                {
                    int waitingTime =
                        change * ((curTime + change) / change) - curTime;
                    curTime += time + waitingTime;
                    cnt++;
                }
            }
            return curTime;
        };

        BFS();
        int smn = dis[n].second;
        if (smn == INF)
        {
            smn = dis[n].first + 2;
        }
        return getTime(smn);
    }
};