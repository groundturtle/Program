'''
Author: avert-win
Date: 2022-04-27 22:39:39
LastEditTime: 2022-04-28 21:26:51
FilePath: \ProgramDaily\dfs_bfs\ocean_bfs.py
Description: Pacific Atlantic Water Flow in leetcode.
'''

# a:list[list[int]] = [[3], [3,3]]
# print(len(a))

from collections import deque
import queue
from unittest import result

class Solution:

    def __init__(self) -> None:
        None

    #! list is unhashable, so that it cann't be a member of set or dict!
    # def bfs(self, start:list[int], visited:set):
    def bfs(self, start:tuple[int], visited:set):
        #! This turn list to queue, instead of push an item to queue!
        # searching = deque(start)
        searching = deque()
        searching.append(start)
        visited.add(start)
        while searching:
            (x0, y0) = searching.popleft()
            #! fatal error!
            # for (x,y) in ( (x0-1,y0-1), (x0-1,y0+1), (x0+1,y0+1), (x0+1,y0-1) ):
            for (x,y) in ( (x0,y0-1), (x0,y0+1), (x0+1,y0), (x0-1,y0) ):
                if x>=0 and y>=0 and x<self.m and y<self.n and (x,y) not in visited:
                    if self.heights[x][y] >= self.heights[x0][y0]:
                        searching.append((x,y))
                        visited.add((x,y))
                        


    def pacificAtlantic(self, heights: list[list[int]]) -> list[list[int]]:
        self.heights = heights
        self.m, self.n = len(heights), len(heights[0])
        pavisited:set = set()
        alvisited:set = set()
        for i in range(self.m):
            self.bfs((i,0), pavisited)
        for i in range(self.n):
            self.bfs((0,i), pavisited)
        for i in range(self.m):
            self.bfs((i,self.n-1), alvisited)
        for i in range(self.n):
            self.bfs((self.m-1,i), alvisited)
        result = []
        for i in range(self.m):
            for j in range(self.n):
                if (i,j) in pavisited and (i,j) in alvisited:
                    result.append([i,j])
        
        return result

solu = Solution()
heights = [[3,2],[2,2],[3,3]]
result = solu.pacificAtlantic(heights)
print(result)

#! type alias!
seta = set
# seta:set = {1, 2}
disset = set("dis")
seta.add(disset)
seta.add(3)
seta.add(4)

def changeSet(setb):
    setb.add(5)

print(seta)
changeSet(seta)
print(seta)