'''
Author: avert-win
Date: 2022-04-28 21:41:32
LastEditTime: 2022-04-29 00:07:34
FilePath: \ProgramDaily\dp\digital_game.py
Description: 
'''

from sys import maxunicode
from numpy import dtype
from pyrsistent import b


n_m = input()

n, m = n_m.split()
nums = []

i = 0
while i<int(n):
    nums.append(int(input()))
    i += 1

# for num in nums:
    # nums.append(num for num in nums)
#% extend() to concat two lists.
nums.extend(nums)

global a
global sum
global f
global d
global maxn
global minn
maxn = 0
minn = 1e8
a = [[]]
sum = [[]]
f = [[]]
d = [[]]


def dp(n, m, p):
    for i in range(1+p, n+p+1):
        for j in range(i, n+p+1):
            sum[i][j] = sum[i][j-1] + a[j]
    for i in range(1+p, n+p+1):
        for j in range(i, n+p+1):
            sum[i][j] %= 10
            if sum[i][j] < 0:
                sum[i][j] += 10
    for i in range(i, n+p+1):
        for j in range(1, m+1):
            f[i][j]=1e8
            d[i][j]=0
    for i in range(1+p, n+p+1):
        f[i][0] = sum[1+p][i]
        d[i][0] = sum[1+p][i]
    for i in range(1, m+1):
        for j in range(j+p+1, n+p+1):
            for k in range(1+p, i):
                f[i][j] = min(f[i][j], f[k][j-1]*sum[k+1][i])
                d[i][j] = max(d[k][j-1]*sum[k+1][i])
    maxn = max(maxn, d[n+p][m-1])
    minn = min(minn, f[n+p][m-1])

