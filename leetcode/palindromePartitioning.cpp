//https://leetcode.com/problems/palindrome-partitioning-ii/submissions/


class Solution {
public:
    int minCut(string s) {

    int n = s.size();

    vector<vector<int> > isPalindrome(n+1,vector<int> (n+1,0));

    for(int i =0;i<=n;i++)
    {
        isPalindrome[i][i]=1;
    }

    for(int len = 2;len<=n;len++)
    {
        for(int i =0;i<n-len+1;i++){
            int j = i+len-1;

            if(j-i+1==2)
            {
                if(s[i]==s[j])
                {
                    isPalindrome[i][j]=1;
                }
            }
            else
            {
                if(s[i]==s[j])
                {
                    isPalindrome[i][j]=isPalindrome[i+1][j-1];
                }
            }
        }
    }

    vector<int> dp(n+1,1e9);

    dp[1]=0;
    dp[0]=-1;

    for(int i =1;i<=n;i++)
    {
        for(int j = i;j>=1;j--){
            if(isPalindrome[j-1][i-1]){
                dp[i]=min(dp[i],1+dp[j-1]);
            }
        }
    }
    return dp[n];

        
    }
};
