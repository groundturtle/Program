/**
 * @file validBST.cpp
 * @author avert-goose (avert-goose@hnu.edu.cn)
 * @brief 验证是否是有效二叉搜索树。节点值可为INT_MAX，INT_MIN，不相等。
 * @version 0.1
 * @date 2023-03-29
 */

/**
 * @brief 法一：分左右深入向下，左边是小则进入，不断进入，右边同理。
 * 一旦发现一个非递增/递减，则立即返回false。每个正常终止的函数都返回子函数返回值中假的那个。
 * 子节点与当前节点比较满足要求的，还要与上方逆向顶部节点再比较，满足条件才能返回为真。
 *      具体为，左子节点需大于沿链右上到顶之后的第一个父节点（拐弯后第一个节点），记为left_top
 *      传递方式，因顺序为向下，因此向右时当前节点即是之后节点的left_top；向左时，当前节点为之后节点的right_top
 * 
 * @brief 法二：中序遍历，二叉搜索树的中序遍历序列一定是递增的。
 */

#include<bits/stdc++.h>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:

    // 因为节点值可能达到int上限值，所以直接改用long long，避免无法有效初始化的问题。！
    bool sim_godeep(TreeNode* root, long long lower_bound, long long upper_bound){
        if(!root)
            return false;
        if(root->val <= lower_bound || root->val >= upper_bound)
            return false;
        return sim_godeep(root->left, lower_bound, root->val) && sim_godeep(root->right, root->val, upper_bound);
    }
    
    bool godeep(TreeNode* root, bool l_top, int left_top, bool r_top, int right_top){
        bool left = true, right = true;         // 初始化必须为真，以使叶节点返回为真
        if(root->left){         // 左子节点存在，且大于left_top（若left_top）未初始化则直接为true并原样传入。
            //! 注意三目运算符与`&&`运算符的运算顺序！
            if(root->val > root->left->val && (l_top ? root->left->val > left_top : true))           // 小于父节点且大于left_top
                left = godeep(root->left, l_top, left_top, true, root->val);
            else
                return false;
        }
        if(root->right){        // 右子节点存在，且小于right_top
            if(root->val < root->right->val && (r_top ? root->right->val < right_top : true))        // 大于父节点且小于right_top
                right = godeep(root->right, true, root->val, r_top, right_top);
            else
                return false;
        }
        return left && right;       // 都为真才返回真。
    }
public:
    bool isValidBST(TreeNode* root) {
        int left_top = INT_MIN;     
        int right_top = INT_MAX;
        return godeep(root, false, left_top, false, right_top);

        long long lower_bound = LONG_LONG_MIN;
        long long upper_bound = LONG_LONG_MAX;
        return sim_godeep(root, lower_bound, upper_bound);
    }
};

int main(){
    TreeNode* root = new TreeNode(INT_MIN);
    root->right = new TreeNode(2);
    root->left = new TreeNode(2);
    Solution solu;
    std::cout<<solu.isValidBST(root);
}