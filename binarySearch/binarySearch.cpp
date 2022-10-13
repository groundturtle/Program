/*
 * @Author: avert-win
 * @Date: 2022-10-09 16:59:10
 * @LastEditTime: 2022-10-09 19:23:09
 * @FilePath: \ProgramDaily\bulk\binarySearch.cpp
 * @Description: 在一个非递减数组中查询目标数字出现的次数，使用二分法。
 * @LastEditors: avert-win
 */
#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
    int binarySerach(vector<int>& nums, int target, bool bigger){
        int left = 0;
        int right = nums.size() - 1;
        int ans = nums.size();
        // 二分搜索定式：定义左边界、右边界、中间索引
        // 由于要寻找第一个更大或相等的，因此每次若nums[mid]为符合条件的数都要将mid记录下来，并且以mid-1为右边界的新值继续逼近。
        // 如果nums[mid]不符合条件，则应该以mid+1为左边界的新值。
        // 如果没有任何一个数字符合条件，则right和left左右错位
        while(left <= right){
            int mid = (left + right) / 2;
            if((!bigger && nums[mid] >= target) || (bigger && nums[mid] > target)){
                right = mid - 1;
                ans = mid;
            }
            else{
                left = mid + 1;
            }
        }
        return ans;
    }

    int search(vector<int>& nums, int target){
        int right = binarySerach(nums, target, true);
        int left = binarySerach(nums, target, false);
        // 只有比目标大的或小的
        if(left == right){
            return 0;
        }
        return right - left;
    }

};