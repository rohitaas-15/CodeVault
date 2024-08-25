/*
You are given a tree with 'N' vertices, where each vertex has an assigned integer. You are given 'Q' queries where each query can be of two types:

1 'U' 'V': Reverse the order of all the integers on the path between 'U' and 'V'.
2 'U' 'V': Print the sum of all the integers on the path between 'U' and 'V'.


1 <= N,Q <= 10^4
1 <= u,v <= N
1 <= value[i] <= 10^4

https://www.naukri.com/code360/problems/tree-queries_1813575?leftPanelTabValue=PROBLEM

*/


#include <bits/stdc++.h>
using namespace std;
struct FenwickTree{

    vector<int> BIT;
    int sz;

    void update(int index, int val) //index is assumed 1 based
    {
        while(index<sz)
        {
            BIT[index]+=val;
            index+=index&-index;
        }
    }
    FenwickTree(vector<int> &v)
    {
        int n = v.size();
        BIT.clear(), BIT.resize(n+1,0);
        sz = n+1;

        for(int i = 0;i<n;i++)
        {
            update(i+1, v[i]);
        }
    }

    int query(int index)
    {
        int ans = 0;
        while(index>0)
        {
            ans+=BIT[index];
            index-=index&-index;
        }
        return ans;
    }

    //sum query
    int query(int l, int r)//l and r are 0 based
    {
        return query(r+1)-query(l-1 + 1);
    }
};
struct HLD{

    vector<int> parent, depth, subtree, max_subtree, height;
    vector<int> head, ci, cai;
    vector<vector<int> > ca, adj;
    vector<FenwickTree> fenwicks;
    int cnt=0;

    void dfs(int node, int par, int dep)
    {
        parent[node]=par;
        depth[node]=dep;
        subtree[node]=1;
        int mx=0;
        for(auto i : adj[node])
        {
            if(i!=par)
            {
                dfs(i,node, dep+1);
                subtree[node]+=subtree[i];
                if(mx<subtree[i])
                {
                    mx = subtree[i];
                    max_subtree[node]=i;
                }
            }
        }
    }

    void decompose(int node, int par, int chead)
    {
        head[node]=chead;
        ci[node]=cnt;
        ca[ci[node]].push_back(node);
        cai[node]=ca[ci[node]].size()-1;


        if(!max_subtree[node])
        {
            return;
        }

        decompose(max_subtree[node], node, chead);
        for(auto i : adj[node])if(i!=par && i!=max_subtree[node])
        {
            cnt++;
            decompose(i, node, i);
        } 
    }

    HLD(int n, vector<vector<int> > &edges, vector<int> &height)
    {
        n++;
        parent.resize(n);
        depth.resize(n);
        subtree.resize(n);
        max_subtree.resize(n, 0);
        head.resize(n,0);
        ci.resize(n,0);
        cai.resize(n,0);
        ca.resize(n);
        adj.resize(n);

        for(auto i : edges)
        {
            adj[i[0]].push_back(i[1]); 
            adj[i[1]].push_back(i[0]);
        }

        dfs(1, 0,0);
        decompose(1,0,1);

        for(int i = 0;i<ca.size();i++)
        {
            for(int j = 0;j<ca[i].size();j++)
            {
                ca[i][j]=height[ca[i][j]-1]; //height is 0 based
            }
        }

        for(int i = 0;i<ca.size();i++)
        {
            FenwickTree F(ca[i]);
            fenwicks.push_back(F);
        }
        this->height= height;
    }

    //according to question

    vector<int> makePath(int a, int b)
    {
        vector<int> aPath, bPath; // to their LCA
        if(depth[a]>depth[b])
        {
            swap(a,b);
        }

        while(depth[b]!=depth[a])
        {
            bPath.push_back(b);
            b = parent[b];
        }

        while(a!=b)
        {
            aPath.push_back(a);
            bPath.push_back(b);
            a=parent[a];
            b=parent[b];
        }

        vector<int> path;
        for(auto i : aPath)path.push_back(i);

        path.push_back(a);//adding LCA

        reverse(bPath.begin(),bPath.end());
        for(auto i : bPath)path.push_back(i);

        return path;
    }

    void reversePath(int a, int b)
    {
        auto path = makePath(a, b);

        int i =0, j = path.size()-1;

        while(i<j)
        {
            int previousIVal = height[path[i]-1];
            int currentIVal = height[path[j]-1];
            int iDiff = currentIVal-previousIVal;
            fenwicks[ci[path[i]]].update(cai[path[i]]+1,iDiff);

            int previousJVal = height[path[j]-1];
            int currentJVal = height[path[i]-1];
            int jDiff = currentJVal-previousJVal;
            fenwicks[ci[path[j]]].update(cai[path[j]]+1,jDiff);

            height[path[i]-1]= currentIVal;
            height[path[j]-1]=currentJVal;
            i++, j--;
        }
    }

    int query(int a, int b)
    {
        int ans = 0;

        while(head[a]!=head[b])
        {
            if(depth[head[a]]>depth[head[b]])
            {
                swap(a,b);
            }

            ans= ans + fenwicks[ci[b]].query(cai[head[b]], cai[b]);
            b = parent[head[b]];
        }

        if(depth[a]>depth[b])swap(a,b);
        ans +=fenwicks[ci[b]].query(cai[a], cai[b]);
        return ans;
    }
};


vector<int> treeQuery(int n,int q,vector<vector<int>> &edges,vector<int> &height,vector<vector<int>> &queries){

    HLD hld(n, edges, height);
    vector<int> ans;
    for(int i = 0;i<q;i++)
    {
        int type = queries[i][0];
        if(type==1)
        {
            hld.reversePath(queries[i][1], queries[i][2]);
        }
        else ans.push_back(hld.query(queries[i][1], queries[i][2]));
    }
    return ans;
   
}