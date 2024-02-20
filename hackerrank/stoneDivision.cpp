/*Consider the following game:

There are two players, First and Second, sitting in front of a pile of  stones. First always plays first.
There is a set, , of  distinct integers defined as .
The players move in alternating turns. During each turn, a player chooses some  and splits one of the piles into exactly  smaller piles of equal size. If no  exists that will split one of the available piles into exactly  equal smaller piles, the player loses.
Both players always play optimally.
Given , , and the contents of , find and print the winner of the game. If First wins, print First; otherwise, print Second.

Input Format

The first line contains two space-separated integers describing the respective values of  (the size of the initial pile) and  (the size of the set).
The second line contains  distinct space-separated integers describing the respective values of .

Constraints

Output Format

Print First if the First player wins the game; otherwise, print Second.

https://www.hackerrank.com/challenges/stone-division/problem*/
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'stoneDivision' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. LONG_INTEGER n
 *  2. LONG_INTEGER_ARRAY s
 */

map<long, bool> dp;
bool play(long lastPile, vector<long> &s)
{

    if (dp.count(lastPile))
    {
        return dp[lastPile];
    }

    bool ans = 0;
    for (auto i : s)
    {
        if (lastPile % i == 0)
        {
            if (i % 2 == 0)
            {
                return dp[lastPile] = 1;
            }
            else
            {
                ans = ans | !(play(lastPile / i, s));
            }
        }
    }
    return dp[lastPile] = ans;
}

string stoneDivision(long n, vector<long> s) // if at any given point, the number of piles are even, the second player wins(can copy the operation peformed by first one)
                                             // so only the last pile matters(if the number of piles are odd)
{

    dp.clear();
    if (play(n, s))
    {
        return "First";
    }
    else
        return "Second";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    long n = stol(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    string s_temp_temp;
    getline(cin, s_temp_temp);

    vector<string> s_temp = split(rtrim(s_temp_temp));

    vector<long> s(m);

    for (int i = 0; i < m; i++)
    {
        long s_item = stol(s_temp[i]);

        s[i] = s_item;
    }

    string result = stoneDivision(n, s);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str)
{
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

    return s;
}

string rtrim(const string &str)
{
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end());

    return s;
}

vector<string> split(const string &str)
{
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos)
    {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
