'''
Author: avert-win
Date: 2022-10-19 11:43:02
LastEditTime: 2022-10-25 22:00:13
FilePath: \ProgramDaily\dfs_bfs\pathSum.py
Description: 找出给定二叉树中的某条路径，其上节点的值的总和为给定值。已知满足条件的路径必定存在，有多条时返回任意一条。
LastEditors: avert-win
'''
import sys
sys.path.append('E:\\ProgramDaily')
from typing import *
from sword_refers_to_offer.creatTree import *
import queue

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