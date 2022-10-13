/*
 * @Author: avert-win
 * @Date: 2022-10-13 16:47:04
 * @LastEditTime: 2022-10-13 16:53:11
 * @FilePath: \ProgramDaily\dfs_bfs\levelOrderTree.cpp
 * @Description: 从上到下按层打印二叉树，一层从左到右、二层从右到左，按之字形顺序打印。
 *      只需要在广度优先搜索的基础上，给入队的元素加上层级信息即可。考虑使用pair等结构。
 *      若不使用额外信息，则对广度优先搜索稍加改造：每次从队列取出时，不是取出一个，而是取出全部。这样就每次都取出了一层的全部节点。
 * @LastEditors: avert-win
 */

// https://leetcode.cn/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof/?envType=study-plan&id=lcof&plan=lcof&plan_progress=ssfiecs

#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        // 当前从左到右，则下一层从右到左，按相同顺序存储，进入最终结果向量前再逆转。
        vector<vector<int>> levelOrder;
        bool leftToright = true;
        queue<TreeNode*> Q;
        if(root)
            Q.push(root);
        while(!Q.empty()){
            int n = Q.size();
            vector<int> nodes;
            TreeNode* curr;
            for(int i=0; i<n; i++){
                curr = Q.front();
                Q.pop();
                nodes.emplace_back(curr->val);
                if(curr->left)
                    Q.push(curr->left);
                if(curr->right)
                    Q.push(curr->right);
                }
            // 如果从右到左，则倒转，利用函数reverse
            if(!leftToright)
                reverse(nodes.begin(), nodes.end());
            levelOrder.emplace_back(nodes);
            leftToright = !leftToright;
        }
        return levelOrder;
    }
};