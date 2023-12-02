/*https://leetcode.com/problems/closest-room*/

/*There is a hotel with n rooms. The rooms are represented by a 2D integer array rooms where rooms[i] = [roomIdi, sizei] denotes that there is a room with room number roomIdi and size equal to sizei. Each roomIdi is guaranteed to be unique.

You are also given k queries in a 2D array queries where queries[j] = [preferredj, minSizej]. The answer to the jth query is the room number id of a room such that:

The room has a size of at least minSizej, and
abs(id - preferredj) is minimized, where abs(x) is the absolute value of x.
If there is a tie in the absolute difference, then use the room with the smallest such id. If there is no such room, the answer is -1.

Return an array answer of length k where answer[j] contains the answer to the jth query.*/

#include<bits/stdc++.h>
using namespace std;

struct query{
    
    int index, sz, proom,ans;
    
    bool operator<(query &a)
    {
        return sz<a.sz;
    }
};

bool compare(vector<int> &a, vector<int> &b)
{
    return a[1]<b[1];
}

bool compare1(query &a, query &b)
{
    return a.sz<b.sz;
}

bool compare2(query &a, query &b)
{
    return a.index<b.index;
}

vector<int> closestRoom(vector<vector<int>> rooms, vector<vector<int>> queries) {
    
    vector<query> q;
    int cnt =0;
    
    for(auto i : queries)
    {
        query temp;
        temp.index=cnt;
        temp.sz=i[1];
        temp.proom=i[0];
        
        q.push_back(temp);
        cnt++;
    }
    
    sort(q.begin(),q.end(),compare1);
    sort(rooms.begin(),rooms.end(),compare);
    
    set<int> add;
    
    for(int i = q.size()-1;i>=0;i--)
    {
        while(rooms.size() && (q[i].sz<=rooms[rooms.size()-1][1]))
        {
            add.insert(rooms[rooms.size()-1][0]);
            rooms.pop_back();
        }
        
        int prefer = q[i].proom;
        
        if(!add.size())
        {
            q[i].ans=-1;
            continue;
        }
        
        auto it = add.lower_bound(prefer);
        auto temp = it;
        
        temp--;
        
        if(it==add.end())
        {
            q[i].ans=*temp;
        }
        else if(it==add.begin())
        {
            q[i].ans=*it;
        }
        else
        {
            int val1 = *temp;
            int val2 = *it;
            
            if(abs(val1-prefer)<=abs(val2-prefer))
            {
                q[i].ans=val1;
            }
            else
            {
                q[i].ans=val2;
            }
        }
    }
    sort(q.begin(),q.end(),compare2);
    vector<int> answer;
    
    for(auto i : q)
    {
        answer.push_back(i.ans);
    }
    return answer;
    
    
    
    
    
    
        
}
