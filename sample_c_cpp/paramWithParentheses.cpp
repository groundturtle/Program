/*
 * @Author: avert-win
 * @Date: 2022-10-31 18:02:27
 * @LastEditTime: 2022-10-31 18:26:12
 * @FilePath: \ProgramDaily\sample_c_cpp\paramWithParentheses.cpp
 * @Description: 简介
 * @LastEditors: avert-win
 */
#include<iostream>
#include<fstream>
#include<list>
using namespace std;

// 如下，在函数形参变量两端加上括号是可行的
int func1(int a, int (b)){
    return a + b;
}

// 但是不能用一个括号将形参的变量类型囊括起来（或单独括住类型）。
// int func1(int a, (int b)){
//     return a + b;
// }

class T{
public:
    T(){};
    T(int){};
};

// 因函数定义不能在参数两端加括号，因此编译器匹配到另一种可能。
int main(){
    T t0();         // 声明函数
    T t1(2);        // 实例化对象
    T t = T();      // 实例化对象

    int x;
    list<int> L0(list<int>(x));     // 声明函数
    list<int> L1( (list<int>(x)) );  // 构造链表
}