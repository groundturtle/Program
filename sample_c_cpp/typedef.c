/*
 * @Author: avert-win
 * @Date: 2022-05-26 21:32:58
 * @LastEditTime: 2022-10-26 21:42:06
 * @FilePath: \ProgramDaily\sample_c_cpp\typedef.c
 * @Description: typedef类型定义，定义函数指针类型和函数指针的使用。
 * @LastEditors: avert-win
 */
#include<stdio.h>

void print_to_n(int n)
{
    for(int i=1; i<=n; i++)
    {
        printf("%d\n", i);
    }
}

void print_n(int n)
{
    printf("%d\n", n);
}

// define(give a name) a type of function pointer called printer_t.
// the instance of this type can point to any function that look like `void func(int)`.
typedef void (*printer_t)(int);

//declare a variable of type printer_t.
printer_t p = &print_to_n;

//the same as above but without using the type name.
void (*p_comp)(int) = &print_to_n;


//In a more complicate situation, typedef is more powerful.
void foo_comp(void (*printer)(int), int y)
{
    printer(y);
}

// with type defined, it's more simple now.
void foo(printer_t printer, int y)
{
    printer(y);
}

int main()
{
    foo(p, 3);
    foo_comp(p, 3);
}