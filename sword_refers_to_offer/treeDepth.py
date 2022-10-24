'''
Author: avert-win
Date: 2022-10-21 15:27:47
LastEditTime: 2022-10-22 21:33:38
FilePath: \ProgramDaily\sword_refers_to_offer\treeDepth.py
Description: 记录树的最大深度。
LastEditors: avert-win
'''
from creatTree import *

class Solution:
    def maxDepth(self, root: TreeNode) -> int:

        self. result = 0
        self.k = 0

        def dfs(root: TreeNode):
            if not root:
                return 
            self.k += 1
            if root.left:
                dfs(root.left)
            if root.right:
                dfs(root.right)
            self.result = max(self.k, self.result)
            self.k -= 1

        dfs(root)

        return self.result

if __name__ == "__main__":

    tree = [3,9,20,None,None,15,7]
    root = createTree(tree)

    solu = Solution()
    print(solu.maxDepth(root))