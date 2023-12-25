/*Once upon a time DravDe, an outstanding person famous for his professional achievements (as you must remember, he works in a warehouse storing Ogudar-Olok, a magical but non-alcoholic drink) came home after a hard day. That day he had to drink 9875 boxes of the drink and, having come home, he went to bed at once.

DravDe dreamt about managing a successful farm. He dreamt that every day one animal came to him and asked him to let it settle there. However, DravDe, being unimaginably kind, could send the animal away and it went, rejected. There were exactly n days in DravDe’s dream and the animal that came on the i-th day, ate exactly ci tons of food daily starting from day i. But if one day the animal could not get the food it needed, it got really sad. At the very beginning of the dream there were exactly X tons of food on the farm.

DravDe woke up terrified...

When he retold the dream to you, he couldn’t remember how many animals were on the farm by the end of the n-th day any more, but he did remember that nobody got sad (as it was a happy farm) and that there was the maximum possible amount of the animals. That’s the number he wants you to find out.

It should be noticed that the animals arrived in the morning and DravDe only started to feed them in the afternoon, so that if an animal willing to join them is rejected, it can’t eat any farm food. But if the animal does join the farm, it eats daily from that day to the n-th.

Input
The first input line contains integers n and X (1 ≤ n ≤ 100, 1 ≤ X ≤ 104) — amount of days in DravDe’s dream and the total amount of food (in tons) that was there initially. The second line contains integers ci (1 ≤ ci ≤ 300). Numbers in the second line are divided by a space.

Output
Output the only number — the maximum possible amount of animals on the farm by the end of the n-th day given that the food was enough for everybody.*/
//https://codeforces.com/problemset/problem/35/D
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

const int N = 102, X = 1e4 + 2;
int dp[N][X], animal[N];
int n;

int maxAnimals(int i, int W)
{

    if (i == n)
    {
        return 0;
    }

    if (dp[i][W] != -1)
    {
        return dp[i][W];
    }

    if (W >= (n - i) * animal[i])
    {
        dp[i][W] = max(dp[i][W], 1 + maxAnimals(i + 1, W - (n - i) * animal[i]));
    }

    dp[i][W] = max(dp[i][W], maxAnimals(i + 1, W));

    return dp[i][W];
}

void solve()
{
    ifstream input;
    ofstream output;
    input.open("input.txt");
    output.open("output.txt");
    int x;
    input >> n >> x;
    for (int i = 0; i < n; i++)
    {
        input >> animal[i];
    }
    memset(dp, -1ll, sizeof(dp));
    output << maxAnimals(0, x);
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