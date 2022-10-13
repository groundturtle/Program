/*
 * @Author: avert-win
 * @Date: 2022-04-29 16:23:03
 * @LastEditTime: 2022-04-29 17:22:06
 * @FilePath: \ProgramDaily\dp\MinCostPath.cpp
 * @Description: 见同名.py文件。
 */

//! 此题的关键在于边界处理！由于不正确的边界赋初值和后续处理操作，先后导致溢出(std::min无法用longlong解决溢出问题)
//! 和结果不正确(偏小)。遇到问题务必首先debug处理！以上错误至少导致浪费了我一小时！
#include<iostream>
#include<limits.h>   // <limits> 没有INT_MAX这个成员！

// 本题中，由于最初的错误的边界处理，数组cost是过大的、不必要的。
int dp(int** cost, int n)
{
    for(size_t i=1; i<=n; i++)
    {
        for(size_t j=1; j<=n; j++)
        {
            //第一行和第一列的格子只能由上面或左边走来，因此条件不一样！
            if(i==1||j==1)
                cost[i][j] = cost[i][j] + std::max(cost[i-1][j], cost[i][j-1]);
            else 
                cost[i][j] = cost[i][j] + std::min(cost[i-1][j], std::min(cost[i-1][j-1], cost[i][j-1]));
        }
    }
    return cost[n][n];
}

int main()
{
    int n;
    std::cin>>n;
    std::cout<<std::min(-1, std::min(2, INT_MAX));
    // 只能用这种方式new二维int型指针变量，然后再循环new一维数组。
    int** cost = new int*[n+1];
    for(size_t i=0; i<=n; i++)
    {
        cost[i] = new int[n+1];
    }
    for(size_t i=0; i<=n; i++)
    {
        for(size_t j=0; j<=n; j++)
        {
            if(i==0||j==0)
                // !fatal! It cause over flow in dp!
                // cost[i][j] = INT_MAX;
                cost[i][j] = 0;
            else 
                std::cin>>cost[i][j];
        }
    }
    std::cout<<dp(cost, n);
}