'''
Author: avert-win
Date: 2022-10-18 16:29:51
LastEditTime: 2022-10-18 17:50:33
FilePath: \ProgramDaily\dfs_bfs\word_in_board.py
Description: 深度优先搜索、回溯
        查询一个二维表格中是否含有某个单词，相邻字母之间只能是左右或上下相邻，不能是斜相邻。
LastEditors: avert-win
'''
# https://leetcode.cn/problems/ju-zhen-zhong-de-lu-jing-lcof/submissions/

# 深度优先搜索，采用递归方式，以每不同一格为起点都需要重新探索全部路径。
# 因来路不再进行搜索，每个点向三个方向搜索，因此每个起点时间复杂度O(l^3)，共有n*m个不同起点
# 使用布尔数组标记防止重复搜索，或使用set(tuple [, tuple[, ...]])，任何immutable的数据结构都是hashable的。
from typing import *
import numpy as np

""" 
    若不论当前是否满足要求都标记已探索，则不能绕回旁边，导致错误；应在确定满足要求后再标记
    回溯之后，若再次到达，必是中间经过了不同路线，此时必须允许再次探索！ 
"""
class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]

        def check(i: int, j: int, k: int) -> bool:
            if board[i][j] != word[k]:
                return False
            if k+1 == len(word):
                return True
            
            visited.add((i, j))
            result = False
            for di, dj in directions:
                newi, newj = i + di, j + dj
                if 0 <= newi < len(board) and 0 <= newj < len(board[0]):
                    if (newi, newj) not in visited:
                        # 回溯时从这里跳出，由于只将false改为true而不将true改为false，因此多余的搜索不会影响最后结果。
                        if check(newi, newj, k + 1):
                            result = True
                            break
            
            visited.remove((i, j))
            return result

        h, w = len(board), len(board[0])
        visited = set()
        for i in range(h):
            for j in range(w):
                if check(i, j, 0):
                    return True
        
        return False

board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]
word = "ABCCED"
solu = Solution()
# print(Solution.exist(Solution(), board, word))
print(solu.exist(board, word))