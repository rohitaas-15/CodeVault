//libraries
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>




//namespaces 
using namespace std;
using namespace __gnu_pbds;
using namespace chrono;




//utility variables
long long int _debug = 0, _nested = 0, _t = 1, _random_setup=0;
time_point <high_resolution_clock> _code_start, _code_end;
duration<double> _code_duration;




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


//Random number generator
int getRandomNumber(int start, int end) {
    static random_device rd; // Random device to generate a seed
    static mt19937 rng(rd()); // Mersenne Twister generator with random seed
    uniform_int_distribution<> dist(start, end); // Uniform distribution
    return dist(rng); // Generate and return a random number
}


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




// debug-------------------------------------------------------------------------------
#define bug(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char *name, Arg1 &&arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f(const char *names, Arg1 &&arg1, Args &&...args)
{
#ifndef ONLINE_JUDGE

    const char *comma = strchr(names + 1, ',');
    cout.write(names, comma - names) << ":" << arg1 << "|";
    __f(comma + 1, args...);

#endif
}



// policy based data
// structures---------------------------------------------------------------------------
#define indexed_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define indexed_map tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update>




// code----------------------------------------------------------------------------------



struct SegmentTree{

	vector<map<int,int> > tree;
	SegmentTree(int n)
	{
		tree.clear(), tree.resize(4*n+1);
	}

	void build(int ss , int se, int ti , vector<int> &v)
	{
		if(ss==se)
		{
			tree[ti][v[ss]]++;
			return ;
		}
		int mid = (ss+se)>>1;
		build(ss, mid, ti*2, v);
		build(mid+1, se, ti*2+1, v);
		for(auto i : tree[ti*2])
		{
			tree[ti][i.first]+=i.second;
		}
		for(auto i : tree[ti*2+1])
		{
			tree[ti][i.first]+=i.second;
		}
	}

	int query(int ss, int se, int qs, int qe, int ti, int val)
	{
		if(qs>se || qe<ss)
		{
			return 0;
		}

		if(qs<=ss && qe>=se)
		{
			return tree[ti][val];
		}
		int mid = (ss+se)>>1;
		return query(ss, mid, qs, qe, ti*2, val) + query(mid+1, se, qs, qe, ti*2+1, val);
	}
};


const int M = 22;
const int N = 1e5+2;

int tin[N+1], tout[N+1], Depth[N+1];
vector<int> flat;
int tme = 1;
vector<vector<int> > Parent(N, vector<int> (M,0));
vector<vector<int> > adj(N);

void dfs(int node, int par, int d)
{
	tin[node]=tme++;
	Depth[node]=d;

	Parent[node][0]=par;
	for(int j = 1;j<M;j++)
	{
		Parent[node][j]=Parent[Parent[node][j-1]][j-1];
	}

	for(auto i : adj[node])
	{
		if(i!=par)
		{
			dfs(i, node, d+1);
		}
	}
	tout[node]=tme;
}

int kthParent(int node, int k)
{
	for(int j = M-1;j>=0;j--)
	{
		if((k>>j) & 1)
		{
			node = Parent[node][j];
		}
	}
	return node;
}



void solve()
{
	int n;cin>>n;
	vector<int> roots;
	for(int i = 1;i<=n;i++)
	{
		int x;cin>>x;
		if(x)
		{
			adj[x].push_back(i);
		}
		else roots.push_back(i);
	}

	for(auto i : roots)
	{
		dfs(i, 0, 1);
	}


	flat.clear(), flat.resize(tme);
	for(int i = 1;i<=n;i++)
	{
		flat[tin[i]]=Depth[i];
	}


	SegmentTree T(tme+1);
	T.build(1,tme, 1, flat);


	int m;cin>>m;
	vector<int> ans;
	while(m--)
	{
		int v, p;cin>>v>>p;

		int ancestor = kthParent(v, p);
		if(!ancestor)
		{
			ans.push_back(0);
		}
		else
		{
			ans.push_back(T.query(1,tme, tin[ancestor], tout[ancestor],1, p+Depth[ancestor]) -1);
		}
	}
	print(ans);
}

signed main()
{


    _code_start =high_resolution_clock::now();
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif



    ios_base::sync_with_stdio(false), cin.tie(NULL);
    //cin >> _t;

    for (int tc = 1; tc <= _t; tc++)
    {
        // cout << "Case " << tc << ":"
        //       << " ";
        solve();
    }



    _code_end =high_resolution_clock::now();
    _code_duration = _code_end - _code_start;
     cerr << "Code executed in " << _code_duration.count() << " seconds." <<endl;

}

// 1) cin does not move the input cursor to the next line, use cin.ignore() to
// move it to the next line;

// 2) GCD(a, b, c , d...) = GCD(a,b-a,c-a,d-a...);

// 3) A reverse iterator moves backwards while doing it++