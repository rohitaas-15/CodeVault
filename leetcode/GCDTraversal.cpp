/*You are given a 0-indexed integer array nums, and you are allowed to traverse between its indices. You can traverse between index i and index j, i != j, if and only if gcd(nums[i], nums[j]) > 1, where gcd is the greatest common divisor.

Your task is to determine if for every pair of indices i and j in nums, where i < j, there exists a sequence of traversals that can take us from i to j.

Return true if it is possible to traverse between all such pairs of indices, or false otherwise.
https://leetcode.com/problems/greatest-common-divisor-traversal/description/*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 2;
int spf[N + 1];
int cnt = 0;

void seive()
{
    for (int i = 2; i < N; i++)
    {
        spf[i] = i;
    }

    for (int i = 2; i < N; i++)
    {
        if (spf[i] == i)
        {
            for (int j = 2 * i; j < N; j += i)
            {
                if (spf[j] == j)
                {
                    spf[j] = i;
                }
            }
        }
    }
}

struct DSU
{

    vector<int> parent, rank;

    DSU(int n)
    {
        parent.resize(n + 1, -1), rank.resize(n + 1, 1);
    }

    int getParent(int x)
    {
        if (parent[x] == -1)
            return x;
        return parent[x] = getParent(parent[x]);
    }

    void unite(int x, int y)
    {
        int s1 = getParent(x);
        int s2 = getParent(y);
        if (s1 == s2)
            return;

        if (rank[s1] < rank[s2])
        {
            swap(s1, s2);
        }

        rank[s1] += rank[s2], parent[s2] = s1;
    }
};

class Solution
{
public:
    bool canTraverseAllPairs(vector<int> &nums)
    {

        if (nums.size() == 1)
            return true;

        int n = nums.size();
        if (!cnt) //to only calculate seive 1 time for multiple test cases
        {
            seive(); //calculating smallest prime factors for each number
            cnt++;
        }

        DSU d(N);
        bool present[N + 1];
        memset(present, 0, sizeof(present));

        for (int i = 0; i < n; i++)
        {
            if (nums[i] == 1)
                return false;

            int temp = nums[i];
            vector<int> pf;
            while (temp != 1)
            {
                present[spf[temp]] = true;
                pf.push_back(spf[temp]);
                temp /= spf[temp];
            }

            for (int j = 1; j < pf.size(); j++)
            {
                d.unite(pf[j], pf[j - 1]); //connecting various prime factors as, the current element can be used as an intermediate
                                            //node in the path for previous elements
            }
        }

        int total = 0, check; //one prime factor to check for size
        for (int i = 1; i < N; i++)
        {
            if (present[i])
                check = i, total++;
        }

        return d.rank[d.getParent(check)] == total; //check if all prime factors present are in a single component
    }
};