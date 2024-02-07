/*Given two strings s and t of lengths m and n respectively, return the minimum window
substring
 of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

*/
#include <bits/stdc++.h>
using namespace std;
bool contains(vector<int> &windowFreq, vector<int> &tfreq)
{
    for (int i = 0; i < 52; i++)
    {
        if (windowFreq[i] < tfreq[i])
        {
            return false;
        }
    }
    return true;
}

class Solution
{
public:
    string minWindow(string s, string t)
    {

        vector<int> tfreq(52, 0);
        for (auto i : t)
        {
            if (i >= 'A' && i <= 'Z')
            {
                tfreq[26 + i - 'A']++;
            }
            else
                tfreq[i - 'a']++;
        }

        vector<int> windowFreq(52, 0), latest(52, -1);

        int i = 0, j = 0;
        int n = s.size();

        int mn = 1e9, start = -1, end = -1;
        while (i < n && j < n)
        {
            while (j < n && !contains(windowFreq, tfreq))
            {
                if (s[j] >= 'A' && s[j] <= 'Z')
                {
                    windowFreq[26 + s[j] - 'A']++;
                }
                else
                    windowFreq[s[j] - 'a']++;
                j++;
            }

            while (i < j && contains(windowFreq, tfreq))
            {
                if (mn > j - i + 1)
                {
                    mn = j - i + 1;
                    start = i, end = j - 1;
                }

                if (s[i] >= 'A' && s[i] <= 'Z')
                {
                    windowFreq[26 + s[i] - 'A']--;
                }
                else
                    windowFreq[s[i] - 'a']--;
                i++;
            }
        }

        if (start == -1)
        {
            return "";
        }
        return s.substr(start, end - start + 1);
    }
};