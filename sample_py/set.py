'''
Author: avert-win
Date: 2022-04-28 01:04:22
LastEditTime: 2022-05-07 21:43:47
FilePath: \ProgramDaily\pythonSample\set.py
Description: 
'''

#? Initialize:

# empty set: small brackets.
set1 = set()
print(f"set1: {set1}")

# any hashable items.
set2 = {2, 3, 4, "3ab"}
print(f"set2: {set2}")

# string:  every char.
set3 = set("hello")
print(f"set3: {set3}")

# list: every item.
set4 = set([2,4,5,7])
print(f"set4: {set4}")

# tuple: every item
set5 = set((3,2,4))
print(f"set5: {set5}")

# Dict: only keys.
set6 = set({"name": "ywh", "IQ": "nan"})
print(f"set6: {set6}")

#? operation
setchar = set("hello")
setchar.add('b')
print(setchar)

# `in` to check whether an element is in set. It has O(1) time complexity.
s = set(['a', 'set'])   
print('a' in s)         

#! fatal:
myset = set     #! It is type alias!
setchar = myset("hello")
print(setchar)