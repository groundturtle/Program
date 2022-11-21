/*
 * @Author: avert-win
 * @Date: 2022-10-26 11:00:45
 * @LastEditTime: 2022-11-14 18:06:10
 * @FilePath: \ProgramDaily\sword_refers_to_offer\addWithoutoperator.cpp
 * @Description: 不使用任何库函数和四则运算运算符，实现加法
 *      只能考虑位运算，发现异或得不进位结果，与得进位部分、再左移一位即得进位结果。
 *      将加法的结果拆成以上两个部分，不断进行，直到两者其一为0返回另一，或者两者相与为0时返回两者相或。
 * @LastEditors: avert-win
 */
#include<bits/stdc++.h>
using namespace std;
/*
    某些编译器禁止负数左移！
    负数补码相加若原码不溢出，则第二位必向符号位进位，符号位进位被舍去、本位由第二位的进位填补，符号位仍然不变；
    由于以上原因，两数皆为负时，相加结果的进位部分必包括符号位，移位之前必须先转成unsigned类型以免引发编译错误。
*/
class Solution {
public:
    int add(int a, int b) {
        // while (a & b) {
        while( b != 0){
            unsigned int carry = (unsigned int)(a & b) << 1;
            a = a ^ b;
            b = carry;
        }
        // return a | b;
        return a;
    }
};