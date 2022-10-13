/*
 * @Author: avert-win
 * @Date: 2022-05-06 09:32:51
 * @LastEditTime: 2022-05-06 18:29:02
 * @FilePath: /ProgramDaily/cppSample/link/link.c
 * @Description: 链接符号及其作用域的简单介绍和实验。
 * @LastEditors: avert-win
 */

/**
 * 1. Global: 由模块m定义，能被其它模块引用的符号。
 * 2. External: 由其它模块定义并被模块m引用的全局符号。
 * 3. Local: 由模块m定义和引用的本地符号（外部不能引用），例如static变量和函数
 * 
 * 强符号：函数和已经初始化的全局变量；
 * 弱符号：未初始化的全局变量（初始化为0的整形变量）
 * 
 * 对于全局符号的多重定义，有如下规则：
 * 1. 不允许有多个强符号，若有，则直接报错；
 * 2. 允许多个相同弱符号，在相同的弱符号和强符号之间，选择强符号；
 * 3. 在多个相同的弱符号之间，任意选择一个（视编译器和其他因素而定）。
 */

#include<stdio.h>
static int x=20;

// 未初始化的弱符号，不报错。
int _x;
int _x;
int _x = 3;
int _y;

// 多个弱符号和一个强符号之间，选择强符号。
void p_symbol()
{ 
    printf("_x: %d", _x); 
}

// 在gcc命令中加入参数`-DINITIALIZE`，则预处理器会认为已经进行了初始化，
// 打印出来的值将会是_g: 23 和 _i: 1；否则打印出来的是未初始化的结果。
extern int _g;           
void preprocess()
{
    #include<preprocess.h>
    //! scope cannot have linkage.
    // extern int _g;           
    printf("\n_g: %d, _i: %d", _g, _i);
}

void p_dll()
{
    // 动态加载动态库的头文件是<dlfcn.h>，库名是<dl>。
    #include<dlfcn.h>
    void *handle;
    handle = dlopen("/home/avert/project/ProgramDaily/cppSample/link/libmylib.so", RTLD_LAZY);
    if(!handle)
    {
        // 捕获错误输出到标准错误流
        fprintf(stderr, "%s\n", dlerror());
    }
    // 创建函数指针，然后从动态库加载函数
    void (*dll_print)();
    dll_print = dlsym(handle, "print");
    // 加载完毕之后，就可以通过函数指针调用函数了。
    dll_print();
    dlclose(handle);
}

int main()
{
    p_symbol();
    preprocess();
    p_dll();
}


/**
 * 若条件允许，尽量不使用全局变量；
 * 若必须使用全局变量，尽可能使用static，一定要初始化；
 * 若需要使用外部全局变量，需使用extern关键字。
 */