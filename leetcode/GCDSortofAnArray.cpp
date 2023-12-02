// https://leetcode.com/problems/gcd-sort-of-an-array/

/*You are given an integer array nums, and you can perform the following operation any number of times on nums:

Swap the positions of two elements nums[i] and nums[j] if gcd(nums[i], nums[j]) > 1 where gcd(nums[i], nums[j]) is the greatest common divisor of nums[i] and nums[j].
Return true if it is possible to sort nums in non-decreasing order using the above swap method, or false otherwise.*/

#include <bits/stdc++.h>
using namespace std;

#define dd long double
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vpii vector<pair<int, int>>
#define pii pair<int, int>
#define vvpii vector<vpii>
#define UB upper_bound
#define LB lower_bound
#define beg(v) v.begin()
#define en(v) v.end()
#define pb push_back
#define nl "\n"
#define con continue
#define br break
#define F first
#define S second
#define yes print("YES")
#define no print("NO")
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(v) v.begin(), v.end()
#define rev(v) reverse(all(v))
#define maxv(v) *max_element(all(v));
#define minv(v) *min_element(all(v));
#define sumv(v) accumulate(all(v), 0ll)
#define print(value) cout << (value) << nl
#define print2(v1, v2) cout << (v1) << " " << (v2) << nl
#define print3(v1, v2, v3) cout << (v1) << " " << (v2) << " " << (v3) << nl
#define print4(v1, v2, v3, v4) cout << (v1) << " " << (v2) << " " << (v3) << " " << (v4) << nl
#define printv(v)                                \
  rep(it, 0, v.size()) { cout << v[it] << " "; } \
  cout << "\n"
#define printvv(v)                                          \
  rep(it, 0, v.size())                                      \
  {                                                         \
    rep(it2, 0, v[0].size()) { cout << v[it][it2] << " "; } \
    cout << "\n";                                           \
  }
#define sz(v) ((int)v.size())

int primeRange = 1e5 + 1;
vi lpf(primeRange + 1, 1);
vector<int> isPrime(primeRange + 1, 1);
void seive()
{
  isPrime[1] = 0;
  rep(i, 2, primeRange)
  {
    if (isPrime[i])
    {
      lpf[i] = i;
      for (int j = 2 * i; j <= primeRange; j += i)
      {
        isPrime[j] = 0;
        if (lpf[j] == 1)
        {
          lpf[j] = i;
        }
      }
    }
  }
}
struct DSU
{
  int n;

  vi parent, rank;

  DSU(int N)
  {
    n = N;
    parent.resize(n + 1, 0);
    rank.resize(n + 1, 1);
    iota(all(parent), 0ll);
  }

  int find(int x)
  {
    if (parent[x] == x)
      return x;

    // path compression

    return parent[x] = find(parent[x]);
  }

  void join(int x, int y)
  {
    int s1 = find(x);
    int s2 = find(y);

    if (s1 != s2)
    {
      // union by rank
      if (rank[s1] > rank[s2])
      {
        parent[s2] = s1;
        rank[s1] += rank[s2];
      }
      else
      {
        parent[s1] = s2;
        rank[s2] += rank[s1];
      }
    }
  }
};

class Solution
{
public:
  bool gcdSort(vector<int> &nums)
  {

    seive();
    int n = nums.size();
    vi v = nums;
    DSU g(1e5 + 1);

    rep(i, 0, n)
    {
      int temp = v[i];
      while (lpf[temp] != 1)
      {
        g.join(v[i], lpf[temp]);
        temp /= lpf[temp];
      }
    }
    vi temp = v;
    bool ans = 1;
    sort(all(temp));
    rep(i, 0, n)
    {
      if (g.find(v[i]) != g.find(temp[i]))
      {
        ans = false;
        br;
      }
    }
    return (ans);
  }
};
