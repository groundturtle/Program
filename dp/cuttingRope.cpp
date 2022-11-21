/*
 * @Author: avert-win
 * @Date: 2022-10-28 22:04:33
 * @LastEditTime: 2022-10-28 22:09:25
 * @FilePath: \ProgramDaily\dp\cuttingRope.cpp
 * @Description: 将数n分成至少两份，求所有分法中各份乘积的最大值。
 * @LastEditors: avert-win
 */
/*
    将n分成两份，其中一份是单独一个数j，j=(1,2,3,4,...n-2)，另一份n-j可以再分，也可以不动；
    由于至少必须分成两份，因此f(n)未必包括n，因此有 
        f(n) = max(j*f(n-j), j*(n-j)), j =1,2,3,4,5
*/
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int cuttingRope(int n) {
        vector <int> dp(n + 1);
        for (int i = 2; i <= n; i++) {
            int curMax = 0;
            for (int j = 1; j < i; j++) {
                curMax = max(curMax, max(j * (i - j), j * dp[i - j]));
            }
            dp[i] = curMax;
        }
        return dp[n];
    }
};