/*
 * @Author: avert-win
 * @Date: 2022-06-07 20:38:37
 * @LastEditTime: 2022-06-07 20:54:44
 * @FilePath: /os/void_star_static.c
 * @Description: 简介
 * @LastEditors: avert-win
 */
#include<stdio.h>

const int x = 3;
// pointer with address of x as value, void** as type.
void **ptr_of_addr = (void**)&x;
// pointer with value of x as value, void* as type.
void *value_to_ptr = (void*)x;
// pointer with address of x as value, void* as type.
void *addr = (void*)&x;

int y = -2;

void func1()
{
    static int y = 1;
    printf("y in func1(): %d.\n", y);
}

void func2()
{
    static int y = 2;
    printf("y in func2(): %d.\n", y);
}

// with static declaration of y, func3 will still get it's own y, intead of global y.
void func3()
{
    static int y;
    printf("y in func3(): %d.\n", y);
}

int main()
{
    func1();
    func2();
    func3();
    return 0;
}