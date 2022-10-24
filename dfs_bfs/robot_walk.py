'''
Author: avert-win
Date: 2022-10-18 18:22:44
LastEditTime: 2022-10-18 18:35:16
FilePath: \ProgramDaily\dfs_bfs\robot_walk.py
Description: 简介
LastEditors: avert-win
'''
# sum 是一个内置函数名，不能使用作为变量名！
class Solution:
    def check(self, x, y, k):
        sum_ = 0
        while(x):
            sum_ += int(x % 10)     # python 使用动态类型，必须强制转换成int!
            x = x / 10
        while(y):
            sum_ += y % 10
            y = int(y / 10)
        if(sum_>k):
            return False
        else:
            return True

    def movingCount(self, m: int, n: int, k: int) -> int:
        visited = set()
        sum_ = 0

        def dfs(x0, y0):
            visited.add((x0,y0))        # 标记已搜索
            if(self.check(x0, y0, k)):
                nonlocal sum_
                sum_ += 1
            else:
                return None
            direction = ((0,1), (0,-1), (1,0), (-1,0))
            for (dx,dy) in direction:
                x = x0 + dx
                y = y0 + dy
                if x>=0 and x<=m and y>=0 and y<=m and not (x,y) in visited:
                    dfs(x,y)

        dfs(0,0)

        return sum_

solu = Solution()
print(solu.movingCount(2,3,1))