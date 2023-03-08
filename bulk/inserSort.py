'''
Author: avert-win
Date: 2022-10-25 16:38:39
LastEditTime: 2022-10-25 16:56:26
FilePath: \ProgramDaily\sword_refers_to_offer\inserSort.py
Description: 插入排序
LastEditors: avert-win
'''
from typing import *

def insert_sort(arr: List):
    n = len(arr)
    # 无序区间: [i:]
    for i in range(n):
        temp = arr[i]       # 提取这个数，稍后将前面的数依次后移填补
        # 有序区间: [:i]
        flag = False
        for j in range(i-1, -1, -1):
            if arr[j] > temp:
                arr[j+1] = arr[j]
            else:
                arr[j+1] = temp
                flag = True
                break
        # 如果有序区间内没有任何数小于temp，则应插入开头
        if not flag:
            arr[0] = temp
    return arr

if __name__ == "__main__":
    arr = [-1,-3,1,2,8,2,4,-2]
    print(insert_sort(arr))