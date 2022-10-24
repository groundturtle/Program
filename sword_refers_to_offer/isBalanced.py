'''
Author: avert-win
Date: 2022-10-22 21:34:27
LastEditTime: 2022-10-22 21:39:56
FilePath: \ProgramDaily\sword_refers_to_offer\isBalanced.py
Description: 判断一棵二叉树是否为平衡二叉树。
    若任意节点的两棵子树高度相差不超过一，则该树为平衡二叉树
    （不对不同父节点的子树高度作比较。）
LastEditors: avert-win
'''
from creatTree import *
""" 
每棵子树都需要一个单独的变量来记录并返回深度，需要传参，过于累赘。
若采用计算高度的方法：则恰好符合递归从底部开始逐层向上的特性，只需要在每一个递归栈内对子树高度差做一个判断即可。
从空节点开始，返回值为0，此后每次返回加1，无需在各个递归调用栈之间传递共享变量（只一次性使用返回值） 
"""

class Solution:
    def isBalanced(self, root: TreeNode) -> bool:

        self.result = True

        def depth(root: TreeNode):
            if not self.result:
                return 0
            if not root:                # 空节点返回0
                return 0
            left_depth = depth(root.left)
            right_depth = depth(root.right)
            if abs(right_depth - left_depth) > 1:       # 对比左右两棵子树高度
                self.result = False
                return 0
            # 以本节点（也许为叶节点）为根的树平衡，则将结果返回给父节点
            return 1 + max(left_depth, right_depth)

        depth(root)
        return self.result