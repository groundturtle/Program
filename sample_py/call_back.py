'''
Author: avert-ubt
Date: 2022-05-02 19:01:20
LastEditTime: 2022-05-02 19:08:52
LastEditors: avert-ubt
Description: 
FilePath: /pythonSample/call_back.py
'''
'''
* A callback is a function that is passed as an argument to an other function. 
'''

from typing import *

def func1(s:str, s2:str):
    print(s.count(s2))
    
def call(s:str):
    s2:str = s[0]
    func1(s,s2)
    
call('abcaazz')