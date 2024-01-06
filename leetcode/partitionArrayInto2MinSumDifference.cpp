#include <bits/stdc++.h>
using namespace std;
vector<int> nums;
vector<vector<int>> leftSums, rightSums;
int n;
void make(int i, int cnt, int limit, int sum)
{
    if (i == limit)
    {
        if (limit == n)
        {
            leftSums[cnt].push_back(sum);
        }
        else
            rightSums[cnt].push_back(sum);
        return;
    }
    make(i + 1, cnt + 1, limit, sum + nums[i]);
    make(i + 1, cnt, limit, sum);
}

class Solution
{
public:
    int minimumDifference(vector<int> &Nums)
    {
        leftSums.clear(), leftSums.resize(1 << 16);   // sums from all subsets from left side of array
        rightSums.clear(), rightSums.resize(1 << 16); // sums from all subsets from right side of array
        nums = Nums;
        n = nums.size() / 2;
        int total = accumulate(nums.begin(), nums.end(), 0);

        make(0, 0, n, 0), make(n, 0, 2 * n, 0);
        for (auto &i : rightSums)
        {
            sort(i.begin(), i.end());
        }

        int target = total / 2; // optimal answer
        int ans = 2e7;
        for (int i = 0; i <= n; i++)
        {
            int rightSubsetSize = n - i;
            for (auto j : leftSums[i]) // making a subset of size n with i elements from left array and 'rightSubsetSize' elements
                                       //  from right array and sum as close as possible to optimal answer
            {
                int targetFromRight = target - j;
                auto it = lower_bound(rightSums[rightSubsetSize].begin(), rightSums[rightSubsetSize].end(), targetFromRight);
                if (it == rightSums[rightSubsetSize].begin())
                {
                    int curSum = j + (*it);
                    ans = min(ans, abs(curSum - (total - curSum)));
                }
                else if (it == rightSums[rightSubsetSize].end())
                {
                    it--;
                    int curSum = j + (*it);
                    ans = min(ans, abs(curSum - (total - curSum)));
                }
                else
                {
                    auto itPrev = it;
                    itPrev--;
                    int curSum = j + (*it);
                    ans = min(ans, abs(curSum - (total - curSum)));
                    curSum = j + (*itPrev);
                    ans = min(ans, abs(curSum - (total - curSum)));
                }
            }
        }
        return ans;
    }
};