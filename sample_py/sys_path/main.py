'''
Author: avert-win
Date: 2022-06-29 16:09:05
LastEditTime: 2022-06-29 16:14:45
FilePath: \ProgramDaily\sample_py\sys_path\main.py
Description: 简介
LastEditors: avert-win
'''
from append_path import append_path
# append sys.path
append_path()

# when import a module from package, __init__.py there will be run.
import package.mod1