'''
Author: avert
Date: 2022-04-14 22:08:15
LastEditTime: 2022-04-14 23:48:07
Description: 请填写简介
'''
# https://www.cnblogs.com/gongcheng-/p/10894205.html

#! With hash table, unorderd_map of cpp and dict in python
#! have almost O(1) time complexity.

'''cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }
};
'''

class Solution:
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        hashtable = dict()
        for i, num in enumerate(nums):
            if target - num in hashtable:
                return [hashtable[target - num], i]
            hashtable[nums[i]] = i
        return []