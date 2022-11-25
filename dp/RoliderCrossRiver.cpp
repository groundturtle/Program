/*
 * @Author: avert
 * @Date: 2022-03-08 23:41:43
 * @LastEditTime: 2022-11-24 16:30:57
 * @Description: 卒过河到B点，其中下界有马，马只走一步或不动，求过河到B点有几种方式。
 */

/**
 * It turns out that we need a long long type to restore the result.
 * All we need to solve the problem are a table and an array whose elements' type is long long int.
 * That's all.
 * 2022.03.09, 0:44
 */

#include<iostream>

int main()
{
    int B[2], horse[2];
    std::cin>>B[0]>>B[1]>>horse[0]>>horse[1];

    long long int dp[B[0]+1][B[1]+1];
    for (size_t i = 0; i < B[0]+1; i++)
    {
        for (size_t j = 0; j < B[1]+1; j++)
        {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;

    // 使用方向数组加循环，避免后续一大串if，来源于深搜/广搜。
    int dirs[9][2] = {
        {0, 0},
        {1, 2},
        {1, -2},
        {2, 1},
        {2, -1},
        {-1, 2},
        {-1, -2},
        {-2, 1},
        {-2, -1}
    };
    for(size_t i = 1; i < B[0]+1; i++)
    {
        // loop： 边界 + 全部 - 冲突
        // 被马阻拦的道路在一次循环内就要处理，以免对后续结果产生错误影响。
        for(size_t j = 1; j < B[1]+1; j++)
        {
            // 先直接判断方法数：上、左两格相加；
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
            // 再判断是否被阻拦，若阻拦直接将方法数置0。
            for(int dir=0; dir<9; dir++)
            {
                if(i==horse[0]+dirs[i][0]&&j==horse[i]+dirs[i][1])
                {
                    dp[i][j] = 0;
                }
            }
        
        }
    }
    std::cout<<dp[B[0]][B[1]];
}