/**
 * @file testElse.cpp
 * @author avert-goose (avert-goose@hnu.edu.cn)
 * @brief 测试运算符重载
 * @version 0.1
 * @date 2023-03-25
 */
#include<bits/stdc++.h>
#include"overloadOP.h"

void testOPoverload(){
    my::Matrix matrix(3, 3);        // 有参构造
    my::Matrix m2(matrix);          // 拷贝构造
    std::cin>>matrix;               // 输入重载
    m2 = matrix;                    // 赋值重载
    std::cout<<matrix<<std::endl;   // 输出重载
    std::cout<< ((m2 == matrix) ? "true\n" : "false\n");    // 相等重载

    my::Matrix m3(std::move(m2));   // 移动构造
    std::cout<<m2<<std::endl;           // 移动构造后，参数矩阵为空（内容被移动走了）。
}

int main(){
    testOPoverload();
}