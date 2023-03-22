'''
Author: avert-win
Date: 2022-05-05 23:21:08
LastEditTime: 2022-05-06 11:16:33
FilePath: \ProgramDaily\pythonSample\name&reference.py
Description: Assignment, Shallow Copy, and Deep Copy.
LastEditors: avert-win
'''
'''
#* 1. In total, python's containers don't actually contain anything, but keep references
#*    to other objects. 
#     In this way, python's variables are just keys associated with a corresponding
#     object, and one object can have many keys(references). 

#* 2. 'garbage collection': when objects have no reference, they will be cleaned.

#* 3. Assignment never copies data, but creats association between object and name.
#     When needed, it creates association after creating name and object respectly.

#* 4. Changes in a value are visible through all of it's names(references).

#* 5. String, tuple and number are immutable, everything else is mutable. Mutable means 
#*    that the value can change __in place__, while immutable can not. 
#     When you think you are changing the value of immutable object, you are actually
#     making a new object from the old one.

#* 6. Python assigns mutable and immutable values in the same way.
#     All are given references.

#* 7. Python passes function arguments by assigning to them.

#* 8. Names have no type, values have no scope. Values can't be deleted manually.
'''

# We have two names below, which refer to one value.
x = 23
y = x

# Assignment doesn't copy data. Change in value are visible through all references.
a = [1,2,3]
b = a
a.append('new')
assert(a == b)
print(id(a)==id(b))

# Shallow copy constructs a new object from original object, but since what inside
# original object are references of some else objects, the new object still has the 
# same grandsons compared with the original object.
# That's why we call it 'shallow copy'.
import copy                         # There are three ways of shallow copy.
a = [[1,2],['compound', 'list']]
b = list(a)
c = a[:]
d = copy.copy(a)
assert(a == b == c == d)               # They have the same value.
print(id(a)==id(b)==id(c)==id(d))      # They are in different memory address.

# Change in b are visible to a, c, and d.
b[0].append('new')
assert(a == b == c == d)             

# Deep copy constructs new object, and then recursively construct all components found.
from copy import deepcopy
e = copy.deepcopy(a)
e[0].append('new')
print(a == e)                           # They are completely different now.


# tuple is immutable, but when there is a compound component inside it and this original
# compound object is mutable, then this tuple seems like a 'mutable' object.
t1 = (1,2,3,list(['compound', 'object', 'in', 'tuple']))
# t1[0]=0                               # aren't allowed to do that.
t1[3].append('new')                     # It's ok.
print(t1)

# strings
# In CPython, one instance is to be used for strings assignment by constant string.
s1 = 'string1'             
s2 = 'string1'
s1_cp = s1
print(id(s1)==id(s2)==id(s1_cp))

# https://nedbatchelder.com/text/names.html
# https://pythontutor.com/visualize.html#mode=display

# https://sharmapacific.in/assignment-vs-shallow-copy-vs-deep-copy-in-python/
# https://stackoverflow.com/questions/9755990/why-can-tuples-contain-mutable-items