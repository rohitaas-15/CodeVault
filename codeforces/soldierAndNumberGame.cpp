/*Two soldiers are playing a game. At the beginning first of them chooses a positive integer n and gives it to the second soldier. Then the second one tries to make maximum possible number of rounds. Each round consists of choosing a positive integer x > 1, such that n is divisible by x and replacing n with n / x. When n becomes equal to 1 and there is no more possible valid moves the game is over and the score of the second soldier is equal to the number of rounds he performed.

To make the game more interesting, first soldier chooses n of form a! / b! for some positive integer a and b (a ≥ b). Here by k! we denote the factorial of k that is defined as a product of all positive integers not large than k.

What is the maximum possible score of the second soldier?

Input
First line of input consists of single integer t (1 ≤ t ≤ 1 000 000) denoting number of games soldiers play.

Then follow t lines, each contains pair of integers a and b (1 ≤ b ≤ a ≤ 5 000 000) defining the value of n for a game.

Output
For each game output a maximum score that the second soldier can get.*/
//https://codeforces.com/problemset/problem/546/D

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

const int N = 5e6 + 2;
int spf[N], sumDiv[N];
int n;

void seive()
{

    for (int i = 2; i < N; i++)
    {
        if (!spf[i])
            for (int j = i; j < N; j += i)
                if (!spf[j])
                    spf[j] = i;
    }
}
void solve()
{
    int a,b;cin>>a>>b;

    print(sumDiv[a]-sumDiv[b]);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    seive();

    for (int num = 2; num < N; num++)
    {
        int temp = num;
        while (temp != 1)
        {
            sumDiv[num]++;
            temp = temp / spf[temp];
        }
    }

    for (int num = 3; num < N; num++)
    {
        sumDiv[num] = sumDiv[num - 1] + sumDiv[num];
    }

    int _t = 1;
    cin >> _t;
    while (_t--)
        solve();
}
// cin does not move the input cursor to the next line, use cin.ignore() to move it to the next line
// use an array instead of an int whenever possible, for coding competitions
