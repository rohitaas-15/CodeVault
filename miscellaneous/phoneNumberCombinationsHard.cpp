/*Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Make sure the returned strings are lexicographically sorted.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters. Printing a number once 
does not correspond to all its letters*/







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

 map<string, vector<string> > m;
 
 
 set<string> ans;
 
 
 void calculate(int index, string sub,string &digits,vector<string> &pairing)
 {
  

  
     
     if(index==digits.size())
     {


        if(sub!="")
        {
          pairing.pb(sub);
        }
        
         string temp;


     
         for(auto i : pairing)
         {
             int val = i.size();

             string ok;
             ok+=i[0];
             
             temp=temp+ m[ok][val-1];
         }
        
         ans.insert(temp);

         if(sub!="")
         {
          pairing.pop_back();
         }
         
        
         
         return ;
         
     }
     
     if(sub=="")
     {
         
         sub+=(digits[index]);
         calculate(index+1,sub,digits,pairing);
         
         pairing.push_back(sub);
         
         sub="";
         
         calculate(index+1,sub,digits,pairing);
         
         pairing.pop_back();
     }
     
     else if(sub[0]=='7' || sub[0]=='9')
     {
         if(sub.size()<4 && digits[index]==sub[0])
         {
            sub+=digits[index];
            
            calculate(index+1,sub,digits,pairing);
            sub.pop_back();
         }
         
         pairing.push_back(sub);

         string ok;
         ok+=digits[index];
         
         sub=ok;
         
     
         
         calculate(index+1,sub,digits,pairing);
         
         pairing.pop_back();
         
         
     }
     else
     {
         if(sub.size()<3 && digits[index]==sub[0])
         {
            sub+=digits[index];
            
            calculate(index+1,sub,digits,pairing);

            sub.pop_back();
         }
      
         
         pairing.push_back(sub);
         string ok;
         ok+=digits[index];
         
         sub=ok;
         
         calculate(index+1,sub,digits,pairing);
         
         pairing.pop_back();
     }
     
     return ;
     
 }


  
void solve()
{


  string digits;cin>>digits;


   
    m["2"]={"a","b","c"};
    
    m["3"]={"d","e","f"};
    
    m["4"]={"g","h","i"};
     
    m["5"]={"j","k","l"};
      
    m["6"]={"m","n","o"};
       
    m["7"]={"p","q","r","s"};
        
    m["8"]={"t","u","v"};
         
    m["9"]={"w","x","y","z"};
    
    vector<string> pairing;
    
    
    calculate(0,"",digits,pairing);


    for(auto i : ans)
    {
      print(i);
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
