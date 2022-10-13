'''
Author: avert-win
Date: 2022-10-05 20:13:21
LastEditTime: 2022-10-05 20:58:40
FilePath: \ProgramDaily\bulk\SA_function.py
Description: 使用模拟退火算法，求解函数x^3 - 60x^2 -4x在定义域[0,100]内的最小值（理解为求内能最小值）。
LastEditors: avert-win
'''

from __future__ import division
import numpy as np
import matplotlib.pyplot as plt
import math

def aimFunction(x):
    y = x**3 - 60*x**2 - 4*x
    return y

x = [i/10 for i in range(1000)] # 0, 0.1, 0.2, 0.3
y = [0 for i in range(1000)]
for i in range(1000):
    y[i] = aimFunction(x[i])

plt.plot(x,y)

T = 1000    # 初始温度
Tmin = 10   # 最低温度
x = np.random.uniform(low=0, high=100)  # 随机初始解
k = 50

y = 0       # 最终解
t = 0       # 

# 双重循环，每次降温一个外循环，内循环在邻域内迭代k次寻找解
while T >= Tmin:
    for i in range(k):
        y = aimFunction(x)
        # 从邻域中随机选取新的解xNew
        xNew = x + np.random.uniform(low=-0.055, high=0.055) * T    
        if(0 <= xNew and xNew <= 100):
            yNew = aimFunction(xNew)
            # 如果新解导致的结果更好，采纳新解
            if yNew - y < 0:
                x = xNew
            # 如果新解不如旧解，按一定公式计算概率，决定是否采纳
            else:
                p = math.exp(-(yNew - y) / T)
                r = np.random.uniform(low=0, high=1)
                if r < p:
                    x = xNew
    t += 1
    # 降温函数，有多种选择，例如 T = kT
    T = 1000 / (1 + t)

print(x)
print(aimFunction(x))