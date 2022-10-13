'''
Author: avert-win
Date: 2022-04-29 20:52:19
LastEditTime: 2022-07-09 21:54:55
FilePath: \ProgramDaily\sample_py\scope.py
Description: 简介
'''

#% LEGB: local, enclosed, global, built-in. 依次进行寻找，前者可覆盖后者

#% parenthese, square brackets(brackets), curly brackets(curly), angle brackets

#! 1. 函数内赋值不改变参数，但列表、集合等的(局部)修改可以 
#? 哪些数据类型可以在函数内部使用哪些方式改变？
#Q: 实际上是引用的问题，只要是数据的局部，并且是非复制方式，就可以
#   在函数内改变；而整个变量名直接赋值则不可（因为引用计数，只是改变了引用）。
from attr import attr
from numpy import squeeze

def func1(arg1):
    print(f"\nget param arg1: {arg1}")
    arg1 = [1,2,3]
    print(f'change arg1 to: {arg1}')

arg1 = 'global arg1.'
func1(arg1)
print(f'exit function, arg1 is:   {arg1}')


#! 2. global关键字
#% This is wrong because declaring global variable is an entire statement.
# global arg2 = 'arg2 is also a string'

#% global 关键字是在函数内部使用的，声明函数内部的该变量来自全局变量，在此处声明没有用。
global arg2
arg2 = 'arg2 in global'

def func2():
    #%如此声明使用的变量来自全局scope.
    global arg2
    # arg2 = 'arg2 in local'
    print(f'In func2, arg2:   {arg2}')
    arg2 = [1,2,3]
    print(f'change arg2 in function:   {arg2}')

func2()
print(f'global arg2 is: {arg2}')


#! 3. nonlocal关键字和闭包函数
# 在嵌套函数中定义的，既非本地，又非全局或内建，因此称为nonlocal.
# 注意python的解释器搜索顺序是本地、非本地、全局、内建。
# 和global一样，
# nonlocal关键字的作用是标识此地符号非本地符号，因此可以重新定义或者修改而不影响本地变量。

def func3(exp):
    def power(base):
        return base**exp
    return power   # without parentheses, return a function(address and type)

# declare an (enclosed) function by using an outer function.
square = func3(2)
cube = func3(3)
print(square(10))
print(cube(10))

#% LEGB之外：Comprehensions, Exception blocks, Classes and instances.

#! 1. Comprehension Variables Scope, 推导式范围，通常用中括号或大括号包围起来

[item for item in range(5)]
# item is not accessible after list comprehension.
# print(item)

for item in range(5):
    None
# but you can get the last item(value) after for loop.
print(item)


#! 2. Exception Variables Scope, you can assign global variables there, but
#! variables there cannot being accessed outside.

list1 = [1,2,3]

ex = None
try:
    list1[3]
except IndexError as error:
    ex = error
    print(error)

# NameError: name 'error' is not defined.
# print(error)

# OK: you can assign a global variable in exception scope.
print(ex)

#! 3. Class and Instance Attributs Scope

#% 1. class不为method创建enclosed scope，在类内必须通过self传参来修改类的属性、调用类的方法；
#% 2. class具有共同的一些属性，同时每个实例还可以为自己增加属性，包括数据和方法。

class cls:
    attr = 100
    def cls_func(self):
        self.attr = 200
        return self.attr
        # 不加self直接访问的是function attrib而非类的属性
        # return attr

# 不用实例化也能直接访问静态属性
print(cls.attr)

# 函数需要参数self，因此不实例化不能访问
# print(cls.cls_func())

# 这种方法是命了别名而不是初始化！
# obj = cls
obj = cls()
print(obj.cls_func())

# 给类的实例增加一个新(数据)属性
obj.insnewattr = 3
print(obj.insnewattr)

# 给类的实例增加一个方法，不要加括号，如果加了括号就是将返回值作为属性
cls.newattr = func1
obj.newattr()

#% 可以给类或者类的实例动态增加属性(包括数据和方法)，
#% 給实例增加的仅限于该实例使用，给类增加的往后的类都能使用。

obj2 = cls()

# 访问给其它实例增加的属性，报错
# print(obj2.insnewattr)

# 访问给类增加的属性，正常执行
obj2.newattr()