/*Given a binary tree where node values are digits from 1 to 9. A path in the binary tree is said to be pseudo-palindromic if at least one permutation of the node values in the path is a palindrome.

Return the number of pseudo-palindromic paths going from the root node to leaf nodes.

 

Example 1:



Input: root = [2,3,1,3,1,null,1]
Output: 2 
Explanation: The figure above represents the given binary tree. There are three paths going from the root node to leaf nodes: the red path [2,3,3], the green path [2,1,1], and the path [2,3,1]. Among these paths only red path and green path are pseudo-palindromic paths since the red path [2,3,3] can be rearranged in [3,2,3] (palindrome) and the green path [2,1,1] can be rearranged in [1,2,1] (palindrome).
https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/description/?envType=daily-question&envId=2024-01-24*/
#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

int cnt = 0;
void check(TreeNode *root, int &mask)
{
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL)
    {
        int previous = mask;
        mask = mask ^ (1 << (root->val));
        cnt += (__builtin_popcount(mask) <= 1);
        mask = previous;
        return;
    }

    int previous = mask;
    mask = mask ^ (1 << (root->val));
    check(root->left, mask);
    check(root->right, mask);
    mask = previous;
}
class Solution
{
public:
    int pseudoPalindromicPaths(TreeNode *root)
    {
        cnt = 0;
        int mask = 0;
        check(root, mask);
        return cnt;
    }
};