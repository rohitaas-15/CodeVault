/*Robbers, who attacked the Gerda's cab, are very successful in covering from the kingdom police. To make the goal of catching them even harder, they use their own watches.

First, as they know that kingdom police is bad at math, robbers use the positional numeral system with base 7. Second, they divide one day in n hours, and each hour in m minutes. Personal watches of each robber are divided in two parts: first of them has the smallest possible number of places that is necessary to display any integer from 0 to n - 1, while the second has the smallest possible number of places that is necessary to display any integer from 0 to m - 1. Finally, if some value of hours or minutes can be displayed using less number of places in base 7 than this watches have, the required number of zeroes is added at the beginning of notation.

Note that to display number 0 section of the watches is required to have at least one place.

Little robber wants to know the number of moments of time (particular values of hours and minutes), such that all digits displayed on the watches are distinct. Help her calculate this number.

Input
The first line of the input contains two integers, given in the decimal notation, n and m (1 ≤ n, m ≤ 109) — the number of hours in one day and the number of minutes in one hour, respectively.

Output
Print one integer in decimal notation — the number of different pairs of hour and minute, such that all digits displayed on the watches are distinct.

https://codeforces.com/contest/685/problem/A*/


#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define INF 1000000000000000000ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
#define endl "\n"

int _debug = 0;
#define nl        \
    cout << endl; \
    if (_debug)   \
        cerr << endl;

//-------------------------------------------------------------------------------

// print helper
int _nested = 0;
template <typename Primitive>
void print(Primitive &&P)
{
    cout << P << " ";
    if (_debug)
        cerr << P << " ";
    if (!_nested)
        nl;
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
    _nested = 1;
    print(C);
    _nested = 0;
    print(list...);
}

// scan helper
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
    scan(C);
    scan(list...);
}

// fill bulk data
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

//-------------------------------------------------------------------------------

string n7, m7;
int hlen, mlen;
int make(string &hour, string &min, int i, int j)
{
    if (i == hlen && j == mlen)
    {
        map<char, int> seen;
        for (auto j : hour)
        {
            seen[j]++;
        }

        for (auto j : min)
        {
            seen[j]++;
        }

        for (auto i : seen)
        {
            if (i.second > 1)
            {
                return 0;
            }
        }
        return 1;
    }

    int ans = 0;

    if (i < hlen)
    {
        int mxDigit = 6;
        if (hour.substr(0, i) == n7.substr(0, i))
        {
            mxDigit = n7[i] - '0';
        }
        for (int k = 0; k <= mxDigit; k++)
        {
            hour += k + '0';
            ans += make(hour, min, i + 1, j);
            hour.pop_back();
        }
    }
    else if (j < mlen)
    {
        int mxDigit = 6;
        if (min.substr(0, j) == m7.substr(0, j))
        {
            mxDigit = m7[j] - '0';
        }
        for (int k = 0; k <= mxDigit; k++)
        {
            min += k + '0';
            ans += make(hour, min, i, j + 1);
            min.pop_back();
        }
    }
    return ans;
}
void solve()
{
    int n, m;
    cin >> n >> m;

    n--, m--;

    while (n)
    {
        n7 += to_string(n % 7);
        n /= 7;
    }

    while (m)
    {
        m7 += to_string(m % 7);
        m /= 7;
    }

    if (!n7.size())
    {
        n7 += '0';
    }

    if (!m7.size())
    {
        m7 += '0';
    }
    reverse(all(n7));
    reverse(all(m7));

    if (n7.length() + m7.length() > 7)
    {
        print(0);
        return;
    }

    hlen = n7.size(), mlen = m7.size();

    int fn, fm;
    fn = n7[0] - '0';
    fm = m7[0] - '0';

    int ans = 0;

    for (int i = 0; i <= fn; i++)
    {
        for (int j = 0; j <= fm; j++)
            if (i != j)
            {
                string H, M;
                H += i + '0', M += j + '0';
                ans += make(H, M, 1, 1);
            }
    }
    print(ans);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int _t = 1;
    // cin >> _t;
    while (_t--)
        solve();
}
// cin does not move the input cursor to the next line, use cin.ignore() to move it to the next line
// use an array instead of an int whenever possible, for coding competitions