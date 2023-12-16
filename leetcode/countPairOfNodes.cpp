/*You are given an undirected graph defined by an integer n, the number of nodes, and a 2D integer array edges, the edges in the graph, where edges[i] = [ui, vi] indicates that there is an undirected edge between ui and vi. You are also given an integer array queries.

Let incident(a, b) be defined as the number of edges that are connected to either node a or b.

The answer to the jth query is the number of pairs of nodes (a, b) that satisfy both of the following conditions:

a < b
incident(a, b) > queries[j]
Return an array answers such that answers.length == queries.length and answers[j] is the answer of the jth query.

Note that there can be multiple edges between the same two nodes.
https://leetcode.com/problems/count-pairs-of-nodes/description/
*/


#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> countPairs(int n, vector<vector<int>> &edges, vector<int> &queries)
    {

        map<pair<int, int>, int> edgeCnt;
        vector<int> degree(n + 1, 0);
        vector<vector<int>> disEdges;
        map<pair<int, int>, int> done;

        for (auto i : edges)
        {
            edgeCnt[{i[0], i[1]}]++;
            edgeCnt[{i[1], i[0]}]++;
        }

        for (auto i : edgeCnt)
        {
            degree[i.first.first] += i.second;
            if (!done[i.first])
            {
                disEdges.push_back({i.first.first, i.first.second, i.second});
                done[i.first]++;
                done[{i.first.second, i.first.first}]++;
            }
        }

        vector<int> sizes;
        for (int node = 1; node <= n; node++)
        {
            sizes.push_back(degree[node]);
        }
        sort(sizes.begin(), sizes.end());

        vector<int> ansQ(queries.size());
        for (int q = 0; q < queries.size(); q++)
        {
            int L = queries[q];
            int ans = 0;

            for (int i = 0; i < n; i++)
            {
                auto it = upper_bound(sizes.begin() + i + 1, sizes.end(), L - sizes[i]);
                ans += sizes.end() - it;
            }

            for (auto i : disEdges)
            {
                if (degree[i[0]] + degree[i[1]] > L && degree[i[0]] + degree[i[1]] - i[2] <= L)
                {
                    ans--;
                }
            }
            ansQ[q] = ans;
        }
        return ansQ;
    }
};