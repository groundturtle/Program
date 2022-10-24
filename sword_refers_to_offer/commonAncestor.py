'''
Author: avert-win
Date: 2022-10-22 21:55:57
LastEditTime: 2022-10-22 22:14:43
FilePath: \ProgramDaily\sword_refers_to_offer\commonAncestor.py
Description: 简介
LastEditors: avert-win
'''
from creatTree import *

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        m = max(p.val, q.val)
        n = min(p.val, q.val)
        curr = root
        while(True):
            if n <= curr.val and curr.val <= m:
                return curr
            elif curr.val < n:
                curr = curr.right
            elif curr.val > m:
                curr = curr.left

if __name__ == "__main__":
    solu = Solution()
    tree = [6,2,8,0,4,7,9,None,None,3,5]
    root = createTree(tree)
    print(solu.lowestCommonAncestor(root, root.left.right.left, root.left.right.right).val)