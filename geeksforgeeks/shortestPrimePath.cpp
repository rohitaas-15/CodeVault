/*You are given two four digit prime numbers Num1 and Num2. Find the distance of the shortest path from Num1 to Num2 that can be attained by altering only single digit at a time such that every number that we get after changing a digit is a four digit prime number with no leading zeros.
https://www.geeksforgeeks.org/problems/shortest-prime-path--141631/1*/
//{ Driver Code Starts
// Initial Template for C++
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

int testcase = 0;
vector<int> primes;
vector<vector<int>> adj(10000);
class Solution
{
public:
    int solve(int num1, int num2)
    {

        if (!testcase)
        {
            for (int i = 1000; i <= 9999; i++)
            {
                int flag = 0;
                for (int j = 2; j * j <= i; j++)
                {
                    if (i % j == 0)
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag)
                    continue;
                else
                    primes.push_back(i);
            }

            for (auto i : primes)
                for (auto j : primes)
                {
                    string t1 = to_string(i), t2 = to_string(j);
                    int cnt = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        if (t1[i] != t2[i])
                        {
                            cnt++;
                        }
                    }
                    if (cnt == 1)
                        adj[i].push_back(j);
                }
        }

        vector<int> dis(10000, 1e9);
        queue<int> q;
        dis[num1] = 0;
        q.push(num1);
        while (q.size())
        {
            auto node = q.front();
            q.pop();

            for (auto i : adj[node])
            {
                if (dis[i] == 1e9)
                {
                    dis[i] = dis[node] + 1;
                    q.push(i);
                }
            }
        }
        if (dis[num2] == 1e9)
            dis[num2] = -1;
        testcase++;
        return dis[num2];
    }
};

//{ Driver Code Starts.
signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int Num1, Num2;
        cin >> Num1 >> Num2;
        Solution obj;
        int answer = obj.solve(Num1, Num2);
        cout << answer << endl;
    }
}
// } Driver Code Ends