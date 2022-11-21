'''
Author: avert-win
Date: 2022-10-24 22:05:42
LastEditTime: 2022-10-25 21:39:55
FilePath: \ProgramDaily\sword_refers_to_offer\quickSort.py
Description: 递归方法实现快速排序。
    优化：
        1. 从左、中、右三者（或更多）中选取中间值作为基准；
        2. 在递归到数组长度较小时，截断递归，采用插入排序；
        3. 将与基准值相等的聚集到基准周边，不进入下次递归；
LastEditors: avert-win
'''
from typing import *

def partition(arr,low,high): 
    i = low        # 最小元素索引
    pivot = arr[high]     # 以最右边的数为基准
  
    for j in range(low , high): 
        # 当前元素小于或等于pivot，则将其与前面的数调换，详解见c++实现版本的注释。
        # if arr[j] <= pivot: 
        if arr[j] <= pivot: 
            arr[i],arr[j] = arr[j],arr[i] 
            i += 1 
  
    arr[i],arr[high] = arr[high],arr[i] 
    return i
  
# 快速排序函数
def quickSort(arr: List, low: int, high: int): 
    if low < high: 
        pi = partition(arr, low, high) 
        quickSort(arr, low, pi-1) 
        quickSort(arr, pi+1, high) 

arr = [-2, 10, 7, 8, 9, 1, 5] 
n = len(arr) 
quickSort(arr,0,n-1) 
print(arr)