/*
 * @Author: avert-win
 * @Date: 2022-04-29 08:52:30
 * @LastEditTime: 2022-06-29 18:37:59
 * @FilePath: /ProgramDaily/sample_c_cpp/ptr_array_const.cpp
 * @Description: spiral rule can solve almost anything of C and C++, 
 * see https://c-faq.com/decl/spiral.anderson.html#:~:text=%20There%20are%20three%20simple%20steps%20to%20follow%3A,Always%20resolve%20anything%20in%20parenthesis%20first%21%20More%20
 */
#include<iostream>
#include<stdio.h>

// C语言标准中，允许定义一个非标准类型（不完整类型），用于扩展结构体，
// 在C语言中可以避免大量花里胡哨指针的使用。在C++中已经没有存在的必要，vector
struct test
{
    int a;
    float f[];
};

// pointer-to-typeT is different to array-of-typeT. But, when talking function
// and fucntion's parameters, `int arr[]` is equal to `int *arr`.
void f(char* a){ a = "char array";}
void f_(char a[]){ a = "char array";}  // They are actually the same in compiler's opinion.

// sizeof() operated in compile time, so it cannot detect lenght by malloc() and new(),
// but it does know the length of an array(remember that function never get array fom params)
char sc[] = "size";
const char *sc_ = "size";

int main()
{
    char* _sc_ = new char[7];
    printf("%ld\n", sizeof(sc));        // size of array(including an ending '\0')
    printf("%ld\n", sizeof(sc_));       // size of pointer
    printf("%ld\n", sizeof(_sc_));      // size of pointer

    // cost不是int**型;
    int n = 3;
    int cost[n+1][n+1];

    // 初始化二维数组：用new int型指针数组的方式来返回一个int**型地址，之后再循环new n次一维数组。
    int** d = new int*[n];
    
    // 创建数组时，必须指定除了第一维以外的所有维度大小.
    int a[][2] = {{1, 2}, {3, 4}};
    int b[][2] = {1, 2, 3, 4};            // compiler can know that what's gg[1].

    // Variable b has types of pointers array: (int*)[2], so only this way is right.
    int* c[2] = {new int[2], new int[2]};

    test struct1{3};
    printf("struct test.f = %d\n", *struct1.f);
    
    char chararray[] = "Memory Layout";
    char *chars1 = "Memory Layout";
    chararray[1] = 'E';
    // chars1[1] = 'E';             // Segmentation fault(core dumped)
}