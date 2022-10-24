'''
Author: avert-win
Date: 2022-10-19 11:43:02
LastEditTime: 2022-10-21 15:25:48
FilePath: \ProgramDaily\dfs_bfs\pathSum.py
Description: 简介
LastEditors: avert-win
'''
from typing import *
import copy
import queue

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def pathSum(self, root: TreeNode, target: int) -> List[List[int]]:
        paths = []
        path = []

        def dfs(root: TreeNode, target: int):
            nonlocal path
            nonlocal paths
            path.append(root.val)               # 一到达就加入，退出时清空，都是无条件的，保证无错误
            if not root.right and not root.left:    # 是叶子节点
                if root.val == target:          # 值等于剩余的值
                    #! error! 以path为整体加入paths，则在后续修改path时paths也发生修改！
                    # paths.append(path)
                    paths.append(list(path[:]))
                    # path = []                 # 不应清空，因为两条路径可能共享同一部分上层节点
            if root.left:
                dfs(root.left, target-root.val)
            if root.right:
                dfs(root.right, target-root.val)
            path.pop(-1)                        # 务必退出，否则会无限叠加直至遍历完整棵树
        
        dfs(root, target)

        return paths

# 从前序遍历数组构造二叉树，只有在子节点左右不对称时数组中才会有None，否则下一个数字可能属于另一棵子树。
def createTree(tree: List):
    if not len(tree):
        return None
    q = queue.Queue()
    root = TreeNode(tree[0])
    q.put(root)
    i = 1
    while not q.empty() and i<len(tree):
        curr = q.get()
        if tree[i]:
            curr.left = TreeNode(tree[i])        
            q.put(curr.left)
        if tree[i+1]:
            curr.right = TreeNode(tree[i+1])
            q.put(curr.right)
        i += 2
    return root

def printTree(root: TreeNode):
    q = queue.Queue()
    q.put(root)
    # 第一层的个数必须特殊处理
    num = 1
    while not q.empty():
        pre_num = num
        num = 0
        print()
        for i in range(pre_num):
            curr = q.get()
            print(curr.val, end=" ")
            if curr.left:
                num += 1
                q.put(curr.left)
            if curr.right:
                q.put(curr.right)
                num += 1

if __name__ == "__main__":

    tree = [5,4,8,11,None,13,4,7,2,None,None,5,1]
    root = createTree(tree)
    printTree(root)
    solu = Solution()
    print(solu.pathSum(root, 22))

    str = "str"
    str.strip()
    str.split()


class Solution_2:
    def reverseWords(self, s: str) -> str:
        s = s.strip()
        words = s.split(' ')    # 如果有连续两个空格，出现一个空字符串（不含空格）

        words.reverse()

        news = ""
        for w in words:
            if w == ' ':
                continue
            news += w
            news += ' '

        news = news.strip()

        return news

def reverse(s):
    news = ""
    j = len(s)-1
    while(j>=0):
        news += s[j]
        j -= 1
    return news

print(reverse("abc"))

solu = Solution_2()
solu.reverseWords("a  b c ")