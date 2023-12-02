//rohitaas_beri
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define dd long double
#define ub upper_bound
#define lb lower_bound
#define pb push_back
#define vi vector<int> 
#define vii vector<pair<int,int> >
#define nl "\n"
#define con continue
#define br break
#define rep(i,a,b) for(int i =(a);i<(b);i++)
#define all(vector_name) vector_name.begin(),vector_name.end()
#define print(value)  cout<<(value)<<nl;
#define print2(value1,value2) cout<<(value1)<<" "<<(value2)<<nl;
#define print3(value1,value2,value3) cout<<(value1)<<" "<<(value2)<<" "<<(value3)<<nl;
#define printv(vector_name)rep(i,0,vector_name.size()){cout<<vector_name[i]<<" ";}cout<<"\n";
#define scan(vector_name) rep(i,0,vector_name.size()){cin>>vector_name[i];}
#define sz(structure) ((int)structure.size())


int fact(int n)
{
    int ans =1;
    rep(i,1,n+1)
    {
        ans = ans *i;
    }
    return ans;
}


void solve()
{

    string s;
    cin>>s;
    int n = s.size();
    vector<int> v(26,0);
    rep(i,0,n)
    {
        v[s[i]-'a']++;
    }
    int cnt =0;
    rep(i,0,n)
    {
        rep(j,0,v.size())
        {
            char c = 'a'+j;
            if(c==s[i] && v[j]>0)
            {
                v[j]--;
                break;
            }
            else if(v[j]>0)
            {
                v[j]--;
                int add = fact(n-i-1);
                rep(k,0,v.size())
                {
                    add = add/fact(v[k]);
                }
                cnt+=add;
                v[j]++;
            }
           
        }
    }
    cnt++;
    cout<<"Rank "<<cnt<<" in the dictionary made by the letters of the word '"<<s<<"'"<<endl;
}
signed main() {

    ios_base::sync_with_stdio(false); cin.tie(NULL);
    clock_t printClock = clock();

    int T=1;
    cin>>T;

    while(T--) solve();

    cerr<< "RUNTIME : "<<((double)clock()-printClock)/CLOCKS_PER_SEC;
}
