//https://leetcode.com/problems/student-attendance-record-ii/?envType=daily-question&envId=2024-05-26

#include <bits/stdc++.h>
using namespace std;

const long M  = 1e9+7;
class Solution {
public:
    int checkRecord(int n) {

        long  noAbsentDP[n+5];//only P and L present
        noAbsentDP[0]=1, noAbsentDP[1]=2, noAbsentDP[2]=4;
        for(int i = 3;i<=n;i++)
        {
            noAbsentDP[i]=(noAbsentDP[i-1]+noAbsentDP[i-2]+noAbsentDP[i-3])%M; //no 3 consecutive L allowed
        }

        long ans = noAbsentDP[n]; //no absent present in the attendence record
        for(int index=1;index<=n;index++)
        {
            //put 1 absent on this day (index), and separately calculate the attendence record(meeting the criteria)
            // for the previous and the next days
            ans =(ans+ (noAbsentDP[index-1]*noAbsentDP[n-index])%M)%M;                             
        }
        return ans;    
    }
};