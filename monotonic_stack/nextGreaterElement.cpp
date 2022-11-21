/*
 * @Author: avert-win
 * @Date: 2022-11-17 21:26:34
 * @LastEditTime: 2022-11-17 21:29:10
 * @FilePath: \ProgramDaily\monotonic_stack\nextGreaterElement.cpp
 * @Description:
 *      nums1中元素全部取自nums2，求nums1中每个元素在nums2中的右边的第一个更大元素。题目保证nums1和nums2中数字皆没有重复。
 * @LastEditors: avert-win
 */

/**
* 使用单调栈：
*   逆向遍历、维护一个栈底向栈顶递减的单调栈： 
*        每一个元素将入栈时，栈顶的元素就是右边第一个大于该元素的元素。若栈空，则右边没有大于该元素的元素。
*   因此此题的关键是在入栈时就已经完成了问题的判断解决，而不是等到栈已形成才从栈中得出结论。
*   使用哈希表可以在常数时间内完成结果的记录，最后在线性时间内依次取出放到返回值中即可。
*/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> upIncrease;
        unordered_map<int, int> nextBigger;         // 因没有重复元素，不存在任何歧义
        for(auto it=nums2.rbegin(); it!=nums2.rend(); it++){    // 反向迭代器就有反向迭代器的加法，不是指针、不逆序，不使用减法
            // 出栈，以使稍后元素入栈后保持单调
            while(!upIncrease.empty() && *it > upIncrease.top()){
                upIncrease.pop();
            }
            if(!upIncrease.empty()){
                nextBigger[*it] = upIncrease.top();
            }
            else{
                nextBigger[*it] = -1;       // 右边没有更大的，记为-1.
            }
            upIncrease.push(*it);
        }

        vector<int> ret;
        for(const auto& n : nums1){
            ret.push_back(nextBigger[n]);
        }
        return ret;
    }
};