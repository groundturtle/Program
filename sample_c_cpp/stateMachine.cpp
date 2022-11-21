/*
 * @Author: avert-win
 * @Date: 2022-10-29 18:18:49
 * @LastEditTime: 2022-10-31 21:13:20
 * @FilePath: \ProgramDaily\sample_c_cpp\stateMachine.cpp
 * @Description: 判断一个字符串是为前后可以有空格、小数点前后缀可以省略、用e表示指数的数字。
 * 如："  -.12e12" 合法，" +.21e2.3 "不合法，指数部分不允许为小数。
 *      解题方法为使用状态机：画出每个状态，然后画出状态之间的转换，最终根据这个状态图来进行变量定义、程序编写。
 * @LastEditors: avert-win
 */
// https://leetcode.cn/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof/solution/biao-shi-shu-zhi-de-zi-fu-chuan-by-leetcode-soluti/

// 按顺序只许头尾空格，中间不许空格；
// 空格之后头部正负符号可以有其一，接着必须是x.y或.y或y.的形式；
// 最后可选e或E其一接一整数，不得为小数或为空。
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        int i=0, len = s.length();
        int flag = 0;               // 分阶段
        bool point = false;         // 小数点是否出现过
        bool pointFlag = false;     // 小数点刚出现过，且前一个不是数字
        bool exponent = false;      // 指数符号刚出现过，下一个必须为数字
        while(i<len){
            if(flag==0){
                if(s[i]==' ')
                    i++;
                else
                    flag++;         // 转阶段时i不自增，因此可以直接跳到下次循环；以下亦同
            }
            else if(flag==1){
                if(s[i]=='+' || s[i] == '-'){
                    i++;
                    flag++;
                }
                else if(s[i]=='.' || (s[i]<='9'&&s[i]>='0')){   // 必须为小数点或数字才能转向下一阶段
                    flag++;
                }
                else{
                    return false;
                }
            }
            else if(flag==2){
                if(point && s[i] == '.')    //重复小数点
                    return false;
                if(s[i] == '.'){    // 首次出现小数点
                    i++;
                    point = true;
                    if( (i<len && (s[i]<'0'||s[i]>'9')) || (i-2>=0 && (s[i-2]<'0'||s[i-2]>'9')) ){
                        return false;
                    }
                    if(i>=len && i-2<0)
                        return false;
                }
                else if(s[i]>='0' && s[i]<='9'){    // 是数字
                    i++;
                }
                else if(s[i] == 'e' || s[i] == 'E'){    // 指数符号出现，跳转到下一个阶段
                    flag++;              
                }
                else{               // 不是小数点也不是数字，也没有跳转到下一个阶段（指数）
                    return false;
                }
            }
            else if(flag==3){
                i++;            // 上面必已确认s[i]是'e'或'E'，下一个必须是数字
                if(exponent && (s[i]<'0' || s[i] >'9'))
                    return false;
                if(exponent)
                    exponent = false;       // 一个数字以后，允许转为空格
                if(s[i] == ' ')
                    flag++;
            }
            else if(flag==4){
                if(s[i] != ' ')
                    return false;
            }
        }
        if(flag==4)
            return true;
        return false;
    }
};