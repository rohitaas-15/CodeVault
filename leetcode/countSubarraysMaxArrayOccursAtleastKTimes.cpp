/*You are given an integer array nums and a positive integer k.

Return the number of subarrays where the maximum element of nums appears at least k times in that subarray.

A subarray is a contiguous sequence of elements within an array.

 */
/*https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/?envType=daily-question&envId=2024-03-29*/
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    long long countSubarrays(vector<int> &nums, int k)
    {
        int mx = 0, n = nums.size();
        for (auto i : nums)
            mx = max(mx, i);

        vector<int> in;
        in.push_back(-1);
        for (int i = 0; i < n; i++)
        {
            if (nums[i] == mx)
                in.push_back(i);
        }

        long long ans = 0;
        for (int i = 1; i < in.size(); i++)
        {
            int left = in[i] - in[i - 1];
            int rightIndex = k + i - 1;
            if (rightIndex >= in.size())
            {
                break;
            }
            int right = n - in[rightIndex];
            ans = ans + ((long long)left * (long long)(right));
        }

        return ans;
    }
};