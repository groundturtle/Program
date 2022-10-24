'''
Author: avert-win
Date: 2022-10-21 15:26:13
LastEditTime: 2022-10-22 22:08:30
FilePath: \ProgramDaily\sword_refers_to_offer\creatTree.py
Description: 简介
LastEditors: avert-win
'''
import queue
from typing import List

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

# 从前序遍历数组构造二叉树.
def createTree(tree: List):
    if not len(tree):
        return None
    q = queue.Queue()
    root = TreeNode(tree[0])
    q.put(root)
    i = 1
    while not q.empty() and i<len(tree):
        curr = q.get()
        if tree[i]==0 or tree[i]:             # 节点值可能为0！无法区分None和数字0！
            curr.left = TreeNode(tree[i])        
            q.put(curr.left)
        if tree[i+1]==0 or tree[i+1]:
            curr.right = TreeNode(tree[i+1])
            q.put(curr.right)
        i += 2
    return root