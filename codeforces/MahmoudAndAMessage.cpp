/*Mahmoud wrote a message s of length n. He wants to send it as a birthday present to his friend Moaz who likes strings. He wrote it on a magical paper but he was surprised because some characters disappeared while writing the string. That's because this magical paper doesn't allow character number i in the English alphabet to be written on it in a string of length more than ai. For example, if a1 = 2 he can't write character 'a' on this paper in a string of length 3 or more. String "aa" is allowed while string "aaa" is not.

Mahmoud decided to split the message into some non-empty substrings so that he can write every substring on an independent magical paper and fulfill the condition. The sum of their lengths should be n and they shouldn't overlap. For example, if a1 = 2 and he wants to send string "aaa", he can split it into "a" and "aa" and use 2 magical papers, or into "a", "a" and "a" and use 3 magical papers. He can't split it into "aa" and "aa" because the sum of their lengths is greater than n. He can split the message into single string if it fulfills the conditions.

A substring of string s is a string that consists of some consecutive characters from string s, strings "ab", "abc" and "b" are substrings of string "abc", while strings "acb" and "ac" are not. Any string is a substring of itself.

While Mahmoud was thinking of how to split the message, Ehab told him that there are many ways to split it. After that Mahmoud asked you three questions:

How many ways are there to split the string into substrings such that every substring fulfills the condition of the magical paper, the sum of their lengths is n and they don't overlap? Compute the answer modulo 109 + 7.
What is the maximum length of a substring that can appear in some valid splitting?
What is the minimum number of substrings the message can be spit in?
Two ways are considered different, if the sets of split positions differ. For example, splitting "aa|a" and "a|aa" are considered different splittings of message "aaa".

Input
The first line contains an integer n (1 ≤ n ≤ 103) denoting the length of the message.

The second line contains the message s of length n that consists of lowercase English letters.

The third line contains 26 integers a1, a2, ..., a26 (1 ≤ ax ≤ 103) — the maximum lengths of substring each letter can appear in.

Output
Print three lines.

In the first line print the number of ways to split the message into substrings and fulfill the conditions mentioned in the problem modulo 109  +  7.

In the second line print the length of the longest substring over all the ways.

In the third line print the minimum number of substrings over all the ways.
https://codeforces.com/problemset/problem/766/C*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
long long int _debug = 0, _nested = 0, _t = 1, INF = 1e18 + 2;
// macros-------------------------------------------------------------------------------
#define ll long long
#define int ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
#define endl "\n"
#define nl        \
    cout << endl; \
    if (_debug)   \
        cerr << endl;

// print
// helper-------------------------------------------------------------------------------
template <typename Primitive>
void print(Primitive &&P)
{
    cout << P << " ";
    if (_debug)
        cerr << P << " ";
    if (!_nested)
    {
        nl;
    }
}
template <typename Complex>
void print(vector<Complex> &Vector)
{
    _nested = 1;
    for (Complex &C : Vector)
        print(C);
    nl;
    _nested = 0;
}
template <typename Complex, typename... ComplexObjects>
void print(Complex &&C, ComplexObjects &&...list)
{
    _nested = 1, print(C);
    _nested = 0, print(list...);
}

// scan
// helper-------------------------------------------------------------------------------
template <typename Primitive>
void scan(Primitive &P)
{
    cin >> P;
}
template <typename Complex>
void scan(vector<Complex> &Vector)
{
    for (Complex &C : Vector)
        scan(C);
}
template <typename Complex, typename... ComplexObjects>
void scan(Complex &C, ComplexObjects &...list)
{
    scan(C), scan(list...);
}

// fill bulk
// data--------------------------------------------------------------------------------
template <typename Primitive>
void fill(Primitive Value, Primitive &P)
{
    P = Value;
}
template <typename Primitive, typename Complex>
void fill(Primitive Value, vector<Complex> &Vector)
{
    for (Complex &C : Vector)
        fill(Value, C);
}
template <typename Primitive, typename Complex, typename... ComplexObjects>
void fill(Primitive Value, Complex &C, ComplexObjects &...list)
{
    fill(Value, C), fill(Value, list...);
}

// policy based data
// structures---------------------------------------------------------------------------
template <typename T>
using indexed_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T1, typename T2>
using indexed_map =
    tree<T1, T2, less<T1>, rb_tree_tag, tree_order_statistics_node_update>;

// code----------------------------------------------------------------------------------
const int M = 1e9 + 7;
void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> limit(26);
    for (int i = 0; i < 26; i++)
    {
        cin >> limit[i];
    }

    int total_ways[n + 1], max_length[n + 1], min_count[n + 1];
    memset(total_ways, 0, sizeof(total_ways));
    memset(max_length, 0, sizeof(max_length));
    memset(min_count, 0, sizeof(min_count));

    total_ways[0] = 1, max_length[0] = 0, min_count[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        int mn = INF;
        min_count[i] = INF;
        for (int j = i; j >= 1; j--)
        {
            if (i - j + 1 <= min(mn, limit[s[j - 1] - 'a']))
            {
                total_ways[i] = (total_ways[i] + total_ways[j - 1]) % M;
                max_length[i] = max({max_length[i], i - j + 1, max_length[j - 1]});
                min_count[i] = min(min_count[i], 1 + min_count[j - 1]);
                mn = min(mn, limit[s[j - 1] - 'a']);
            }
            else
                break;
        }
    }

    print(total_ways[n]);
    print(max_length[n]);
    print(min_count[n]);
}

signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    // cin >> _t;
    for (int tc = 1; tc <= _t; tc++)
    {
        // cout << "Case " << tc << ":"
        //      << " ";
        solve();
    }
}

// cin does not move the input cursor to the next line, use cin.ignore() to
// move it to the next line use an array instead of an int whenever possible,
// for coding competitions