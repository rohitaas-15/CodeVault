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