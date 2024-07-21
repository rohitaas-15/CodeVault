#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
long long int _debug = 0, _nested = 0, _t = 1;
// macros-------------------------------------------------------------------------------
#define ll long long
#define int ll
#define all(x) x.begin(), x.end()
#define rep(i, x, n) for (int(i) = (x); (i) < (n); (i)++)
#define endl "\n"
#define nl        \
    cout << endl; \
    if (_debug)   \
        cerr << endl ;
 
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
 
 
//debug-------------------------------------------------------------------------------
#define bug(...)  __f (#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f (const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f (const char* names, Arg1&& arg1, Args&&... args)
{
     #ifndef ONLINE_JUDGE 
 
     	const char* comma = strchr (names + 1, ',');
	    cout.write (names, comma - names) << ":" << arg1 << "|"; __f (comma + 1, args...);
                    
    #endif 
 
}
 
 
// policy based data
// structures---------------------------------------------------------------------------
#define indexed_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define indexed_map tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update>
 
// code----------------------------------------------------------------------------------
 
const int M = 1e9+7;
int power(int a, int b, int MOD = M)
{
	if(b==0)
	{
		return 1ll;
	}
 
	int smallAns = power(a,b/2,MOD);
	smallAns=(smallAns*smallAns)%MOD;
 
	if(b&1)
	{
		return (smallAns*a)%MOD;
	}
	return smallAns;
}
 
int moduloDivide(int a, int b, int mod)
{
	return ((a%M)*(power((b%M),mod-2,mod)))%M;
}


int nChoose2(int n)
{
	return moduloDivide((n*(n-1))%M,2ll,M);
}

void solve()
{
	int n;cin>>n;
	vector<int> v(n);
	for(int i = 0;i<n;i++)
	{
		cin>>v[i];
	}
	sort(all(v));
	reverse(all(v));

	int dp[n+1]; //expected value for i people (in the same test case)
	dp[2]=v[1]; //as v is reverse sorted now

	for(int i = 3;i<=n;i++)
	{
		//this person is the second last place

		//all matches should be between previous i-1 people;

		int no = moduloDivide(1,nChoose2(i),M);

		dp[i]=(no*(v[i-1]))%M ;

		//this person is not the second last, answer is already calculated

		dp[i]= (dp[i] + (((1-no+M)%M)*(dp[i-1]))%M)%M;
	}
	print(dp[n]);
}
 
signed main()
{
 
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
 
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    cin >> _t;
 
 
    for (int tc = 1; tc <= _t; tc++)
    {
        // cout << "Case " << tc << ":"
        //       << " ";
        solve();
    }
}
 
// cin does not move the input cursor to the next line, use cin.ignore() to
// move it to the next line
