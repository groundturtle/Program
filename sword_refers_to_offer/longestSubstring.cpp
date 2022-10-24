/*
 * @Author: avert-win
 * @Date: 2022-10-13 20:56:32
 * @LastEditTime: 2022-10-13 21:01:57
 * @FilePath: \ProgramDaily\sword_refers_to_offer\longestSubstring.cpp
 * @Description: 简介
 * @LastEditors: avert-win
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int length = s.length();
        size_t result = 0;
        size_t left = 0, right = 0;     // 左闭右开（与right++处于循环体中的位置有关）
        unordered_map<char, bool> chars;
        while(right < length){
            // 如果首次出现，窗口直接向右扩张
            if(!chars[s[right]]){
                chars[s[right]] = true;
                right++;
            }
            // 如果已存在，更新当前最长窗口长度，然后窗口左边沿向右收缩直到不重复。
            else{
                result = max(result, right-left);
                while(chars[s[right]] && left<=right){
                    chars[s[left]] = false;
                    left++;
                }
                // chars[s[right]] = true;  因为在循环体内最开始进行判断、赋值，此处不能改变为真，否则会导致无限循环！
            }
        }
        result = max(result, right-left);
        return result;
    }
};


int main(){
    Solution solu;
    cout<<solu.lengthOfLongestSubstring("aabcaabcd");
}