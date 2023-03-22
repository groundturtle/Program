/*
 * @Author: avert-win
 * @Date: 2022-10-12 19:42:13
 * @LastEditTime: 2022-10-13 08:15:28
 * @FilePath: \ProgramDaily\sword_refers_to_offer\findMin.cpp
 * @Description: 寻找旋转过的非递减数组中的最小元素。
 *      使用二分法，是对二分法的扩展，仅对区域的一个边缘进行对比、相等时向里收缩而不二分。最差时间复杂度O(n)，平均略大于O(logn)
 * @LastEditors: avert-win
 */
// https://leetcode.cn/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int len = nums.size();
        int left = 0, right = len - 1;
        int result = INT_MAX;
        while(left < right){
            int mid = (left + right) / 2;
            // mid处可能就是最小值，因此令right = mid 而非 mid + 1
            if(nums[mid] < nums[right])
                right = mid;                
            // right处可能是最小值，而right不变更，因此无需理会
            else if(nums[mid] > nums[right])   
                left = mid + 1;
            // 平坦处，令right缩小1，此后无论是mid首先跨出平原还是right首先跨出平原，都能得到适当处理。
            // 因为mid是与right比较，所以收缩的必须是right，否则如left陷入低谷的情况会使解题出错。
            else 
                right = right - 1;
        }
        return nums[left];
    }
};



int main(){
    Solution solu;
    vector<int> mynums = {3, 5, 2};
    int result = solu.findMin(mynums);
    cout<<result<<endl;
    return 0;
}