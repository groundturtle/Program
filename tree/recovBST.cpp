/**
 * @file recovBST.cpp
 * @author avert-goose (avert-goose@hnu.edu.cn)
 * @brief 给予一棵树，已知其中有一对节点交换位置后该树为二叉树，不改变结构将其恢复。
 * @version 0.1
 * @date 2023-03-29
 */

/**
  * @brief 思路：进行中序遍历，找到不符合规矩的两个点，记录其指针用于交换。
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

class Solution {
    vector<TreeNode*> vec;

    void inorder(TreeNode* root){
        if(!root)   
            return;
        inorder(root->left);
        vec.push_back(root);
        inorder(root->right);
    }

    void myswap(){
        int out[2];
        int j = 0;
        for(int i=0; i<vec.size(); i++){
            if(vec[i]->val > vec[i+1]->val){
                out[0] = i;
                break;
            }
        }
        for(int i=vec.size()-1; i>0; i--){
            if(vec[i]->val < vec[i-1]->val){
                out[1] = i;
                break;
            }
        }
        std::swap(vec[out[0]]->val, vec[out[1]]->val);
    }

public:
    void recoverTree(TreeNode* root) {
        inorder(root);
        myswap();
    }
};