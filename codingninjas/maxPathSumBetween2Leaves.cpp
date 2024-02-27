
/*You are given a non-empty binary tree where each node has a non-negative integer value. Return the maximum possible sum of path between any two leaves of the given tree.

The path is also inclusive of the leaf nodes and the maximum path sum may or may not go through the root of the given tree.

If there is only one leaf node in the tree, then return -1.
https://www.codingninjas.com/studio/problem-of-the-day/hard*/
#include <bits/stdc++.h>
using namespace std;

// Following is the Tree node structure

template <typename T>
class TreeNode
{
public:
    T val;
    TreeNode<T> *left;
    TreeNode<T> *right;

    TreeNode(T val)
    {
        this->val = val;
        left = NULL;
        right = NULL;
    }
};

const int INF = 1e9;
pair<int, int> maxPath(TreeNode<int> *root) // max answer in subtree, max path till root
{
    if (root->left == NULL && root->right == NULL)
    {
        return make_pair(-INF, root->val);
    }
    else if (root->left == NULL)
    {
        auto right = maxPath(root->right);

        return make_pair(max(-INF, right.first), root->val + right.second);
    }
    else if (root->right == NULL)
    {
        auto left = maxPath(root->left);
        return make_pair(max(-INF, left.first), root->val + left.second);
    }

    auto left = maxPath(root->left);
    auto right = maxPath(root->right);

    return make_pair(max({left.first, right.first, left.second + right.second + root->val}), max(left.second, right.second) + root->val);
}

long long int findMaxSumPath(TreeNode<int> *root)
{
    if (root == NULL)
        return -1;
    auto ans = maxPath(root);
    if (ans.first == -INF)
    {
        ans.first = -1;
    }
    return ans.first;
}