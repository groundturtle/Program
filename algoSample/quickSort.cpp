/*
 * @Author: avert-win
 * @Date: 2022-11-22 18:32:09
 * @LastEditTime: 2022-11-22 19:25:39
 * @FilePath: \ProgramDaily\sample_c_cpp\quickSort.cpp
 * @Description: 尝试自己实现一个快速排序算法。
 * @LastEditors: avert-win
 */

//& 快速排序的稳定化实现：额外开辟一个完整的空间，先遍历处理大的放进末端、再遍历处理小的放进前端，最后拷贝回原位。

#include<bits/stdc++.h>
using namespace std;

/**
 * @brief 选取最右边为基准，相等和更大的的放到右边，不保证相等的相邻。
 * @param arr 整个待排序数组。
 * @param start 此次需要排序的部分的开头迭代器
 * @param end 此次需要排序部分的结尾迭代器（开区间）
 * @return vector<int>::iterator 分界线：左小右大（或相等）。
 */
vector<int>::iterator sortPart(vector<int>& arr, vector<int>::iterator start, vector<int>::iterator end){
    vector<int>::iterator r = end;
    vector<int>::iterator l = start;
    r--;
    int pivot = *(end--);
    while(l != r){       // 从左到右，小于与大于交换，最后pivot放到start和end相逢处。
        if(*l < pivot){
            l++;
            continue;
        }
        if(*r >= pivot){
            r--;
            continue;
        }
        int temp = *l;
        *l = *r;
        *r = temp;
    }
    assert(l == r);
    *(end-1) = *r;
    *r = pivot;
    return l;
}

// 为保持调用习惯一致，参数左闭右开。因为此函数才是递归函数，递归出口也必须设置在这里。此处采用的方式是设置递归退出条件，而不是递归准入条件。
void quickSort(vector<int>& arr, vector<int>::iterator begin, vector<int>::iterator end){
    if(begin != end){
        auto mid = sortPart(arr, begin, end);
        // 分界线本身不需要再参与排序。
        quickSort(arr, begin, mid);     
        quickSort(arr, mid+1, end);         // 因为是左闭右开，一定有mid+1 <= end，所以以上判断足够退出递归。
    }
}

int main(){
    vector<int> arr = {9,1,2,-2,-3,112,5,7,-3};
    quickSort(arr, arr.begin(), arr.end());
    cout<<endl;
    for(auto it=arr.begin(); it!=arr.end(); it++){
        cout<<*it<<" ";
    }
}