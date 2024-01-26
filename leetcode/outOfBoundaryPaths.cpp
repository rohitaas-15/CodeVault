/*There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn]. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply at most maxMove moves to the ball.

Given the five integers m, n, maxMove, startRow, startColumn, return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it modulo 109 + 7.
https://leetcode.com/problems/out-of-boundary-paths/description/?envType=daily-question&envId=2024-01-26*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll M = 1e9+7;
class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        swap(n,m);
        vector<vector<int> > prev(n+2,vector<int> (m+2,0)),cur;
        cur = prev;
        for(int i = 0;i<=n+1;i++)
        {
            for(int j = 0;j<=m+1;j++)
            {
                if(i==0 || i==n+1 || j==0 || j==m+1)
                {
                    prev[i][j]=cur[i][j]=1;
                }
            }
        }

        for(int k = 1;k<=maxMove;k++)
        {
            for(int i = 1;i<=n;i++)
            {
                for(int j = 1;j<=m;j++)
                {
                    cur[i][j]=((ll)prev[i][j-1]+(ll)prev[i][j+1]+(ll)prev[i+1][j]+(ll)prev[i-1][j])%M;
                }
            }
            prev=cur;
        }
        return cur[startRow+1][startColumn+1];
    }
    
};