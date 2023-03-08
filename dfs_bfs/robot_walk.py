'''
Author: avert-win
Date: 2022-10-18 18:22:44
LastEditTime: 2022-10-18 18:35:16
FilePath: \ProgramDaily\dfs_bfs\robot_walk.py
Description: 机器人从(0, 0)出发，每次只能向左/右/上/下移动一格，并且不能移动到 行数的每位+列数的每位 > k 的位置，
    求该机器人可到达的格子总数有多少。给定地图大小为 (m,n)，给定k，满足条件 1 <= m,n <= 100,  0 <= k <= 20。
LastEditors: avert-win
'''
'''
思路: 使用深度优先搜索，从（0，0）开始: 
每深入一格就检查两个条件: i+j < k 和 not in visited；
    若该格满足条件，则计数加一、标记已探索，并尝试向四周搜索（越界在此控制）；若不满足条件则直接回退一格；
若回溯时才标记已探索，会导致原路返回！  回溯是由递归退出而来，并非函数调用，所以不需要满足任何条件。
'''

# sum 是一个内置函数名，不能使用作为变量名！
class Solution:
    '''
    检查行和列的个位数和十位数之和是否小于等于k（该格是否可到达）。
    '''
    def check(self, x, y, k):
        checksum = 0
        while(x):
            checksum += int(x % 10)     # python 使用动态类型，必须强制转换成int!
            x = int(x / 10)
        while(y):
            checksum += int(y % 10)
            y = int(y / 10)
        if(checksum > k):
            return False
        else:
            return True

    def movingCount(self, m: int, n: int, k: int) -> int:
        visited = set()
        self.__counter = 0

        def dfs(x0, y0):
            visited.add((x0,y0))        # 标记已搜索
            if(self.check(x0, y0, k)):      # 若可达则计数加一。不能在此进行未探索检查，因为上面刚刚标记本节点已探索！
                self.__counter += 1
            else:
                return None
            direction = ((0,1), (0,-1), (1,0), (-1,0))
            for (dx,dy) in direction:
                x = x0 + dx
                y = y0 + dy
                if x>=0 and x<m and y>=0 and y<n and not (x,y) in visited:      # 行号和列号都从零开始，因此不能等于m或n。
                    dfs(x,y)

        dfs(0,0)

        return self.__counter

solu = Solution()
print(solu.movingCount(1,2,1))