
/*You are given a non-decreasing array and an integer K. You need to remove exactly K integers from the given array such that the maximum difference between adjacent elements is minimum.

For example:
If the given array is: [2 6 7 7 10] and K = 2. We need to remove A[0] = 2 and A[4] = 10, then the resultant array would become [6 7 7], where the difference between adjacent pairs are {1, 0}. Thus our answer would be 1. You can see that there would not be any better answer than 1 for this array
https://www.codingninjas.com/studio/problem-of-the-day/easy?leftPanelTabValue=PROBLEM*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int getMax(multiset<int> &ms)
{
    auto i = ms.end();
    i--;
    return *(i);
}
int maxAdjDifference(vector<int> &arr, int k)
{
    int n = arr.size();

    int len = n - k; //constant length after removal of elements, elements are preferred to remove either from the back or from the front , 
                    //as removing them in middle, will increase my answer

    multiset<int> ms;
    for (int i = 1; i < len; i++)
    {
        ms.insert(arr[i] - arr[i - 1]);
    }

    int mx = INF;
    mx = min(mx, getMax(ms));

    for (int i = len; i < n; i++)
    {
        ms.erase(ms.lower_bound(arr[i - len + 1] - arr[i - len]));
        ms.insert(arr[i] - arr[i - 1]);
        mx = min(mx, getMax(ms)); //taking min of maxAdjacent diff in every subarray of size (n-k)
    }
    return mx;
}
