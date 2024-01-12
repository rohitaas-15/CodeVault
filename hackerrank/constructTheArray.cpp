/*Your goal is to find the number of ways to construct an array such that consecutive positions contain different values.

Specifically, we want to construct an array with  elements such that each element between  and , inclusive. We also want the first and last elements of the array to be  and .

Given ,  and , find the number of ways to construct such an array. Since the answer may be large, only find it modulo .

For example, for , , , there are  ways, as shown here:

image

Complete the function countArray which takes input ,  and . Return the number of ways to construct the array such that consecutive elements are distinct.

https://www.hackerrank.com/challenges/construct-the-array/problem*/

#include <bits/stdc++.h>
using namespace std;
const long long M = 1e9 + 7;
long countArray(int n, int k, int x)
{
    long long dpAll[n + 1], dpX[n + 1]; //number of ways of constructing the array with any last element, and last element X(respectively)
    memset(dpAll, 0ll, sizeof(dpAll));
    memset(dpX, 0ll, sizeof(dpX));
    dpAll[2] = k - 1, dpX[2] = (x != 1);
    for (int i = 3; i <= n; i++)
    {
        dpAll[i] = ((long long)dpAll[i - 1] * (long long)(k - 1)) % M;
        dpX[i] = ((long long)dpAll[i - 1] - (long long)dpX[i - 1] + M) % M;
    }
    return dpX[n];
}
