
/*https://leetcode.com/problems/word-ladder/

A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

Every adjacent pair of words differs by a single letter.
Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
sk == endWord
Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.*/




#define dd long double
#define vi vector<int> 
#define vvi vector<vi> 
#define vvvi vector<vvi>
#define vpii vector<pair<int,int> > 
#define pii pair<int,int> 
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
#define rep(i,a,b) for(int i =(a);i<(b);i++)
#define all(v) v.begin(),v.end()
#define rev(v) reverse(all(v))
#define maxv(v) *max_element(all(v));
#define minv(v) *min_element(all(v));
#define sumv(v) accumulate(all(v),0ll)
#define print(value)  cout<<(value)<<nl
#define print2(v1,v2) cout<<(v1)<<" "<<(v2)<<nl
#define print3(v1,v2,v3) cout<<(v1)<<" "<<(v2)<<" "<<(v3)<<nl
#define print4(v1,v2,v3,v4) cout<<(v1)<<" "<<(v2)<<" "<<(v3)<<" "<<(v4)<<nl
#define printv(v)rep(it,0,v.size()){cout<<v[it]<<" ";}cout<<"\n"
#define printvv(v)rep(it,0,v.size()){rep(it2,0,v[0].size()){cout<<v[it][it2]<<" ";}cout<<"\n";}
#define sz(v) ((int)v.size())


//Template Graph

template<typename T> struct Graph{

  int n;
  map<T,vector<T> > adj;
  map<T, int> vis;

  //adding edges


  void addEdge(T x, T y, int undir = true)
  {
    adj[x].pb(y);

    if(undir)
    {
      adj[y].pb(x);
    }
  }

  //DFS

   void dfs(T node)
  {
    vis[node]=1;

    //variable

    for(auto i : adj[node])
    {
      if(!vis[i])
      {
        dfs(i);
      }
    }
  }

  //BFS


  int bfs(T node,string en,map<string, int>  &words)
  {
    map<string,int> temp;
    vis=temp;
    queue<T> q;


    map<string, int> dis;

    q.push(node);
    vis[node]=1;
    dis[node]=1;

    //variable

    while(!q.empty())
    {
      T check = q.front(); q.pop();
      for(auto i : adj[check])
      {
        if(!vis[i])
        {
          
          dis[i]=dis[check]+1;
          vis[i]=1;
          if(i==en)
          {
            return dis[en];
          }
          q.push(i);
        }
      }
    }
    return dis[en];
  }

};



Graph<string> g;

void makeGraph(string node,string &en, map<string, int>  &words)
{
  queue<string> q;

  q.push(node);
  g.vis[node]=1;

  while(!q.empty())
  {

    string c = q.front();
    q.pop();
    for(int i =0;i<sz(c);i++)
    {
      
        string temp;
      
        rep(j,0,26)
        {
          temp = c;
          temp[i]=j+'a';

          if(words.count(temp))
          {
            if(!g.vis[temp])
            {
              g.vis[temp]=1;
              g.addEdge(c, temp,0);
              q.push(temp);
            }
          }
        }
    }
  }
}




class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
  g.adj.clear();
  map<string, int> words;
  int n;n = wordList.size();

  rep(i,0,n)
  {
    words[wordList[i]]++;
  }
  g.vis.clear();
  makeGraph(beginWord,endWord,words);
  g.vis.clear();
  return (g.bfs(beginWord,endWord,words));

        
    }
};
