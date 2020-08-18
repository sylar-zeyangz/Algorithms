/*
Given two non-empty binary trees s and t, 
check whether tree t has exactly the same structure and node values with a subtree of s. 
A subtree of s is a tree consists of a node in s and all of this node's descendants. 
The tree s could also be considered as a subtree of itself.
*/

#include<iostream>
using namespace std;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if(t == nullptr) return true;
        if(s == nullptr) return false;
        if(isSameTree(s, t)) return true;
        return isSubtree(s->left, t) || isSubtree(s->right, t);
    }
    
    bool isSameTree(TreeNode* a, TreeNode* b) {
        if(a == nullptr && b == nullptr) return true;
        if(a == nullptr || b == nullptr) return false;
        return (a->val == b->val) && isSameTree(a->left, b->left) && isSameTree(a->right, b->right);
    }
};

int main()
{
    Solution s;

    return 0;
}