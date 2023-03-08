'''
Author: avert-win
Date: 2022-05-07 21:28:06
LastEditTime: 2022-05-08 00:46:53
FilePath: \ProgramDaily\MinimumGeneticMutation.py
Description: 有八位基因，每次只许突变一次，给出基因池和初始基因、目标基因，求初始基因经基因池突变到目标基因的最短路径长度。
             目标基因保证在基因池内，突变路径必须在基因池内；若不存在这种路径，则路径长度为-1.
LastEditors: avert-win
'''

'''
思路：
将基因池送入集合，从初始基因开始一步一步到基因池中寻找路径长度为1的突变，将找到的基因划出基因池，
    转而送入下一次寻找过程的起始基因池中。重复寻找过程直至找到目标基因或以下两种情况：
    1. 基因池为空，则无路径，返回负一；但因实际上目标基因也在基因池里，所以这种情况不可能发生；
    2. 基因池还有基因，但每次寻找路径都不能找到，导致进入死循环。
在实际实现时，出现了问题：
    1. 在同一步长内使用不同基因`s`作为初始基因`start`进行搜寻时，没有每次清空找到的步长为1的可突变目的基因集合`morestep`，导致在完成搜索后重复
        删除同一元素（上次在morestep内的遗留），引起报错。
    2.  在更正第一步的错误之后，对初始基因池的更新又出现了错误：每次只将基因池内的最后一个初始基因所找到的突变基因池morestep作为下次的初始基因池，
        导致许多基因被从基因池_bank划分了出去，却没有进入下次寻找的初始基因池start。
        正确的做法应当是用额外的一个集合(backup)，将同一步长内的全部基因用union()存储起来，等待下次搜寻时作为初始基因，然后才清除。

#!  3. 该按照顺序的程序，不要考虑逆序，否则可能在循环和递归时出现问题！

'''

# https://leetcode-cn.com/problems/minimum-genetic-mutation/submissions/

from typing import *

class Solution:
    
    def findonestep(self, start, morestep, bankset):
        for s in bankset:
            num = 0
            for i in range(8):
                if s[i] != start[i]:
                    num += 1
            if num == 1:
                morestep.add(s)
                # bankset.remove(s)         #! Set changed size during iteration.
        if len(morestep) == 0:
            return -1
        for s in morestep:
            bankset.remove(s)
        return 0

    def minMutation(self, start: str, end: str, bank: List[str]) -> int:
        
        # turn list to set to speed up operations.
        self.end = end
        _bank = set()
        for s in bank:
            _bank.add(s)

        if end not in _bank:
            return -1
        if start in _bank:
            _bank.remove(start)

        step = 1
        lessstep = set()
        backup = set()

        # 以基因池lessstep内的基因作为初始基因开始搜寻，找到步长为1的目的基因作为下一次的初始基因。
        while(len(_bank)!=0):
            lessstep = backup
            backup = set()              # backup存储本轮内找到的目的基因，突变到这些基因的步长都相同

            if step == 1:
                lessstep.add(start)
            # If found a step to end, return, else increase step and find again.
            morestep = set()
            for s in lessstep:
                # backup = backup.union(morestep)
                morestep = set()                    # morestep存储本个基因作为初始基因找到的目的基因，为了防止重复，每次都要更新。
                self.findonestep(s, morestep, _bank)
                if end in morestep:
                    return step
                backup = backup.union(morestep)     # 寻找完成后，加入本轮的目的基因池。
            if len(backup) == 0:
                return -1
            step += 1

        return -1
        
solu = Solution()
print(solu.minMutation("AACCTTGG","AATTCCGG",["AATTCCGG","AACCTGGG","AACCCCGG","AACCTACC"]))