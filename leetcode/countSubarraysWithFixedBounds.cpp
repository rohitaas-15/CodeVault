/*You are given an integer array nums and two integers minK and maxK.

A fixed-bound subarray of nums is a subarray that satisfies the following conditions:

The minimum value in the subarray is equal to minK.
The maximum value in the subarray is equal to maxK.
Return the number of fixed-bound subarrays.

A subarray is a contiguous part of an array.*/

//https://leetcode.com/problems/count-subarrays-with-fixed-bounds/?envType=daily-question&envId=2024-03-31
#include <bits/stdc++.h>
using namespace std;

bool isContagious(multiset<int> &s, int &mink, int &maxk)
{
    if (!s.size())
    {
        return false;
    }

    auto it1 = s.begin();
    auto it2 = s.end();
    it2--;

    auto num1 = *it1;
    auto num2 = *it2;
    return (num1 <= mink && num2 >= maxk);
}

long long slidingWindow(vector<int> &nums, int mink, int maxk) // number of subarrays where min element is <=mink and max element is >=maxk
{
    int i = 0, j = 0, n = nums.size();
    long long ans = 0;
    multiset<int> s;
    while (i < n && j < n)
    {
        while (j < n && !isContagious(s, mink, maxk))
        {
            s.insert(nums[j]);
            j++;
        }

        while (i < j && isContagious(s, mink, maxk))
        {
            ans = ans + (long long)(n - j + 1);
            s.erase(s.lower_bound(nums[i]));
            i++;
        }
    }
    return ans;
}

class Solution
{
public:
    long long countSubarrays(vector<int> &nums, int minK, int maxK)
    {

        return slidingWindow(nums, minK, maxK) - slidingWindow(nums, minK - 1, maxK) - slidingWindow(nums, minK, maxK + 1) + slidingWindow(nums, minK - 1, maxK + 1);
    }
};