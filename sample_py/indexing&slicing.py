'''
Author: avert-win
Date: 2022-05-06 10:16:06
LastEditTime: 2022-10-09 16:02:57
FilePath: \ProgramDaily\sample_py\indexing&slicing.py
Description: 简介
LastEditors: avert-win
'''

from typing import List

#* 1. indexing

# It's not a list, but range, immutable.
r = range(5)            # r = [0,1,2,3,4,5].
print('\n', r[0]==r[-5])      # index can be [0,1,2,3,4], or [-5,-4,-3,-2,-1], without negtive zero.

# Assignment to an indexed position of immutable objects raise a `TypeError`.
# You can only catch the first exception in a single try block.
try:
    r[0] = 10
except TypeError as e:
    print('caught an error:', e)
print()

#* 1.1 Assignment by index copies data, but not recursively.
n = [['nested', 'list'], [1, ['nested nested', 'list']], 2, 3, 4]

n_0 = n[0]
n[0].append('new')
print(n_0==n)

n_1 = n[1]                  # origin is n[1]
n[1][1].append('new')       # change inside origin's component is visible to n_1.
print(n_1==n[1])            # true.

#* 2. slicing

s = 'Python'
print('\n'+s[:3])
print(s[-3:])
print(s[0:5:2])             # start, end, step.
print(s[10:])               #! out of range in slicing will not raise any exception!

#* 2.1 assignment by slicing copies data, but not recursively.
n = [0,1,2,3,4]
n_cp = n[:]
print(id(n)==id(n_cp))         # false
print(n==n_cp)                 # true

n.append('new')
print(n==n_cp)                 # false

n[0] = 'new'
print(n==n_cp)                 # false

print()

#* 2.2
n = [['nested', 'list'], 1, 2, 3, 4]
n_cp = n[:]                    # origin is n[:], instead of n. 
n.append('new')
print(n_cp==n)                 # false. change object n refers to, but not origin n[:].
n[0].append('new')             # change inside origin's component is visible to n_scp.
print(n_cp==n)                 # true.

#* 3. myth
# This sentence create 3 list, but 9 references.
test:List[List] = [[0]*3]*3
assert(len(test)==len(test[0])==3)
assert(id(test[0])==id(test[1]))