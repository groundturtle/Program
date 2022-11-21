/*
 * @Author: avert-win
 * @Date: 2022-10-28 15:39:40
 * @LastEditTime: 2022-11-17 16:56:08
 * @FilePath: \ProgramDaily\sword_refers_to_offer\verifyPostOrderSearchTree.cpp
 * @Description: 给予一个数组，判断这个数组是否是（任意）某个二叉搜索树的后序遍历结果。
 *  此处使用递归分治方法：将序列分到各棵子树上，递归处理。
 *  使用单调栈方法见目录下文件 verifyPostOrderSearchTree_v2.0.cpp，时间复杂度仅为O(n)。
 * @LastEditors: avert-win
 */
#include<bits/stdc++.h>
using namespace std;

// 将数组倒过来，即是中、右、左顺序的遍历结果；
// 不符合一棵树的情况：左子树存在元素比中间大或右子树存在元素比中间小。题目保证数组中没有相等的数。
/*
* 划分子树：第一个为树根，往左更大的为右子树，剩余为左子树；
* 递归划分和检验：树根的左子树和右子树可以为空，但需要满足左小右大的约束。。
    检验是否满足约束的方法是，将往上第一个向左和向右连接的祖宗节点分别作为参数传入，进行比较限制。
    首先预定义，然后每次对于左子树，更新最近的右连接节点为当前节点；右子树更新最近的左连接节点为当前节点；

* 更简单的方法是，直接在划分子树过程中将全部子节点与根节点对比，不必传入上一个要求更大/更小节点。
*/
// 当树退化为右向链表时，时间复杂度O(n^2)，空间复杂度O(n)。
class Solution {
    bool result;
    // 递归检验，左闭右开
    void recurStruct(vector<int>& postorder, int start, int end, int firstleft, int firstright){
        if(start >= end)  return;               // 空树在此处理，构建子树时不再管
        int root = postorder[end-1];
        // 进行限制：大于顶上
        if(root < firstleft || root > firstright){
            result = false;
            return;
        }
        int rightstart = end-1;
        // 由于此处，当树退化为右向链表时，时间复杂度O(n^2)，空间复杂度O(n)。
        for(int i=end-2; i>= start; i--){
            if(postorder[i] >= root){
                rightstart = i;
            }
            else break;
        }
        recurStruct(postorder, rightstart, end-1, root, firstright);
        recurStruct(postorder, start, rightstart, firstleft, root);
    }
public:
    bool verifyPostorder(vector<int>& postorder) {
        result = true;              // 假设为真，递归构建过程检验
        recurStruct(postorder, 0, postorder.size(), INT_MIN, INT_MAX);
        return result;
    }
};