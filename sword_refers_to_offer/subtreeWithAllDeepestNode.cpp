/*
 * @Author: avert-win
 * @Date: 2022-11-14 18:10:15
 * @LastEditTime: 2022-11-14 19:30:04
 * @FilePath: \ProgramDaily\sword_refers_to_offer\subtreeWithAllDeepestNode.cpp
 * @Description: 寻找一棵二叉树中包含全部最深节点的最小子树（全部最深节点为其子孙节点的最矮节点）。
 * @LastEditors: avert-win
 */

/**
 * @brief 代码采用了哈夫曼编码（法一），清晰易懂，但时间效率较低。
 * 
 */

#include<bits/stdc++.h>
using namespace std;

/* 
    法一：进行哈夫曼编码，编码的长度即节点的深度、节点的公共前缀即公共祖宗节点。
        每次到达叶节点就记录该节点编码，最后取出编码长度相同的叶节点，其最后一个公共节点即是所求节点。
    如此，若为完全二叉树，则空间复杂度最多可达到O(n)，与广度优先搜索和深度优先搜索的复杂度相同，因此无需考虑优化；
    时间复杂度：深度优先搜索O(n)，寻找最矮公共节点亦为O(n)，最终时间复杂度取决于编码的处理：
    使用哈希表存储最深节点编码；用一个额外的变量记录当前最大深度，若深度更新，则将哈希表清空重新填入。到最后哈希表中的全部编码长度都相等。
    由于最深节点最多可有n/2个，而此时编码长度可达logn，因此寻找节点的时间复杂度为O(n*logn)。
*/

/*
    法二：自顶向下，较高的子树一定包含所有最深节点，直到两子树高度相等时该节点即为所求。
        遍历一次，用哈希表记录每个节点以自身为根的子树的高度，
    然后递归比较两子树的高度，较高的子树含有全部最深节点，若两子树高度相同则该节点本身包含全部最深节点且为题目所求。
    若节点个数为n，则空间复杂度严格为O(n)，时间复杂度为两次深度优先搜索，亦为O(n)。
*/



struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    int deepest;
    int depth;
    unordered_set<string> huffmanCodes;
    // 编码由调用者传入，加入集合前不做处理（因无法知道自己属于左侧还是右侧）。
    void huffmanDFS(TreeNode* root, string code){
        depth++;
        if(depth > deepest){        // 清空集合、更新深度
            if(!huffmanCodes.empty())    huffmanCodes.clear();
            deepest = depth;
        }
        if(depth == deepest)        // 填入编码
            huffmanCodes.insert(code);
        if(root->left)
            huffmanDFS(root->left, code+'0');
        if(root->right)
            huffmanDFS(root->right, code+'1');
        depth--;
    }

public:

    Solution(){
        deepest = 0;
        depth = 0;      // 根节点深度为1
    }

    // 题设树非空
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        huffmanDFS(root, "0");        // 找出全部最深节点
        TreeNode* ret = root;
        string eg = *huffmanCodes.begin();
        for(int i=1; i<eg.length(); i++){
            char c = eg[i];
            for(auto& s : huffmanCodes){        // 判断i位编码是否全部相同
                if(s[i] != c){
                    return ret;            // 一旦出现不同，就可以结束搜索
                }
            }
            if(c == '0')    ret = ret->left;        // 如果全部相同，则更新返回节点指针
            else    ret = ret->right;
        }
        return ret;
    }
};