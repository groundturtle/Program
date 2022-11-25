/**
 * @file jobAssignment.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 任务分配问题
 *    n个人，n个任务，每个人最多完成一个任务且每个任务必须被一个人独立完成，
 *    给定i完成任务j的代价cost[i][j]，求完成全部任务的最小代价。1 <= n <= 10
 * @version 0.1
 * @date 2022-11-24
 * @lasteditdate 2022-11-25
 */

/**
 * 思路：动态规划，进行状态压缩
 *  用一个整型掩码`mask`表示哪些人已经领到了任务，建立数组dp[i][mask]，每个元素都表示将前i个任务按该方法（mask）分发出去的代价。
 *  顺序将任务发出， 为每一个任务建立一个代价集合set，将满足以下三个条件的所有dp数组元素（代价）加入集合:
 *      dp[i-1][mask_0], dp[i][mask], mask\j = mask_0（将mask的二进制表示中第j位为1，且改为0之后等于mask_0）
 *  集合中的数分别加上各自的cost[j][i]，然后集合中的最小值即是当前状态（领任务的人）、当前分配任务数的最小代价。
 * 
 * 以上算法不关心人与任务对应关系，只关心哪些人领到了任务、哪些任务已发出，以及它们对应的最小代价；
 * 一旦确定前述三个因素，只需要将新任务i分发给新人j，并针对i-1种任务的(全部)分配方法穷举j即可，只需要知道旧任务在旧人之间分配，具体如何分配并不需要关心。
 */

#include<bits/stdc++.h>
using namespace std;

/**
 * @step
 * 1. 根据数据大小，定义掩码的上限(2^n-1)；
 * 2. 声明dp数组，并初始化首个元素；任务标号从11开始。
 * 3. 开始遍历，分发任务，并记录dp[i][mask]；具体步骤如下：
 *      a. 穷举j，将mask中的第j位（1）变成0（下次恢复）得到mask_0;
 *      b. 取dp[i][mask] = min(dp[i-1][mask_0] + cost[j][i], dp[i][mask])
 */
int minimumCost(int n, vector<vector<int>>& cost){
    int maskMax = pow(2, n) - 1;
    int dp[n+1][maskMax+1];
    // 初始化，除（0，0）外应全部初始化为INT_MAX（不可采纳的值）。
    for(int i=0; i<=n; i++){
        for(int j=0; j<=maskMax; j++)
            dp[i][j] = INT_MAX;
    }
    dp[0][0] = 0;
    for(int i=1; i<=n; i++){       //  对于每个任务
        for(int mask=0; mask<=maskMax; mask++){     //  存储每个状态（领到任务人群）的最小消耗
            for(int j=0; j<n; j++){                    //  检查第j位是否为1，是1则变为0并用于递推（取最小值）
                if(mask & (1<<j)){
                    dp[i][mask] = min( dp[i-1][mask ^ (1<<j)] + cost[j][i-1],  dp[i][mask]);        // 注意dp中任务从1开始编号，但cost中任务从0开始编号
                    // cout<<i<<" "<<j<<" "<<mask<<" "<<(mask^(1<<j))<<endl;
                }
            }
        }
    }
    return dp[n][maskMax];          // 最后一定是将全部任务发出、全部人都接收到了一个任务（掩码有效位全为1）
}

int main(){
    // vector<vector<int>> cost = {{250,400,350}, {400,600,350}, {200,400,250}};
    vector<vector<int>> cost = {{90,75,75,80},{35,85,55,65},{125,95,90,105},{45,110,95,115}};
    cout<<minimumCost(cost.size(), cost);
}