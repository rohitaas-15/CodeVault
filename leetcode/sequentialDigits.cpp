/*An integer has sequential digits if and only if each digit in the number is one more than the previous digit.

Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.*/
//https://leetcode.com/problems/sequential-digits/description/?envType=daily-question&envId=2024-02-02
#include <bits/stdc++.h>
using namespace std;
set<int> seq;
string s;
void make(int index, int last, int zero, int prev, string &ans)
{
    if (index == s.size())
    {
        seq.insert(stoi(ans, nullptr, 10));
        return;
    }

    int limit = (last) ? s[index] - '0' : 9;

    if (zero)
    {
        for (int i = 0; i <= limit; i++)
        {
            ans += '0' + i;
            make(index + 1, last && i == limit, zero && i == 0, i, ans);
            ans.pop_back();
        }
    }

    if (prev + 1 <= limit)
    {
        ans += '0' + prev + 1;
        make(index + 1, last && prev + 1 == limit, zero && prev + 1 == 0, prev + 1, ans);
        ans.pop_back();
    }
}

class Solution
{
public:
    vector<int> sequentialDigits(int low, int high)
    {
        s = to_string(high);
        string ans;

        seq.clear();
        make(0, 1, 1, -1, ans);
        auto hset = seq;

        seq.clear();
        s = to_string(low - 1);
        ans = "";
        make(0, 1, 1, -1, ans);
        auto lset = seq;

        for (auto i : lset)
        {
            hset.erase(i);
        }
        vector<int> finalAns;

        for (auto i : hset)
        {
            finalAns.push_back(i);
        }

        return finalAns;
    }
};