/*
 * @Author: avert-win
 * @Date: 2022-10-13 11:54:29
 * @LastEditTime: 2022-10-13 16:46:46
 * @FilePath: \ProgramDaily\sword_refers_to_offer\translateNum.cpp
 * @Description: 翻译数字，0到25可翻译，其中如25的数字有两种翻译方式，但06只有一种方式，求总共有几种方式。用动态规划方法。
 *      https://leetcode.cn/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/solution/
 * @LastEditors: avert-win
 */

/**
小于等于25的两位数和大于25的数分别有2种和1种翻译法；
每增加一个数，如果与前一个数合并大于25，则没有新的翻译方法，f(n) = f(n-1);
如果合并小于等于25，则有与num[n-1]合并与不合并两种方法，但是与num[n-1]合并又与num[n-1]与num[n-2]合并的方法冲突，需去掉其一取其大者。

分两数f()和g()计算，分别为最后两个合并、最后一个单独，h(n,n-1)为num[n]与num[n-1]合并的翻译方法数（0或1），有递推式：
f(n) = h(n-1,n) * (g(n-2) + f(n-2))  // 前后关系（前n-2个与后2个）应相乘，并列（最后两个合并与相加）应相加
g(n) = f(n-1) + g(n-1)

记r(n)为n个数字的翻译方法，则有r(n) = f(n) + g(n)，且g(n) = r(n-1)，只剩最后一个单独翻译时翻译方法数为1.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution {
    int h(char a, char b){
        // 0开头的两位数不可翻译成一位，测试过了才知道
        if((a - '0')*10 + (b - '0') <= 25 && (a - '0')*10 + (b - '0') >=10)
            return 1;
        else 
            return 0;
    }
public:
    int translateNum(int num) {
        int jie = 0;
        string numStr = to_string(num);
        if(numStr.length() == 1)
            return 1;
        for(int i=1; i<numStr.length(); i++){
            if(h(numStr[i-1], numStr[i]))
                jie ++;
        }


        if(numStr.length() == 1)
            return 1;
        int f = 0, g = 0;      
        int f_1 = 0, g_1 = 1;         // 初始化为处理完第一个数字的状态，必须严格正确 
        int f_2 = 0, g_2 = 1;           // g_2仅用于乘，因此初始化为1 
        for(int i=1; i<numStr.length(); i++){
            f = h(numStr[i-1], numStr[i]) * (g_2 + f_2);
            g = f_1 + g_1;

            f_2 = f_1;
            f_1 = f;
            g_2 = g_1;
            g_1 = g;
        }
        return f + g;
    }
};

int main(){
    Solution solu;
    cout<<solu.translateNum(506);
    cout<<solu.translateNum(25);
    return 0;
}