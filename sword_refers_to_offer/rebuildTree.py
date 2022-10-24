'''
Author: avert-win
Date: 2022-10-24 13:32:19
LastEditTime: 2022-10-24 18:17:05
FilePath: \ProgramDaily\sword_refers_to_offer\rebuildTree.py
Description: 从前序遍历和中序遍历序列中重构二叉树。
        若在递归中，每次都重新搜寻中序序列中的根节点，则因为大量重复搜寻过程的存在导致十分慢；
        提前构造哈希表解决问题，但这就要求调用递归函数时不能将列表切片传入（索引变化），而只能传递索引。
LastEditors: avert-win
'''
from typing import *
from creatTree import *

# 代码中列表的全部区间采用左闭右开模式，本体的主要难点是确定左右子树的边界在原序列中的索引，多用asser()
# 本题至少耗时四小时！！
class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        
        def recur(i, j, in_i, in_j):
            # print(f"i, j, in_i, in_j: {i, j, in_i, in_j}")
            if j - i < 1:
                return None
            if j - i == 1:
                return TreeNode(preorder[i])
            root = TreeNode(preorder[i])        # 构建树根
            in_root = dic[preorder[i]]          # 中序树根索引
            left_size = in_root - in_i          # 左子树长度
            right_size = in_j - in_root - 1       # 右子树长度    # wrong: 1

            # print(f"left_size: {left_size}")
            # 左子树边界
            left_i = i + 1              # 前序左子树左边界比原来+1，中序左边界相同；
            left_j = left_i + left_size
            left_in_i = in_i
            left_in_j = in_root
            # 右子树边界
            right_i = left_j     
            right_j = j                 # 右子树右边界与原来相同，左边界为左子树右边界+1（前序，树根不在中间）
            right_in_i = in_root + 1
            right_in_j = in_j

            root.left = recur(left_i, left_j, left_in_i, left_in_j)
            root.right = recur(right_i, right_j, right_in_i, right_in_j)

            return root

        dic, preorder = {}, preorder
        for i in range(len(inorder)):
            dic[inorder[i]] = i
        n = len(preorder)
        return recur(0, n, 0, n)

if __name__ == "__main__":

    solu = Solution()
    preorder = [3,9,20,15,7]
    inOrder = [9,3,15,20,7]
    root = solu.buildTree(preorder, inOrder)
    while(root):
        print(root.val)
        root = root.left