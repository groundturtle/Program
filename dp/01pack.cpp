/*
 * @Author: avert
 * @Date: 2022-03-05 20:24:21
 * @LastEditTime: 2022-03-07 02:27:05
 * @Description: 
 */

// The most important thing to understand this 0-1 Knapsack problem,
// is to write a table by hand, which is declared as array dp.
// To see the table, go https://www.javatpoint.com/0-1-knapsack-problem#:~:text=What%20is%20the%200%2F1%20knapsack%20problem%3F%20The%200%2F1,we%20have%20to%20pick%20the%202kg%20item%20completely.
// Note: there is a mistake on the website: the weight should be 3,4,5,6 according to the last one num in the table.
#include<iostream>
#include<stdio.h>

int main()
{
    int n = 0, V = 0;
    std::cin>>n>>V;
    int w[n+1];
    int profits[n+1];
    int dp[n+1][V+1];
    for(int i=0; i<=n; i++)
        for(int j=0; j<=V; j++)
            dp[i][j]=0;
    for(int i=1; i<=n; i++)
    {
        std::cin>>w[i];
    }
    for (size_t i = 1; i <= n; i++)
    {
        std::cin>>profits[i];   
    }

    //The first index of dp is the biggest index of stuffs you can pack.
    //The second index of dp is the biggest volume you can use to pack stuffs.
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=V; j++)
        {
            if(j<w[i])
                dp[i][j] = dp[i-1][j];
            else
            {
                //If you can pack it, then check whether you should pack it 
                //by comparing it with the profits,
                //which lay beyond and left in the table. 
                //(It turns out that them two should be the biggest two.)
                dp[i][j] = std::max(dp[i-1][j], dp[i-1][j-w[i]]+profits[i]);
            }
        }
    }
    std::cout<<dp[n][V];
}