/*
 * @Author: avert-win
 * @Date: 2022-05-26 21:32:58
 * @LastEditTime: 2022-05-26 22:31:41
 * @FilePath: \ProgramDaily\c_cppSample\typedef.c
 * @Description: 简介
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

//define a function pointer called printer_t.
typedef void (*printer_t)(int);
//declare a variable.
printer_t p = &print_to_n;
//the same as above.
void (*p_comp)(int) = &print_to_n;


//In a more complicate situation, typedef is more powerful.
void foo(printer_t printer, int y)
{
    printer(y);
}
//the same as above, but more complicate.
void foo_comp(void (*printer)(int), int y)
{
    printer(y);
}

int main()
{
    foo(p, 3);
    foo_comp(p, 3);
}