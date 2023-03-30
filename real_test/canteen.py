
# & 食堂每张桌允许坐两人，男员工优先选择有人餐桌，女员工优先选择无人餐桌，
# & 男女员工都会优先选择同等条件的左边餐桌；
# & 已知有n张桌及其就坐情况，另有m人在等待进入并知道每个人性别，
# & 求预测排队的人依次选择的餐桌座号，输入保证每个人都有座位可坐。

# & 进阶要求: 时间复杂度O(nlogn)，空间复杂度O(n)；

import heapq
import sys
from typing import List, AnyStr

'''
输入共t组，每组调用一次；每组输入四行：
第一行一个整数n，表示桌子数；
第二行一个字符串，表示每张桌子上坐的人数；
第二行一个整数表示排队人数；
第三行一个m位字符串，'M', 'F'表示性别
'''
def getInput():

    n = int(sys.stdin.readline())       # sys.stdin/out 批量读取，更快
    sit = sys.stdin.readline()
    m = int(sys.stdin.readline())
    sex = sys.stdin.readline()

    zeroList = []
    oneList = []
    for i, num in enumerate(sit):
        if num == '0':
            zeroList.append(i+1)
        elif num == '1':
            oneList.append(i+1)
    heapq.heapify(zeroList)         # O(n)
    heapq.heapify(oneList)

    return sex, zeroList, oneList

def run(sex: AnyStr, zeroList: List, oneList: List):
    '''
    以排队人为基础，进行性别判断，然后取出零人或一人桌分配，并更新桌子（删除或转移）；
    排队人m，堆操作log(k)，k小于总的桌子数n，m小于2*n，最终时间复杂度O(nlogn)
    
    Arguments:
        sex {_type_} -- _description_
        zeroList {_type_} -- _description_
        oneList {_type_} -- _description_
    '''
    result = []
    for per in sex:
        if per == 'M':      # 男的，找1
            if len(oneList):
                result.append(oneList[0])
                # sys.stdout.write(str(oneList[0])+'\n')
                heapq.heappop(oneList)
            else:
                result.append(zeroList[0])
                # sys.stdout.write(str(zeroList[0])+'\n')
                heapq.heappush(oneList, zeroList[0])
                heapq.heappop(zeroList)

        elif per == 'F':
            if len(zeroList):
                result.append(zeroList[0])
                # sys.stdout.write(str(zeroList[0])+'\n')
                heapq.heappush(oneList, zeroList[0])
                heapq.heappop(zeroList)
            else:
                result.append(oneList[0])
                # sys.stdout.write(str(oneList[0])+'\n')
                heapq.heappop(oneList)

    return result

if __name__ == "__main__":

    # import time
    # start_time = time.perf_counter()  # 获取开始时间

    t = int(input())
    for i in range(t):
        sex, zeroList, oneList = getInput()
        result = run(sex, zeroList, oneList)
        sys.stdout.write('\n'.join(result))

    
    # end_time = time.perf_counter()  # 获取结束时间
    # elapsed_time = (end_time - start_time) * 1000  # 计算程序运行时间，单位为ms

    # print("程序运行时间：{:.2f}ms".format(elapsed_time))