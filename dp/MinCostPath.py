'''
Author: avert-win
Date: 2022-04-29 15:03:00
LastEditTime: 2022-04-29 16:18:35
FilePath: \ProgramDaily\dp\MinCostPath.py
Description: 
    给定方格，可以向右、下和右下三个方向行走，每个方格有一个正整数代价，
    求从左上顶点走到右下顶点的最小代价。计算代价包括起点和终点。
'''

'''
1. 分解子问题：到最后一格的最小代价等于到左、上、左上三格的最小代价与本格代价之和。
2. 状态表达式+状态转移方程式：dp[i][j] = min(dp[i-1][j], dp[i-1][j-1], dp[i][j-1]).
'''

# import numpy as np

n = int(input())
dp = [[0]*n]*n  

for i in range(n):
    nums = input()
    nums = nums.split()
    for j in range(n):
        dp[i][j] = int(nums[j])

print("dp input", dp)
dp[1][2] = 3
print('dp after', dp)

# # dp_np = np.array()
# # print(dp_np)

# n = int(input())
nums = [[0]*n]*n

for i in range(n):
    line = input().split()
    nums[i] = [int(num) for num in line]

print(nums)
nums[1][2] = -2
print(nums)