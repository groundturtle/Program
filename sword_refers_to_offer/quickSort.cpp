/*
 * @Author: avert-win
 * @Date: 2022-10-25 18:37:00
 * @LastEditTime: 2022-10-25 21:22:40
 * @FilePath: \ProgramDaily\sword_refers_to_offer\quickSort.cpp
 * @Description: 简介
 * @LastEditors: avert-win
 */
#include<bits/stdc++.h>
using namespace std;
class Solution {
    int partition(vector<int>& arr, int low, int high)
    {
        int pivot = arr[high-1];    // 以最后一个数为基准
        int i = low; // Index of smaller element and indicates
                    // the right position of pivot found so far
        // 分为两个区域，一个是已经确定比pivot小的，起于low、终于i（左闭右开）
        // 一路向前遍历，凡是发现小的就和未确定区域的第一个交换，不管前面是否也小。
        for (int j=low; j < high-1; j++) {
            if (arr[j] < pivot) {
                swap(arr[i], arr[j]);       // 可能存在一路和自身交换的风险，但并不影响正确性
                i++;            // increment index of smaller element
                // cout<<arr[i]<<" "<<arr[j]<<endl;
            }
        }
        swap(arr[i], arr[high-1]);
        return i;
    }
public:
    bool isStraight(vector<int>& nums) {
        int low = 0;
        int high = nums.size();
        quickSort(nums, low, high);
        return true;
    }
    void quickSort(vector<int>& arr, int low, int high)
    {
        // 左闭右开
        if(low < high){
            int p = partition(arr, low, high);
            quickSort(arr, low, p);
            quickSort(arr, p+1, high);
        }
    }
};

int main()
{
    Solution solu = Solution();
    vector<int> nums = {1,2,3,4,5};
    solu.quickSort(nums, 0, nums.size());
    for(auto n : nums){
        cout<<n<<" ";
    }
}