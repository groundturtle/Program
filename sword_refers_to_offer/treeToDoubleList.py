'''
Author: avert-win
Date: 2022-10-20 11:39:33
LastEditTime: 2022-10-20 11:40:34
FilePath: \ProgramDaily\sword_refers_to_offer\treeToDoubleList.py
Description: 将二叉搜索树改为双向链表，要求不创造新的节点。
LastEditors: avert-win
'''

# 法一：结构体存储节点值和节点指针，然后排序，最后生成链表。 空间复杂度O(n)，时间复杂度O(n*logn)，没有用到二叉搜索树的特性。
# 法二：中序遍历，得到的就是递增序列；维持两个指针pre和curr，令curr->left = pre; pre->right = curr; 最后处理头尾。 时间复杂度O(n)，空间复杂度O(d)，其中n为节点数量，d为最大深度，也即O(n)

# Definition for a Node.
class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

from typing import *

class Solution:
    def treeToDoublyList(self, root: 'Node') -> 'Node':

        pre = None
        head = None
        def midOrder(root: Node):
            nonlocal pre
            nonlocal head
             # 索引计数加一，不是新构造；pre将为最后一次进入递归函数时的root节点索引
            if root.left:
                midOrder(root.left)
            # 改当前的left和下一个的right，则第一个和最后一个需另外处理
            if pre:     # 除第一个节点，修改前一个节点的right指针
                pre.right = root
            else:       # 记录表头节点
                head = root
            root.left = pre
            pre = root
            if root.right:
                midOrder(root.right)

        if not root:
            return None

        midOrder(root)
        head.left = pre
        pre.right = head

        return head