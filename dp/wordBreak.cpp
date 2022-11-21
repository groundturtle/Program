/*
 * @Author: avert-win
 * @Date: 2022-11-14 20:58:06
 * @LastEditTime: 2022-11-15 21:54:13
 * @FilePath: \ProgramDaily\dp\wordBreak.cpp
 * @Description: 给定一个字符串和一个字典，判断字符串是否可有字典中单词拼接构成（单词可复用）。
 * @LastEditors: avert-win
 */

/**
 * @brief 此题字符串（单词）之间没什么内在关系，因此必须使用相对暴力的方法：
 *      穷尽所有可能以不同方式切割字符串，并判断每一个分段的可拼接性；若全部可拼接则整个字符串可拼接，反之不然。
 * 在此基础上，应用动态规划方法：
 *      从头到尾进行从短到长的切割，存储每一个不同前缀子串的合法性；
 *      将前缀子串[0,i]分解为一个前缀子串[0,j]和一个由子串[j,i]构成的单词，则问题分解为一个已知子问题dp[0,j]和一个未知子问题dp[j,i]；
 *          此时只要穷举分解的前缀子串的长度（穷举j），就能利用此前存储的结果，在常数时间内计算一种可能的合法性；
 *      至此，任意一个长度为n的子串已经能够被分解为2*n个常数时间的子问题进行求解。
 */

#include<bits/stdc++.h>
using namespace std;

class Solution{

public:
    bool wordBreak(string s, vector<string>& wordDict){
        unordered_set<string> dict;                     // 牺牲空间换取时间：查找更快速。
        for(auto word : wordDict){
            dict.insert(word);
        }
        dict.insert("");        // 填入空字符串，以保证空字符串的合法性。
        bool dp[s.length()+1];              // dp[i] 表示s[0:i]是否可拼接
        dp[0] = true;                   // 空字符串可拼接

        // 判断[0,i]是否可拼接(外循环)
        for(int i=0; i<=s.length(); i++){        
            // 将任务拆解，分为判断[0,j]和[j,i]是否可拼接两个子任务，并对j进行穷举(内循环)。
            for(int j=0; j<=i; j++){            
                // 运用动态规划方法，子任务（[0,j]是否可拼接）是已经知道的，可以直接引用。
                if(dp[j] && dict.find(s.substr(j, i-j))!=dict.end() ){
                    dp[i] = true;               // 一旦确定[0,i]可拼接，就没有必要再穷举下去，直接退出、令i自增即可。
                    break;
                }
                dp[i] = false;
            }
        }
        return dp[s.length()];
    }
};

int main(){
    Solution solu = Solution();
    string s = "leetcode";
    vector<string> wordDict = {"leet","code"};
    cout<<solu.wordBreak(s, wordDict)<<endl;
}