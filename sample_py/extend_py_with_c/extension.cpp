/*
 * @Author: avert-win
 * @Date: 2022-06-29 19:09:13
 * @LastEditTime: 2022-06-29 19:53:45
 * @FilePath: /ProgramDaily/extend_py_with_c/extension.cpp
 * @Description: 
 * @LastEditors: avert-win
 */
#include<iostream>
/*
 * C++ 允许函数重载，因此仅仅依靠函数名称不能确定链接时的唯一id，需要添加参数信息到符号名称中；
 * 当使用`extern "C"`指明时，编译器就不再自动添加参数信息，因此可以被C(或Python的ctypes)用于链接。
 */

/**
 * @brief `g++ extension.cpp -fPIC -shared -o libextension.so`
 * because of C++ name mangling, you have to use `extern "C"` to define symbols.
 */
extern "C" 
int sum(int a, int b)
{
    return a + b;
}

extern "C"
{
    void display(char *str)
    {
        printf("%s\n", str);
    }
}