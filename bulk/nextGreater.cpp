/*
 * @Author: avert-win
 * @Date: 2022-09-22 09:19:03
 * @LastEditTime: 2022-09-23 16:47:56
 * @FilePath: \ProgramDaily\bulk\nextGreater.cpp
 * @Description: nums1中的元素从nums2中提取，求其中每个元素在nums2中的下一个更大元素。单调栈方法。
 * @LastEditors: avert-win
 */

/**
 * 从后向前遍历nums2，维护一个自底向上单调递减的栈，每个nums1中的数字
 * 只需与栈中数字比较，不需要与整个nums2比较。
 * 又nums1中的数字源于nums2，因此在构造单调栈的过程中就可以将每个数字的
 * 下一个更大元素存储起来，稍后直接从字典中提取。
 */

#include<bits/stdc++.h>
using namespace std;

vector<int> nums1{4,1,2};
vector<int> nums2{1,3,4,2};

int main()
{
    stack<int> monotony;
    unordered_map<int, int> greater;
    int len2 = nums2.size();
    auto it=nums2.end();
    for(int i=len2-1; i>=0; i--)
    {
        int temp = nums2[i];
        // 比x[i]小或相等的数出栈，保证栈内数字自底向上是从大到小的；
        while(!monotony.empty() && temp>=monotony.top())
            monotony.pop();
        // x[i]映射到第一个严格比x[i]大的数，没有（栈空）则-1
        greater[temp] = monotony.empty() ? -1:monotony.top();
        // x[i]一定比栈内所有的数都小，入栈后仍然单调，等待筛选。
        monotony.push(temp);
    }
    vector<int> result(nums1.size());
    for(int i=0; i<nums1.size(); i++)
    {
        result[i] = greater[nums1[i]];
    }
    for(auto i:result)
        cout<<i<<" ";
    // return result;
}