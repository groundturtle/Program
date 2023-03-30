/**
 * @file catch_screen.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 输入n个目标坐标，求一个大小为[a, b]的矩形可覆盖的最大目标数。
 * @version 0.1
 * @date 2023-03-18
 * @complexity:
 */

// 在指定区域内的目标数量。考虑数组动态规划
// dp[i][j] = 以(0,0)、(i,j)为顶点的矩形内目标个数
// 递推式：
//      dp[i][j] = dp[i][j-1] + dp[i-1][j] - dp[i-1][j-1] + exist(i, j)
// ret = max(ret, dp[i][j] - dp[i][j-b] - dp[i-a][b] + dp[i-a][j-b])
// 上式错误！因为相邻行的距离为1，当a = 1时，应该可以同时打到相邻两行，因此减去的dp[][]下标应该是 i/j -a/b -1 

#include<bits/stdc++.h>
using namespace std;

const int max_x = 1000;
const int max_y = 1000;

int main(){

    int n, a, b;
    cin>>n>>a>>b;
    int** dp= new int*[max_x + 1];
    for(int i=0; i<max_x+1; i++){ 
        dp[i] = new int[max_y + 1];
        memset(dp[i], 0, (max_y+1)*sizeof(int));
    }

    int x, y;
    for(int i=0; i<n; i++){
        cin>>x>>y;
        dp[x][y] = 1;           // 初始化dp[][]，充当exist(x, y)函数
    }

    int ret = 0;
    for(int i=1; i<=max_x; i++){
        for(int j=1; j<=max_y; j++){
            // 递推式
            dp[i][j] = dp[i][j-1] +dp[i-1][j] - dp[i-1][j-1] + dp[i][j];
            // 更新返回值
            if(i > a && j > b){
                ret = max(ret, dp[i][j] - dp[i][j-b] - dp[i-a][j] + dp[i-a][j-b]);
            }
            else if(i > a){
                ret = max(ret, dp[i][j] - 0 - dp[i-a][j] + 0);
            }
            else if(j > b){
                ret = max(ret, dp[i][j] - dp[i][j-b] - 0 + 0);
            }
            else{
                ret = max(ret, dp[i][j]);
            }
        }
    }
    assert(dp[max_x][max_y] == n);

    cout<<ret;
}