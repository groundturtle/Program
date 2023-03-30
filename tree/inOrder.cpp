/**
 * @file inOrder.cpp
 * @author avert-goose (avert-goose@hnu.edu.cn)
 * @brief 二叉树的中序遍历
 * @version 0.1
 * @date 2023-03-29
 */
#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void inorder(TreeNode* root, vector<int>& ret){
    if(!root) 
        return;
    inorder(root->left, ret);
    ret.push_back(root->val);       // 中序遍历，先左后本最后右。
    inorder(root->right, ret);
    return;
}