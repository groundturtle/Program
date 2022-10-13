/*
 * @Author: avert-win
 * @Date: 2022-05-06 18:28:42
 * @LastEditTime: 2022-05-07 15:00:35
 * @FilePath: /ProgramDaily/cppSample/link/scope.c
 * @Description: 简介
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
 * 
 * ? 注意：编译时的本地符号，在链接器眼里是不存在的符号，链接器只关心文件整体，
 * ? 函数内部和循环内部的符号相关问题由所属文件自行解决。
 * ? 链接器的本地符号指的是static，其它文件不可访问的符号。
 * ? 链接符号和程序语言代码符号不同，多个函数内的同名static变量在链接时是不同的。
 */

static int x = 20;

// Q: 为什么此处定义了未初始化的弱符号，而全局有已初始化的强符号，但函数返回的仍然是局部的弱符号？
int f()
{
    static int x;
    return x += 1;
}

int g()
{
    static int x=10;
    return x += 3;
}

int h()
{
    return x += 5;
}

int main()
{
    printf("f(x) = %d\n", f());
    printf("f(x) = %d\n", f());
    printf("g(x) = %d\n", g());
    printf("g(x) = %d\n", g());
    printf("h(x) = %d\n", h());
    printf("h(x) = %d\n", h());
}
