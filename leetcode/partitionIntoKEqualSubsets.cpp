/*Given an integer array nums and an integer k, return true if it is possible to divide this array into k non-empty subsets whose sums are all equal.

 

Example 1:

Input: nums = [4,3,2,3,5,2,1], k = 4
Output: true
Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
Example 2:

Input: nums = [1,2,3,4], k = 3
Output: false
 

Constraints:

1 <= k <= nums.length <= 16
1 <= nums[i] <= 104
The frequency of each element is in the range [1, 4].
https://leetcode.com/problems/partition-to-k-equal-sum-subsets/*/
#include <bits/stdc++.h>
using namespace std;
int targetCnt, targetSum, totalSum;
vector<int> nums;
bool makeSubsets(int i, int subCnt, int csum, int vis)
{
    if (csum > targetSum)
    {
        return false;
    }
    if (subCnt == targetCnt)
    {
        return vis == ((1 << (nums.size())) - 1);
    }
    if (i == nums.size())
    {
        return (csum == targetSum && makeSubsets(0, subCnt + 1, 0, vis));
    }
    if (vis & (1 << i))
    {
        return makeSubsets(i + 1, subCnt, csum, vis);
    }
    return makeSubsets(i + 1, subCnt, csum + nums[i], vis | (1 << i)) || makeSubsets(i + 1, subCnt, csum, vis);
}

bool makeSum(int i, int csum, int vis)
{
    if (i == nums.size())
    {
        return (targetSum = csum) && (targetSum * targetCnt == totalSum && makeSubsets(0, 1, 0, vis));
    }
    return makeSum(i + 1, csum + nums[i], vis | (1 << i)) || makeSum(i + 1, csum, vis);
}

class Solution
{
public:
    bool canPartitionKSubsets(vector<int> &Nums, int k)
    {
        nums = Nums, totalSum = accumulate(nums.begin(), nums.end(), 0), targetCnt = k;
        int vis = 0;//visited array as a mask
        return makeSum(0, 0, vis);
    }
};