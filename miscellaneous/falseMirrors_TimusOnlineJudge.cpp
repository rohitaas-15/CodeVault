/*1152. False Mirrors
Time limit: 2.0 second
Memory limit: 64 MB
Background
We wandered in the labyrinth for twenty minutes before finally entering the large hall. The walls were covered by mirrors here as well. Under the ceiling hung small balconies where monsters stood. I had never seen this kind before. They had big bulging eyes, long hands firmly holding riffles and scaly, human-like bodies. The guards fired at me from the balconies, I shot back using my BFG-9000. The shot shattered three mirrors filling the room with silvery smoke. Bullets drummed against my body-armor knocking me down to the floor. Falling down I let go a shot, and got up as fast as I fell down by rotating on my back, like I did in my youth while break dancing, all this while shooting three more times. Three mirrors, three mirrors, three mirrors…
Sergey Lukjanenko, “The Labyrinth of Reflections”
Problem
BFG-9000 destroys three adjacent balconies per one shoot. (N-th balcony is adjacent to the first one). After the shoot the survival monsters inflict damage to Leonid (main hero of the novel) — one unit per monster. Further follows new shoot and so on until all monsters will perish. It is required to define the minimum amount of damage, which can take Leonid.
Input
The first line contains integer N, аmount of balconies, on which monsters have taken a circular defense. 3 ≤ N ≤ 20. The second line contains N integers, amount of monsters on each balcony (not less than 1 and no more than 100 on each).
Output
Output minimum amount of damage.
https://acm.timus.ru/problem.aspx?space=1&num=1152*/
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

void solve()
{
    int n;
    cin >> n;
    vector<int> monsters(n);
    for (int i = 0; i < n; i++)
    {
        cin >> monsters[i];
    }


    int dp[1ll<<n];
    dp[0]=0;
    for(int i = 1;i< (1ll<<n);i++)
    {
        int sum = 0;
        dp[i]=INF;
        for(int j = 0;j<n;j++)
        {
            if(i & (1ll<<j))
            {
                sum += monsters[n-1-j];
            }
        }

        for(int j = 0;j<n;j++) //using bitmasks to store the alive balcony of monsters and shooting 1 shot, calculating the answer through dp
        {
            int index = j;
            int damage = 0,mask=0;

            damage+=(i &(1ll<<(n-1-index)))?monsters[index]:0ll;
            mask = mask | 1ll<<(n-1-index);

            index= (index+1)%n;
            damage+=(i &(1ll<<(n-1-index)))?monsters[index]:0ll;
            mask = mask | 1ll<<(n-1-index);

            index= (index+1)%n;
            damage+=(i &(1ll<<(n-1-index)))?monsters[index]:0ll;
            mask = mask | 1ll<<(n-1-index);

            dp[i]=min(dp[i],sum-damage+dp[i&(~mask)]);
        }
    }

    print(dp[(1ll<<n)-1]);
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