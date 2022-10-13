/*
 * @Author: avert-win
 * @Date: 2022-04-28 22:40:57
 * @LastEditTime: 2022-04-28 23:12:37
 * @FilePath: \ProgramDaily\dp\Fibonacci_Numbers.cpp
 * @Description: 
 *      用递归和动态规划两种方法实现斐波那契数列函数。
 *      斐波那契数列中从第三个数开始，每个数都等于其前两项和，且
 *      从第三个数开始，每个数与其后面一个数的比都接近0.618：黄金分割比例。
 *      自然界有很多斐波那契数列的实例，如蜻蜓翅膀、许多花瓣等。
 */

// size_t 类型包含在iostream中。
#include<iostream>
#include<assert.h>

/**
 * @description: 计算斐波那契数列指定项的值。
 * @param {int} n
 * @return {*} 数列中第n项的值。
 */
int fib_recur(int n)
{
    if(n==0||n==1)
        return n;
    else
        return fib_recur(n-1) + fib_recur(n-2);
}

int fib_dp(int n)
{
    int nums[n+1];
    for(size_t i=0; i<2&&i<n; i++)
    {
        nums[i] = i;
    }
    for(size_t i=2; i<=n; i++)
    {
        nums[i] = nums[i-1] + nums[i-2];
    }
    return nums[n];
}

int main()
{
    int n;
    std::cin>>n;
    // std::cout<<fib_dp(3)<<std::endl;
    // std::cout<<fib_recur(3)<<std::endl;
    assert(fib_dp(n) == fib_recur(n));
    return 0;
}