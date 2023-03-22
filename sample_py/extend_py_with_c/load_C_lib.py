'''
Author: avert-win
Date: 2022-06-29 19:10:01
LastEditTime: 2022-06-29 20:19:31
FilePath: /ProgramDaily/extend_py_with_c/load_C_lib.py
Description: Load C library using ctypes. 
    The only two data types you can pass between C program and Python Program 
    without any error are int and bytes(`b'hello'`).
LastEditors: avert-win
'''
import ctypes
import os

# provide absolute path to ld to link.
curdir = os.path.dirname(os.path.abspath(__file__))
lib = ctypes.CDLL(curdir+"/../bin/libextension.so")

c_sum = lib.sum
c_sum.argtypes = [ctypes.c_int, ctypes.c_int]
c_sum.restype = ctypes.c_int

# it will only print one character unless you pass a `b` before string quotation.
c_display = lib.display
c_display(b"YEAP!")

# ctypes define data types of C.
ret = ctypes.c_int()
ret = lib.sum(4, 3)
print(ret)