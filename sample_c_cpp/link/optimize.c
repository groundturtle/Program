/*
 * @Author: avert-win
 * @Date: 2022-05-06 15:38:45
 * @LastEditTime: 2022-05-06 16:55:51
 * @FilePath: /ProgramDaily/cppSmaple/optimize.c
 * @Description: 记录一些简单的代码优化方法。
 * @LastEditors: avert-win
 */

/**
 * 1. 减少函数调用，需要函数返回值时尽量存储而非反复调用；
 * 2. 减少存储器引用，需要的外部变量尽量使用临时（局部）变量先保存，最后再写入存储器；
 * 3. 循环展开；开启了优化的编译器也会为我们进行循环展开。
 * 4. 多路并行，减少前后相关性，让更多机器代码能够被同步执行。高级语言代码和汇编代码都是串行的，但机器实际执行过程中很可能存在并行。
 */

//* First. 循环展开
// 计算前缀和正常循环
void prefixsum1(float a[], float p[], long int n)
{
    long int i;
    p[0] = a[0];
    for(i=1; i<n; i++)
        p[i] = p[i-1] + a[i];
}

// 循环展开：一次计算两个
void prefixsum2(float a[], float p[], long int n)
{
    long int i;
    p[0] = a[0];
    for(i=1; i<n-1; i+=2)
    {
        float mid_val = p[i-1] + a[i];
        p[i] = mid_val;
        p[i+1] = mid_val + a[i+1];
    }
}

//* Second. 循环展开(C语言并行)之后的指令级并行
// 在方法2中，先计算一个中间值再计算p[i]和p[i+1]，而在此处机器
// 可以直接并行计算p[i]和p[i+1]，从指令执行的角度来看没有前置条件。
void prefixsum3(float a[], float p[], long int n)
{
    long int i;
    p[0] = a[0];
    for(i=1; i<n-1; i+=2)
    {
        p[i] = p[i-1] + a[i];
        p[i+1] = p[i-1] + a[i] + a[i+1];
    }
}

//* Third. 内存读写
typedef struct
{
    int a;
    float f;
    double d;
}data, *data_t;

typedef struct
{
    long len;
    struct data_t *data;        // 必须加上struct关键字
}vec_rec, *vec_prt;

// 正常函数，每次计算得一个中间结果就写入进去，不断更新
void factorial1(int* dst, int n)
{
    int i;
    *dst = 1;
    // int *arr = malloc(sizeof(int)*n);
    for (i=2; i <= n; i++)
    {
        *dst = *dst * i;
    }
}

// 优化函数：先在过程栈内计算，最后再一次性写入内存（这个内存可能就在附近，也可能在堆或者其他地方而导致很慢）
void factorial2(int *dst, int n)
{
    int i;
    int result = 1;
    for(i=2; i<n; i++)
    {
        result = result * i;
    }
    *dst = result;
}