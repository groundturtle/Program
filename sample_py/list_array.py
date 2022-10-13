'''
Author: avert-win
Date: 2022-04-29 15:37:27
LastEditTime: 2022-06-29 09:06:02
FilePath: \ProgramDaily\sample_py\list_array.py
Description: 简介
'''

# numpy array:

import numpy as np

a = np.zeros(3, np.int16)
b = np.zeros((3,3), np.float16)
b[2][1] = 3
print(a)
print(b)


# python list

a = []
b = [0.33]*5
c = list(range(1,5))
c.remove(2)
print(a)
print(b)
print(c)

class myClass():
    def __init__(self) -> None:
        pass