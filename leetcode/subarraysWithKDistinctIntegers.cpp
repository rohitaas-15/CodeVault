#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

const int N = 1e5 + 2;

class Solution
{
public:
    int subarraysWithKDistinct(vector<int> &nums, int k)
    {
        ordered_set s;
        int latestIndex[N];
        memset(latestIndex, -1, sizeof(latestIndex));
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            int prevIndex = latestIndex[nums[i]];
            auto it = s.find(prevIndex);

            if (it != s.end())
                s.erase(it);

            latestIndex[nums[i]] = i;
            s.insert(i);

            //Use policy based data structure to subtract subarrays that contain at least k distinct integers from those that contain at least k+1 distinct integers
            int indexFromStart = s.size() - k;
            if (indexFromStart < 0)
            {
                continue;
            }
            it = s.find_by_order(indexFromStart);
            int right = *it;

            int secondIndexFromStart = s.size() - (k + 1);
            if (secondIndexFromStart < 0)
            {
                ans += right + 1;
            }
            else
            {
                auto it2 = s.find_by_order(secondIndexFromStart);
                int left = *it2;
                ans += right - left;
            }
        }
        return ans;
    }
};