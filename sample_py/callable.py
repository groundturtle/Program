'''
Author: avert-win
Date: 2022-05-02 12:04:14
LastEditTime: 2022-05-05 23:19:07
FilePath: \ProgramDaily\pythonSample\callable.py
Description: 简介
LastEditors: avert-win
'''

from typing import Callable, Type, Any

#* All making a class callable need is an implementation of method `__call__()`.
class call:
    def __init__(self) -> None:
        pass
    def __call__(self, args: Any, kwds: Any) -> Any:
        print(args, kwds)

# This function can be a parameter of other function.
def count_char(s1:str, s2:str):
    return len(s1)+len(s2)

# Take a function as an argument.
def function_call(func:Callable[[str, str], int], value:str):
    return func(value, value)

if __name__ == '__main__':

    mycall = call()          # A callable instance.
    mycall(3,'agb')       # Call.
    # Above two is equal to:
    call()('creat', 'call')

    print(function_call(count_char, 'calling count_char()'))