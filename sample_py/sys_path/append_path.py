'''
Author: avert-win
Date: 2022-06-29 09:57:29
LastEditTime: 2022-06-29 10:40:53
FilePath: \ProgramDaily\sample_py\sys_path\append_path.py
Description: 简介
LastEditors: avert-win
'''
def append_path():
    import os
    import sys
    curdir = os.path.dirname(__file__)      # directory of current file.
    curdir = os.path.abspath(curdir)        # absolute path.
    sys.path.append(os.path.dirname(curdir))