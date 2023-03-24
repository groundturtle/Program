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

template <typename T>
using Iter = typename vector<T>::iterator;      //! 必须加上typename才能标识！

/**
 * @brief 选取最右边为基准，相等和更大的的放到右边，稳定排序。\n
 * 调用者必须保证传入的区间长度不为0.
 * 
 * @param arr 整个待排序数组。
 * @param begin 指向待排序部分开头的元素的迭代器
 * @param end 待排序部分的结尾迭代器（开区间）
 * @return vector<int>::iterator 分界线：左小右大（或相等）。
 */
vector<int>::iterator sortPart(vector<int>& arr, Iter<int> begin, Iter<int> end){
    vector<int> tmp(arr.begin(), arr.end());       // 拷贝，用于排序，以保证稳定。
    Iter<int> pit = tmp.begin();

    Iter<int> it = begin;
    int pivot = *(end-1);
    while(it != end){           // 首先遍历一次，小于的依次放到前头
        if(*it < pivot){
            *pit = *it;
            pit ++;
        }
        it++;
    }

    *pit = pivot;            // 然后中间把分界线放进来。
    // Iter<int> ret = pit;         //! 返回值不对！返回了一个被销毁变量的指针!
    Iter<int> ret = pit;
    pit++;

    it = begin;
    while(it != end){           // 最后再遍历一次，大于等于的依次放到前头
        if(*it >= pivot){
            *pit = *it;
            pit ++;
        }
        it++;
    }
    // 将临时空间里的数据拷贝回去。
    it = tmp.begin();
    while(begin != end){
        if(it == ret)       // 因为长度相等，当 tmp 迭代器到达了标记位置，arr 迭代器也到达了，此时才能获得返回值。
            ret = begin;        // 这才是真正应该返回的！
        *begin = *it;
        begin++;
        it++;
    }
    return ret;
}

void quickSort(vector<int>& arr, vector<int>::iterator begin, vector<int>::iterator end){
    if(begin == end)
        return;
    Iter<int> ret = sortPart(arr, begin, end);
    cout<<*ret<<"  ";
    if(ret != begin){
        quickSort(arr, begin, ret);
    }
    if(ret+1 != end){      
        quickSort(arr, ret+1, end);         //! 这里不加一就永远出不去！因为被调用者的栈中begin和end不相等！
    }
    return;
}

int main(){
    vector<int> arr = {9,1,2,-2,-3,112,5,7,-3};
    quickSort(arr, arr.begin(), arr.end());
    cout<<endl;
    for(auto it=arr.begin(); it!=arr.end(); it++){
        cout<<*it<<" ";
    }
}