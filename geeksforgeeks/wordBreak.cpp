/*Given a string A and a dictionary of n words B, find out if A can be segmented into a space-separated sequence of dictionary words. Return 1 if it is possible to break A into sequence of dictionary words, else return 0. 

Note: From the dictionary B each word can be taken any number of times and in any order.
https://www.geeksforgeeks.org/problems/word-break1352/1*/
//{ Driver Code Starts
// Initial template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function template for C++

// A : given string to search
// B : vector of available strings
struct Node
{

    vector<Node *> children;
    bool isLeaf;
    Node()
    {
        children.clear();
        children.resize(26, NULL);
        isLeaf = false;
    }
};

struct Trie
{

    Node *root;
    Trie()
    {
        root = new Node();
    }

    void addWord(string word)
    {
        Node *temp = root;
        for (int i = 0; i < word.size(); i++)
        {
            if (temp->children[word[i] - 'a'] == NULL)
            {
                temp->children[word[i] - 'a'] = new Node();
            }
            temp = temp->children[word[i] - 'a'];
        }
        temp->isLeaf = true;
    }
};

class Solution
{
public:
    int wordBreak(string A, vector<string> &B)
    {
        Trie t;
        for (auto &i : B)
        {
            reverse(i.begin(), i.end());
            t.addWord(i);
        }

        int n = A.size();
        int dp[n + 1];
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            Node *temp = t.root;
            for (int j = i; j >= 1; j--)
            {
                if (temp->children[A[j - 1] - 'a'] == NULL)
                {
                    break;
                }

                temp = temp->children[A[j - 1] - 'a'];
                if (temp->isLeaf && dp[j - 1])
                {
                    dp[i] = 1;
                    break;
                }
            }
        }
        return dp[n];
    }
};

//{ Driver Code Starts.

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<string> dict;
        for (int i = 0; i < n; i++)
        {
            string S;
            cin >> S;
            dict.push_back(S);
        }
        string line;
        cin >> line;
        Solution ob;
        cout << ob.wordBreak(line, dict) << "\n";
    }
}

// } Driver Code Ends