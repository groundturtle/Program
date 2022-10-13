/*
 * @Author: avert-win
 * @Date: 2022-04-22 22:51:10
 * @LastEditTime: 2022-09-23 16:34:13
 * @Description: 给出数组，求删除最少数目的位置连续的元素，使剩余元素严格单调递增。
 */
#include<vector>
#include<iostream>
#include<math.h>

/**
 * @brief 既然要删除一个位置连续的子数组，使得剩余部分递增，那么隐含条件就是数组的不严格单调递增部分只有一个！
 *      这个部分的元素数目最少为0，最多为整个数组，但一定连续，因此一定在中间（可能包含头尾）
 * 最后的结果可能有三种：保留左边，保留右边，保留左边和右边的衔接部分
 * 1. 左边窗口从一开始扩大，直到不再单调; 记录删除的（右边部分的）数量len（len的初始值）；
 * 2. 把剩余的部分从左边开始删除，直到剩下的最右边部分单调递增；
 * 3. 循环，保留右边部分的最后i个（i = 1, 2, 3 ...）元素，将左边窗口内不满足单调的元素删除，计算总共需要删除的元素数量；更新len(取小者)；
 *     第3步中，i = 0 的情况已在第一步中完成。
 */
int delesubSequence(const std::vector<int>& array)
{
    int right=0, i=1, n=array.size();
    int len = 0;

    // Find the longest incremental sub array on the left.
    while (i<n && array[i]>array[right])
    {
        right=i;
        i++;
    }
    len = n-1-right;

    // Cut the remainder array until it's incremental.
    size_t left = i;
    for(size_t i=left+1; i<n; i++)
    {
        // 若不满足严格递增条件，则左边界加一
        left = array[i]<=array[i-1]?i:left;
    }   

    // Make sure that the small end of right array is larger than the big end of left array.
    for(int i=n-1;i>=left; i--)
    {
        // 左框的右边界若大于右框内的某一元素，则往左退，直到满足单调递增后更新当前需删除的元素个数len。
        // i和right的意义是：i及i后的元素，以及right和right之前的元素，将联合起来拼凑成一个单调递增的元素；
        // 将i从最后逐步往前，通过枚举所有可能来更新答案。
        // 由于i越往前其所指数字越小，此前不能满足array[right]<array[i]的right，此后一定也不能满足，因此right不用复原。
        while(right>=0 && array[i]<array[right])
            right--;
        std::cout<<len<<" "<<right<<" "<<i<<" "<<i-right-1<<std::endl;
        len = std::min(len, i-right-1);
    }

    return n-len;
}

int main()
{
    int temp;
    std::vector<int> array;
    std::cin>>temp;
    array.emplace_back(temp);
    while (std::cin.get()!='\n')
    {
        std::cin>>temp;
        array.emplace_back(temp);
    }
    std::cout<<delesubSequence(array);
}