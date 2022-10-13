'''
Author: avert-win
Date: 2022-06-28 19:44:57
LastEditTime: 2022-06-29 10:38:39
FilePath: \ProgramDaily\sample_py\sys_path\builtin_attributes.py
Description: 简介
LastEditors: avert-win
'''
'''
dir() and __dict__,
__path__ and __file__,
__doc__ and __annotations__.
top to down: any code will be taken as in main until a function is defined when this file is imported.
    when run it directly, all run top down.
'''
import cv2
from append_path import append_path     # append()
import os
append_path()
import list_array

print('cv2.__version__:', cv2.__version__)

def main(name:list[str]) -> int:
    '''
    annotation is not comment.
    annotation: {'name': list[str], 'return': <class 'int'>}
    '''
    print('\nyes, it is.\n')

print('this will never be print if is imported.')


if __name__ == '__main__':

    '''dir()
    no param: list of names in current local scope(including which imported). 
    class param: list of valid attributes.
    module param: list of all attributes(and classes).
    '''
    print('built-in attributes: ', dir(), '\n')
    print('attributes of list_array.myClass: ', dir(list_array.myClass), '\n')
    print('attributes of list_array: ', dir(list_array), '\n')

    '''__dict__'''
    print('__dict__ of list_array.myClass: ', list_array.myClass.__dict__, '\n')

    '''__annotations__, __doc__:
    annotations of return type, param and others.
    comment of module and functions.
    '''
    print(main.__annotations__)
    print(main.__doc__)

    # this is called when you build a class with 'class'. 
    # It can be reassigned.
    print(__build_class__)
    
    '''__file__, __path__, and os.getcwd()
    __file__ is location of the module,
    __path__ 
    os.getcwd() return where you launch the python script,
    '''
    print(__file__)
    print(os.getcwd())
    print(os.path.dirname(__file__))
    print(os.path.basename(__file__))
    print(os.path.abspath('abc'))