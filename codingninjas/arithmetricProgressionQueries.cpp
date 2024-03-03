/*Problem statement
Given an integer array(ARR) of size N, the following operations need to be performed:

update(l, r, val) : Add (val + i) to arr[l + i] where, 0 <= i <= r - l.

rangeSum(l, r): return the sum of all elements in the array from index l to r, i.e., the sum of array arr[l...r].
Two type of queries denote these operations:

Type 1: for update(l, r, val) operation.
Type 2: for rangeSum(l, r) operation.

Note: (1 based indexing) for the queries.
Constraints:
1 <= N <= 10^5
1 <= Q <= 10^5
1 <= l <= r <= N
0 <= val <= 10^6
0 <= arr[i] <= 10^6

where 'N' is the size of the array, 'Q' is the number of queries, and arr[i] denotes the ith element of the array.

Time Limit: 1 sec.
https://www.codingninjas.com/studio/problem-of-the-day/ninja?leftPanelTabValue=PROBLEM
Name: Arithmetic Progression Queries*/


#include <bits/stdc++.h>
using namespace std;
long sqSum(long n)
{
    if (n < 1)
        return 0;
    return (n * (n + 1)) / 2ll;
}
struct SegmentTree
{
    vector<long> tree, lazy;
    vector<vector<long>> changes;
    void _build(int s, int e, int ti, vector<int> &arr)
    {
        if (s > e)
            return;
        if (s == e)
        {
            tree[ti] = (long)arr[s - 1];
            return;
        }
        int mid = (s + e) >> 1;
        _build(s, mid, ti * 2, arr);
        _build(mid + 1, e, ti * 2 + 1, arr);
        tree[ti] = tree[ti * 2] + tree[ti * 2 + 1];
    }

    void build(int n, vector<int> &arr)
    {
        tree.clear(), lazy.clear(), changes.clear();
        tree.resize(4 * n + 1, 0);
        lazy.resize(4 * n + 1, -1);
        changes.resize(4 * n + 1);
        _build(1, n, 1, arr);
    }

    void resolve(int s, int e, int ti, int val)
    {
        tree[ti] += ((e - s) + 1ll) * (long)val;
    }

    void resolveChanges(int s, int e, int ti)
    {
        while (changes[ti].size())
        {
            int index = changes[ti].size() - 1;
            int num = changes[ti][index];

            int first = num, last = num + (e - s);
            tree[ti] += sqSum(last) - sqSum(first - 1);
            changes[ti].pop_back();
        }
    }

    void update(int s, int e, int qs, int qe, int ti, long val)
    {
        // cout<<s<<" "<<e<<endl;
        if (lazy[ti] != -1)
        {
            resolve(s, e, ti, lazy[ti]);
            if (s != e)
            {
                lazy[2 * ti] = max(0l, lazy[2 * ti]);
                lazy[2 * ti + 1] = max(0l, lazy[2 * ti + 1]);
                lazy[2 * ti] += lazy[ti];
                lazy[2 * ti + 1] += lazy[ti];

                int mid = (s + e) >> 1;

                for (auto i : changes[ti])
                {
                    changes[ti * 2].push_back(i);
                    changes[ti * 2 + 1].push_back(i + (mid - s + 1));
                }
            }

            resolveChanges(s, e, ti);
            lazy[ti] = -1;
        }

        if (qs > e || qe < s)
        {
            return;
        }

        if (qs <= s && qe >= e)
        {
            resolve(s, e, ti, val);
            changes[ti].push_back(s - qs);
            if (s != e)
            {
                lazy[2 * ti] = max(0l, lazy[2 * ti]);
                lazy[2 * ti + 1] = max(0l, lazy[2 * ti + 1]);
                lazy[2 * ti] += val;
                lazy[2 * ti + 1] += val;

                int mid = (s + e) >> 1;

                for (auto i : changes[ti])
                {
                    changes[ti * 2].push_back(i);
                    changes[ti * 2 + 1].push_back(i + (mid - s + 1));
                }
            }
            resolveChanges(s, e, ti);
            lazy[ti] = -1;
            return;
        }

        int mid = (s + e) >> 1;

        update(s, mid, qs, qe, ti * 2, val);
        update(mid + 1, e, qs, qe, ti * 2 + 1, val);
        tree[ti] = tree[ti * 2] + tree[ti * 2 + 1];
    }

    long query(int s, int e, int qs, int qe, int ti)
    {
        if (lazy[ti] != -1)
        {
            resolve(s, e, ti, lazy[ti]);
            if (s != e)
            {
                lazy[2 * ti] = max(0l, lazy[2 * ti]);
                lazy[2 * ti + 1] = max(0l, lazy[2 * ti + 1]);
                lazy[2 * ti] += lazy[ti];
                lazy[2 * ti + 1] += lazy[ti];

                int mid = (s + e) >> 1;

                for (auto i : changes[ti])
                {
                    changes[ti * 2].push_back(i);
                    changes[ti * 2 + 1].push_back(i + (mid - s + 1));
                }
            }

            resolveChanges(s, e, ti);
            lazy[ti] = -1;
        }

        if (qs > e || qe < s)
        {
            return 0l;
        }

        if (qs <= s && qe >= e)
        {
            return tree[ti];
        }

        int mid = (s + e) >> 1;
        return query(s, mid, qs, qe, ti * 2) +
               query(mid + 1, e, qs, qe, ti * 2 + 1);
    }
};

#include <bits/stdc++.h>
class NumArray
{
public:
    // Initialize here.
    int N;
    SegmentTree t;
    NumArray(vector<int> &arr, int n)
    {
        t.build(n, arr);
        N = n;
    }

    // Update operation.
    void update(int l, int r, int val) { t.update(1, N, l, r, 1, val); }

    // Return the sum of subarray arr[l..r].
    long long rangeSum(int l, int r) { return t.query(1, N, l, r, 1); }
};