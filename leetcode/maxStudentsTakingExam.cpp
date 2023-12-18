/*Given a m * n matrix seats  that represent seats distributions in a classroom. If a seat is broken, it is denoted by '#' character otherwise it is denoted by a '.' character.

Students can see the answers of those sitting next to the left, right, upper left and upper right, but he cannot see the answers of the student sitting directly in front or behind him. Return the maximum number of students that can take the exam together without any cheating being possible.

Students must be placed in seats in good condition.
https://leetcode.com/problems/maximum-students-taking-exam/description/*/


#include <bits/stdc++.h>
using namespace std;

int n, m;
struct edge
{
    int from, to, res;
};

struct Dinic
{
    vector<vector<int>> adj;
    vector<int> level, vis;
    vector<edge> edges;
    int n, src, sink, ec = 0;

    Dinic(int n, int src, int sink)
    {
        this->n = n, this->src = src, this->sink = sink;
        adj.resize(n + 1);
    }

    void addEdge(int x, int y, int w)
    {
        edges.push_back({x, y, w});
        adj[x].push_back(ec++);
        edges.push_back({y, x, 0});
        adj[y].push_back(ec++);
    }

    bool levelGraph()
    {
        level.clear(), level.resize(n + 1, -1);
        queue<int> q;
        level[src] = 0, q.push(src);

        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            for (auto i : adj[node])
            {
                int to = edges[i].to, res = edges[i].res;

                if (res && level[to] == -1)
                {
                    level[to] = level[node] + 1;
                    q.push(to);
                }
            }
        }
        return level[sink] != -1;
    }

    int augmentPath(int node, int mn)
    {
        if (node == sink)
            return mn;

        vis[node] = 1;
        int flow = 0;
        for (auto i : adj[node])
        {
            int to = edges[i].to, res = edges[i].res;
            if (res && mn && !vis[to] && level[to] == level[node] + 1)
            {
                int newMn = min(mn, res);
                int pathFlow = augmentPath(to, newMn);
                flow += pathFlow, edges[i].res -= pathFlow, edges[i ^ 1].res += pathFlow, mn -= pathFlow;
            }
        }
        return flow;
    }

    int max_flow()
    {
        int flow = 0;

        while (levelGraph())
        {
            vis.clear(), vis.resize(n + 1, 0);
            flow += augmentPath(src, 1e9);
        }
        return flow;
    }
};

int getVal(int x, int y)
{
    return x * m + y;
}

bool isCheating(int x, int y, int i, int j)
{
    if (x == i && y == j)
        return false;

    for (int ii = -1; ii <= 1; ii++)
    {
        for (int jj = -1; jj <= 1; jj++)
        {
            if (jj != 0)
            {
                int nx = x + ii, ny = y + jj;

                if (nx >= 0 && nx < n && ny >= 0 && ny < m && (nx == i && ny == j))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

class Solution
{
public:
    int maxStudents(vector<vector<char>> &seats)
    {
        n = seats.size(), m = seats[0].size();

        int N = n * m + 5, src = n * m + 3, sink = n * m + 4;
        Dinic g(N, src, sink);
        int cnt = 0;

        map<int, int> seen;

// for bipartite graph, maximum matching= min vertex cover, and complement of min vertex cover is maximum independent set

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (seats[i][j] == '.')
                {
                    cnt++;
                    for (int k = 0; k < n; k++)
                    {
                        for (int l = 0; l < m; l++)
                        {
                            if (seats[k][l] == '.' && isCheating(i, j, k, l))
                            {
                                int fVal = getVal(i, j), sVal = getVal(k, l);

                                if (j % 2 == 1) //maintain edges from group 1(even number column) to group 2(odd number column)
                                                //as the graph is bipartite
                                {
                                    swap(sVal, fVal);
                                }

                                g.addEdge(fVal, sVal, 1);

                                if (!seen[fVal])
                                {
                                    g.addEdge(src, fVal, 1), seen[fVal]++;
                                }

                                if (!seen[sVal])
                                {
                                    g.addEdge(sVal, sink, 1), seen[sVal]++;
                                }
                            }
                        }
                    }
                }
            }
        }

        return cnt - g.max_flow(); 
    }
};