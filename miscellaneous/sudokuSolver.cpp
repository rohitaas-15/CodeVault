//rohitaas_beri
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// #define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define int ll
#define dd long double
#define vi vector<int> 
#define vvi vector<vi> 
#define vvvi vector<vvi>
#define vpii vector<pair<int,int> > 
#define pii pair<int,int> 
#define vvpii vector<vpii> 
#define ub upper_bound
#define lb lower_bound
#define beg(v) v.begin()
#define en(v) v.end()
#define pb push_back
#define nl "\n"
#define con continue
#define br break
#define ret return;
#define yes print("YES")
#define no print("NO")
#define rep(i,a,b) for(int i =(a);i<(b);i++)
#define all(v) v.begin(),v.end()
#define rev(v) reverse(all(v))
#define maxv(v) *max_element(all(v));
#define minv(v) *min_element(all(v));
#define sumv(v) accumulate(all(v),0)
#define print(value)  cout<<(value)<<nl
#define print2(v1,v2) cout<<(v1)<<" "<<(v2)<<nl
#define print3(v1,v2,v3) cout<<(v1)<<" "<<(v2)<<" "<<(v3)<<nl
#define printv(v)rep(it,0,v.size()){cout<<v[it]<<" ";}cout<<"\n"
#define sz(v) ((int)v.size())

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
bool canPlace(int num, int x , int y, vvi &board, int n)
{
  rep(i,0,n)
  {
    if(board[x][i]==num && i!=y)
    {
      return false;
    }

    if(board[i][y]==num && i!=x)
    {
      return false;
    }
  }

  int sz = 0;
  while(sz*sz<n)sz++;

  int subx= x/sz;
  int suby = y/sz;

  int subi=subx*sz;
  int subj=suby*sz;

 

  rep(i,subi,subi+sz)
  {
    rep(j,subj,subj+sz)
    {
      if(board[i][j]==num && i!=x && j!=y)
      {
        return false;
      }
    }
  }

  return true;
}


void printSudoku(vvi &board,int n)
{

  int sz = 0;
  while(sz*sz<n)sz++;

  rep(i,0,n){

    if(i%sz==0 && i!=0)
    {
      rep(k,0,2*n+sz)
      {
        cout<<"-";
      }

      cout<<nl;
    }


    rep(j,0,n)
    {
      if(j%sz==0 && j!=0)
      {
        cout<<"| ";
      }

      cout<<board[i][j]<<" ";
    }
    cout<<nl;

  }

}


int canFlag=1;



bool sudoku(int i , int j, vvi &board, int n)
{


  


  if(i==n && j==0)
  {
    
    printSudoku(board,n);
    return true;
  }

  if(j==n)
  {
    return sudoku(i+1,0,board,n);
  }

  if(board[i][j]!=0)
  {
    if(canPlace(board[i][j],i,j,board,n))
    {
      return sudoku(i,j+1,board,n);
      
    }

    return false;
    
  }

  rep(k,1,n+1)
  {
    if(canPlace(k,i,j,board,n)){

      board[i][j]=k;

      bool success = sudoku(i,j+1,board, n);

      if(success)
      {
        return true;
      }

      board[i][j]=0;

    }
  }
  return false;
}


  
void solve()
{


  int n;cin>>n;

  vvi grid(n,vi(n,0));

  rep(i,0,n)
  {
    rep(j,0,n)
    {
      cin>>grid[i][j];
    }
  }

  //check the input

  canFlag=1;

  rep(i,0,n)
  {
    rep(j,0,n)
    {
      if(grid[i][j]!=0 && ((grid[i][j]<1 || grid[i][j]>n) || !canPlace(grid[i][j],i,j,grid,n)))
      {
        canFlag=0;
        br;
      }
    }

    if(!canFlag)
    {
      br;
    }
  }

  if(canFlag)
  sudoku(0,0,grid,n);



  if(!canFlag)
  {
    print("Invalid Input!");
  }

}

signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(0);

    

    clock_t printClock = clock();

    int T=1;
    cin>>T;

 

    while(T--) solve();

    cerr<< "RUNTIME : "<<((double)clock()-printClock)/CLOCKS_PER_SEC<<"s";
}




/* notes:

1) Dont use vector.resize() without vector.clear() .

2) Range of long long is -2^63 to 2^63-1 , range of unsigned long long 
   is 0 to 2^64-1 .

3) Expected number of coin throws to get N consecutive heads is 2^(n+1) - 2 .

4) Upper bound of number of divisors of a number n is n^(1/3) .

5) 𝐺𝐶𝐷(𝑥,𝑦)=𝐺𝐶𝐷(𝑥−𝑦,𝑦) , The same applies for multiple arguments: 𝐺𝐶𝐷(𝑥,𝑦,𝑧,…)=𝐺𝐶𝐷(𝑥−𝑦,𝑦,𝑧,…),
   𝐺𝐶𝐷(𝑎1+𝑏𝑗,…,𝑎𝑛+𝑏𝑗)=𝐺𝐶𝐷(𝑎1+𝑏𝑗,𝑎2−𝑎1,…,𝑎𝑛−𝑎1) .

6) To meet the constraints int the question,  we can sometimes kick out one state of our dp.
  We can achieve that by a relatively common trick: turn the removed state into the value of the dp.


7) If we have N elements out of which we want to choose K elements and it is allowed
  to choose one element more than once, then number of ways are given by: nCr(n+k-1,k) .


*/


/* Good Questions :

1 ) https://www.codechef.com/submit/SECPLAYER

 */
