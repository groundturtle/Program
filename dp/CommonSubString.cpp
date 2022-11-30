/*
 * @Author: avert-win
 * @Date: 2022-04-18 23:56:20
 * @LastEditTime: 2022-04-19 01:30:03
 * @Description: 最长公共子串问题，用表格，若当前格为true, 
 *      则取一条斜线上连续true的个数(包括自己)和左/上一格三者中的较大者，
 *      若当前格为false则取左/上两者中的较大者。
 *      本程序实现有缺陷，使用以上思路的正确版本时间复杂度O(m*n)、空间复杂度O(m*n)
 *      也可以使用滑窗法及使用哈希表的滑窗法，见'substring_*.cpp'文件。
 */
#include<bits/stdc++.h>

int main()
{
    std::string str1, str2;
    std::cin>>str1>>str2;

    size_t len1 = str1.length();
    size_t len2 = str2.length();

    size_t dp[len1+1][len2+1];
    bool dp_flag[len1+1][len2+1];

    for(size_t i=0; i<len1+1; i++)
    {
        for(size_t j=0; j<len2+1; j++)
        {
            dp_flag[i][j] = false;
            dp[i][j] = 0;
        }
    }       
    
    for(size_t i=1; i<len1+1; i++)
    {
        for (size_t j = 1; j < len2+1; j++)
        {
            if(str1[i-1] == str2[j-1])
            {
                dp_flag[i][j] = true;
                size_t flag = 0;
                for(; (i-flag)>0&&(j-flag)>0; )
                {
                    if(dp_flag[i-flag][j-flag])
                    {
                        flag++;
                    }
                    else
                    {
                        break;
                    }
                }
                flag = flag>1?flag:1;
                dp[i][j] = dp[i-1][j]>dp[i][j-1]?dp[i-1][j]:dp[i][j-1];
                dp[i][j] = dp[i][j]>flag?dp[i][j]:flag;
            }
            else
            {
                dp[i][j] = dp[i-1][j]>dp[i][j-1]?dp[i-1][j]:dp[i][j-1];
            }
        }
    }

    std::cout<<dp[len1][len2]<<std::endl;
    
}