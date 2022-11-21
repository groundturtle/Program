/*
 * @Author: avert-win
 * @Date: 2022-11-17 17:00:57
 * @LastEditTime: 2022-11-17 18:50:16
 * @FilePath: \ProgramDaily\sword_refers_to_offer\verifyPostOrderSearchTree_v2.0.cpp
 * @Description: 给予一个数组，判断这个数组是否是（任意）某个二叉搜索树的后序遍历结果。
 *      此处使用单调栈方法。
 * @LastEditors: avert-win
 */

/**
 * @brief 单调栈方法：保持栈中的元素单调，并设置一个基准值，该值为已经遍历过整个右子树并进入左子树的最小元素值，后续遍历中没有任何元素应该大于此元素值。
 *              该节点为树中遍历过并第二次回到的最左节点，随着遍历向左进行，该值不断缩小。为保持单调，显然该值应出栈。
 * 后序遍历顺序为左、右、中（根），若将其逆序，则为根、右、左；
 * 将第一个元素入栈，设置limit为正无穷，然后序列中的其他元素逆序入栈;
 *      若大于limit，该树非二叉搜索树；
 *      若小于limit但大于栈顶，则该节点系某节点的左子节点，说明有新的可以作为基准的节点出现，需要找到该节点，以更新limit。
 * 此时循环出栈，直到弹出最后一个大于本元素的节点或栈空为止；栈空说明本节点处在左链上，否则找到的是最新的基准节点。
 * 每当某元素出栈就立即用其更新limit；因为最后一个出栈的元素已经开始向左遍历，而总的遍历顺序又为根、右、左，因此后续遍历的节点不可能大于次节点（一旦大于就可以判定这不是一棵BST）。
 */


#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {
        stack<int> goright;
        int limit = INT_MAX;
        int i = postorder.size();
        cout<<i<<endl;
        while(i>0){
            cout<<i<<endl;
            i--;
            // 当前节点大于历史最右节点，且非该节点的右子节点，则非二叉搜索树;
            if(postorder[i] > limit)    return false;       
            // 当前节点系上一节点的右子节点，或此前栈为空，可以直接入栈
            if(goright.empty() || postorder[i] > goright.top()){               
                goright.push(postorder[i]);
            }
            // 当前节点系某节点的左子节点: 寻找该节点并更新limit。
            else{       
                // 栈非空，且栈顶大于当前的，则出栈并更新limit。
                while(!goright.empty() && goright.top() > postorder[i]){
                    limit = goright.top();
                    goright.pop();
                }
                goright.push(postorder[i]);
            }
        }
        return true;
    }
};

int main(){
    vector<int> postorder = {4, 8, 6, 12, 16, 14, 10};
    Solution solu = Solution();
    solu.verifyPostorder(postorder);
}