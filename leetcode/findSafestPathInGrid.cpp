//https://leetcode.com/problems/find-the-safest-path-in-a-grid/?envType=daily-question&envId=2024-05-15

/*You are given a 0-indexed 2D matrix grid of size n x n, where (r, c) represents:

A cell containing a thief if grid[r][c] = 1
An empty cell if grid[r][c] = 0
You are initially positioned at cell (0, 0). In one move, you can move to any adjacent cell in the grid, including cells containing thieves.

The safeness factor of a path on the grid is defined as the minimum manhattan distance from any cell in the path to any thief in the grid.

Return the maximum safeness factor of all paths leading to cell (n - 1, n - 1).

An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) and (r - 1, c) if it exists.

The Manhattan distance between two cells (a, b) and (x, y) is equal to |a - x| + |b - y|, where |val| denotes the absolute value of val.*/
#include <bits/stdc++.h>
using namespace std;

int manhattan[401][401];
int vis[401][401];
bool canReach(int x, int y, int mn,vector<vector<int>>& grid)
{
    int n = grid.size(), m = grid[0].size();
    if(x==n-1 && y==n-1)
    {
        return true;
    }
    if(x<0 || x>=n || y<0 || y>=m)
    {
        return false;
    }
    vis[x][y]=1;
    for(int i = -1;i<=1;i++)for(int j = -1;j<=1;j++)if(abs(i)!=abs(j))
    {
        int nx = x+i, ny = y+j;
        if(nx>=0 && nx<n && ny>=0 && ny<m && !vis[nx][ny] && manhattan[nx][ny]>=mn)
        {
            bool yes = canReach(nx,ny,mn,grid);
            if(yes)return yes;
        }
    }
    return false;
}
class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {

        memset(manhattan,-1,sizeof(manhattan));
        queue<pair<int,int> > q;
        for(int i = 0;i<grid.size();i++)
        {
            for(int j = 0;j<grid[0].size();j++)
            {
                if(grid[i][j])
                {
                    q.push({i,j});
                    manhattan[i][j]=0;
                }
            }
        }
        while(!q.empty())
        {
            auto node = q.front();
            q.pop();
            for(int i = -1;i<=1;i++)for(int j = -1;j<=1;j++)if(abs(i)!=abs(j))
            {
                int nx = node.first+i, ny = node.second + j;
                if(nx>=0 && nx<grid.size() && ny>=0 && ny<grid[0].size() && manhattan[nx][ny]==-1)
                {
                    manhattan[nx][ny]=manhattan[node.first][node.second]+1;
                    q.push({nx,ny});
                }
            }
        }

        int high = 801, low = 0, minManhattan, ans;
        while(low<=high)
        {
            minManhattan = (low+high)>>1;
            memset(vis,0,sizeof(vis));
            if(manhattan[0][0]>=minManhattan && canReach(0,0, minManhattan, grid))
            {
                ans = minManhattan, low = minManhattan+1;
            }
            else high = minManhattan-1;
        }
        return ans;
        
    }
};