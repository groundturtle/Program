/**
 * @file capWays.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief n个人有最多m种不同帽子，其中每个人拥有的帽子由一个向量给出，求大家戴不同帽子出门的方法数量。
 *      保证 0<n<=10，0<m<=40，结果可能太大，对10^9+7取余后再返回。
 * @version 0.1
 * @date 2022-11-28
 * @LastEditTime 2022-11-28, 16:35
 */

//! 进行两处优化之后，目前存在栈溢出情况！

/**
 * @brief 思路：动态规划 + 使用掩码的状态压缩
 * 为降低时间复杂度，将较小的一个状态变量用掩码表示，即n，人；
 * 掩码最大值2^n-1，最小值0，有效位为1时表示该人已戴帽子，为0表示未戴帽子。
 * 外循环顺序遍历帽子，内循环遍历掩码的有效值（表示人是否已戴帽子的所有可能状态）；
 * 状态转移：
 *  外循环中的每个新变量i，表示一顶种类为i的新帽子被戴与否；
 *  若被戴，则对于每个状态（掩码mask）枚举有效位j，有
 *      dp[i][mask] = sum([dp[i-1][mask\j] for j in validBit) )，
 *  其中maks\j表示mask的第j位为1且被变为0. 式子表示将一顶新帽子发给某个新人(编号j)的方法数之和。
 *  若不戴，则有 
 *      dp[i][mask] = dp[i-1][mask]。
 *  因此每个 dp[i][mask] 的值就等于上述两式右侧之和。
 *  
 *  由于题目要求最后每个人都要有一顶帽子，因此返回值应当是 max{dp[i][2^n-1]}，即掩码全1：全部戴上了帽子。
 *  又因为dp数组在第一维的单调递增性，可以确定 max{dp[i][2^n-1]} 即为 dp[m][2^n-1]。
 */

/**
 * !本题易错点和优化点
 * 1：没有检查第j个人是否拥有该帽子；
 * 2. 将dp[][]数组的第二维大小设错。
 *      因为帽子未必顺序拥有，因此即便所有人都只有一顶帽子，第二维的大小也可能需要达到40. 
 *      同时，由于 dp[i][mask] 至少等于 dp[i-1][mask]，直接返回最后一个值即可。
 * 3. 第二点也可以用提前找出最大值来计算。由于m<=40, n<=10，因此O(m*n)时间复杂度实际上微不足道。
 *      三重循环的循环次数分别为 m, 2^n-1, n, 由于指数的存在，线性叠加的O(m*n)可以忽略。
 * 4. 对于某个人是否拥有该帽子的检查，可以提前存储为每个帽子的拥有者，以空间换时间。
 *    尽管提前存储的时间复杂度更大，但时间消耗线性叠加在指数之上，而不是相乘，这是值得的。
 */

#include<bits/stdc++.h>
using std::vector;      // c++17之后才允许一个using后跟随多个声明。
using std::cout;

class Solution{
public:
    int numberWays(vector<vector<int>>& hats){
        int n = hats.size();
        int m;      // 找到最大的帽子编号，不往后遍历，节省时间。
        for(auto& v : hats)
            m = std::max( *std::max_element(v.begin(), v.end()), m);
        int maskMax = pow(2, n) - 1;
        int dp[m+1][maskMax+1];             // 为了初始化能使整个过程以一致的方式运行，将帽子从1开始编号，保留0.
        for(int j=0; j<=maskMax; j++)
            dp[0][j] = 0;           // 第一维中的后续完全取决于前面的值，因此只需要初始化一行为0即可。
        dp[0][0] = 1;       // 初始化，使得循环到第一顶帽子时，任意一个人已经戴上帽子的方法数都是1


        // 存储每个帽子的全部拥有者，以节省时间。
        vector<vector<int>> hatToPerson(m+1);
        for (int i=0; i<n; ++i) {
            for (auto h : hats[i]) {
                hatToPerson[h].push_back(i);
            }
        }

        // 外循环：帽子
        for(int i=1; i<=m; i++){
            // 内循环：状态掩码
            for(int mask=0; mask<=maskMax; mask++){      // 从没有人戴帽子开始，到所有人都戴上
                dp[i][mask] = dp[i-1][mask];      // 新帽子不被戴的情况
                for(auto bit : hatToPerson[i]){     // 拥有新帽子的每个人，检查是否刚刚戴上一顶帽子。
                    //! 易错点：没有检查该人员是否具有该帽子。
                    if(mask & 1<<bit){       // 第bit个人未戴帽子，且具有该帽子。从后往前编号或是相反都无所谓，只要保持一致就行。只有此处用到了人的编号，因此不会出错。
                        dp[i][mask] += dp[i-1][mask ^ 1<<bit];
                        dp[i][mask] %= (int)(pow(10, 9)) + 7;
                    }
                }
            }
        }
        return dp[m][maskMax];
    }
};

int main(){
    vector<vector<int>> hats = {{3,4}, {4,5}, {5}};
    Solution solu = Solution();
    cout<<solu.numberWays(hats);
}