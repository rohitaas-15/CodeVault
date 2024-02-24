/*You are given an integer n indicating there are n people numbered from 0 to n - 1. You are also given a 0-indexed 2D integer array meetings where meetings[i] = [xi, yi, timei] indicates that person xi and person yi have a meeting at timei. A person may attend multiple meetings at the same time. Finally, you are given an integer firstPerson.

Person 0 has a secret and initially shares the secret with a person firstPerson at time 0. This secret is then shared every time a meeting takes place with a person that has the secret. More formally, for every meeting, if a person xi has the secret at timei, then they will share the secret with person yi, and vice versa.

The secrets are shared instantaneously. That is, a person may receive the secret and share it with people in other meetings within the same time frame.

Return a list of all the people that have the secret after all the meetings have taken place. You may return the answer in any order.
https://leetcode.com/problems/find-all-people-with-secret/description/?envType=daily-question&envId=2024-02-24*/
#include <bits/stdc++.h>
using namespace std;
struct DSU
{
    vector<int> parent, rank;

    DSU(int n)
    {
        parent.resize(n + 1, -1);
        rank.resize(n + 1, 1);
    }

    int getParent(int x)
    {
        if (parent[x] == -1)
            return x;
        return parent[x] = getParent(parent[x]);
    }

    void unite(int x, int y)
    {
        int p1 = getParent(x);
        int p2 = getParent(y);

        if (p1 == p2)
            return;

        if (rank[p2] > rank[p1])
        {
            swap(p1, p2);
        }

        parent[p2] = p1, rank[p1] += rank[p2];
    }
};

class Solution
{
public:
    vector<int> findAllPeople(int n, vector<vector<int>> &meetings, int firstPerson)
    {
        map<int, vector<pair<int, int>>> m;
        for (auto &i : meetings)
        {
            m[i[2]].push_back({i[0], i[1]});
        }

        DSU d(n);

        d.unite(0, firstPerson);

        for (auto i : m)
        {
            for (auto j : i.second)
            {
                d.unite(j.first, j.second);
            }

            for (auto j : i.second) // if noone could know the secret at this particular time point
            {
                if (d.getParent(j.first) != d.getParent(0))
                {
                    d.parent[j.first] = -1, d.rank[j.first] = 1;
                }

                if (d.getParent(j.second) != d.getParent(0))
                {
                    d.parent[j.second] = -1, d.rank[j.second] = 1;
                }
            }
        }

        vector<int> keepers;
        for (int i = 0; i < n; i++)
        {
            if (d.getParent(0) == d.getParent(i))
            {
                keepers.push_back(i);
            }
        }
        return keepers;
    }
};