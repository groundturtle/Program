'''
Author: avert-win
Date: 2022-10-24 20:41:54
LastEditTime: 2022-10-24 22:00:58
FilePath: \ProgramDaily\sword_refers_to_offer\myPow.py
Description: 求x的n次方，n最大可达2^31-1，可为负数。
LastEditors: avert-win
'''
# 运用递归树方法分析时间复杂度，见
# https://takeuforward.org/recursion/recursion-tree-method-for-solving-recurrence/#:~:text=1%20The%20recursion-tree%20method%20converts%20the%20recurrence%20into,use%20techniques%20for%20summations%20to%20solve%20the%20recurrence.
'''
这题需要采用递归分治法来解，但是画出递归深入的树可以发现，如果采用形如：
def recur(n):
    if n == 0:
        return 1
    if n == 1:
        return x
    return recur(n//2) * recur((n+1)//2))
的函数，则根本不能节省任何时间或空间（即便递归有优化算法并行，循环也可以自动展开）。
假设输入n，画出递归树，第二层有b个节点，第三层有b^3个节点，依次类推; 
    在每个节点内，时间消耗都为常数（n=0,n=1,或递归调用），因此时间负载度等于节点个数，即O(2^n)
也可根据递推式T(n) = 2*T(n/2) + 1，计算得时间复杂度O(2^n)，这样的方法比直接循环迭代还要慢!

一个很简单的解决办法是采用以下形式的实现：
def recur(n)
    if n == 0:
        return 1
    if n == 1:
        return x
    a = recur(n//2)
    return a*a
这样，在每一层内只有一个节点是实际存在的，其余节点棵用这个节点的返回值做一次性乘法来替代，
因此实际存在的节点总数为一条单链表，即树的深度。根据上面分析，树的深度为d，又有b^d = n，
因而有：
    d = log_b^n，即时间复杂度为O(logn)。

这种方法又称快速幂方法。

也可以使用迭代方式实现快速幂，因为
    n = i0*2^0 + i1*2^1 + i2*2^2 + ...
其中i0, i1, i2是n的二进制表示的第0，1，2位。所以
    x^n = x^(i0*2^0) * x^(i1*2^1) * ...
只需要在32次循环中在（从低到高）第i位为1的时候将x^(2^i)乘上结果即可。而由于i从0循环增长而来，
因此该数无需计算，只需不断相乘，存入另外一个变量中，只在需要时取出乘进结果里。
'''

class Solution:
    def myPow(self, x: float, n: int) -> float:

        # # 直接用while循环，得到的时间复杂度是O(n)，由于此处n巨大（可达2^31-1），这种方法显然不合理。
        # 考虑分治，x的n次方等于x的(a+b)次方，其中a = ceil(n/2)，b = floor(n/2)；
        # 按这种方法递归下去，返回值为两个递归调用的返回值之和。 
        def recur(exponent):
            if exponent == 0:
                return 1
            if exponent == 1:
                return x
            a = recur(exponent//2)
            return a*a if exponent%2==0 else a*a*x

        if n >= 0:
            return recur(n)
        else:
            return 1/recur(-n)