/*
 * @Author: avert-win
 * @Date: 2022-11-17 22:28:45
 * @LastEditTime: 2022-11-17 22:35:56
 * @FilePath: \ProgramDaily\monotonic_stack\nextGreaterV2.0.cpp
 * @Description: 为数组中的每个数寻找其下一个更大的数，输入数组视为头尾相接的环。
 *      注意相比V1.0，本题输入数组不保证没有重复元素。
 * @LastEditors: avert-win
 */

/*
* 使用单调栈，按非循环数组的方法，只需要额外将数组复制一份拼接在一起即可。
* 为节省空间，也可以只用一个标记，允许一次到尾之后回头重来。
* 注意由于将数组复制了一遍，即便原本不存在重复的数字也会重复，因此必须注意出入栈时的比较条件。
*/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> ret(nums.size());       // 因数组中存在重复元素，必须用序列容器来保证顺序
        stack<int> monotonic;
        for(int i=nums.size()-1; i>=0; i--){
            while(!monotonic.empty() && nums[i] >= monotonic.top())
                monotonic.pop();
            if(monotonic.empty()){
                ret[i] = -1;
            }
            else{
                ret[i] = monotonic.top();
            }
            monotonic.push(nums[i]);
        }
        // 栈不清空，重来一次，第一轮中已找到下一个更大值而这次没找到的以上次为准；若都找到则必相同。
        for(int i=nums.size()-1; i>=0; i--){
            while(!monotonic.empty() && nums[i] >= monotonic.top())
                monotonic.pop();
            // 这次找到了，直接修改；没找到的不管（monotonic.empty()为true情况）
            if(!monotonic.empty()){
                ret[i] = monotonic.top();
            }
            monotonic.push(nums[i]);
        }
        return ret;
    }
};

int main(){
    Solution solu = Solution();
    vector<int> nums = {1,2,3,4,3};
    solu.nextGreaterElements(nums);
}