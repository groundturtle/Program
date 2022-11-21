/*
 * @Author: avert-win
 * @Date: 2022-10-27 08:56:37
 * @LastEditTime: 2022-10-27 10:30:43
 * @FilePath: \ProgramDaily\binarySearch\insertPlace.cpp
 * @Description: 最简单的二分查找形式，找到非递减数组中该数可插入的位置。
 * @LastEditors: avert-win
 */
#include<bits/stdc++.h>
using namespace std;

// 向非递增数组中插入一个新数，查找该数插入后在数组中的下标。
int findPlace(vector<int>& nums, int num){
    int start = 0;
    int end = nums.size();
    int mid = 0;
    while(start < end){
        mid = (start + end) / 2;
        if(nums[mid] < num)         // 小于向右，在只有一个数字的情况下start会越界，然后退出循环，然而插入这个越界的位置是没有问题（正好正确的）。
            start = mid + 1;
        else if(nums[mid] > num)         // 大于向左
            end = mid;      // 左闭右开，end不应为mid-1。
        else if(nums[mid] == num)        // 相等直接返回
            return mid;
    }
    return start;
}

int main(){
    vector<int> v1 = {5};
    vector<int> v2 = {1};
    // 由于vector::insert()的线性时间复杂度，使用二分法查找插入位置实际上没有意义
    int index = findPlace(v1, 3);
    int index2 = findPlace(v2, 3);
    v1.insert(v1.begin()+index, 3);
    v2.insert(v2.begin()+index2, 3);
    cout<<index<<"  "<<index2<<endl;
    for(auto n : v1)
        cout<<n<<"  ";
    cout<<endl;
    for(auto n : v2)
        cout<<n<<"  ";
}