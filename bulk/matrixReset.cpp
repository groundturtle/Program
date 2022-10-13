/*
 * @Author: avert-win
 * @Date: 2022-09-30 16:26:11
 * @LastEditTime: 2022-09-30 17:15:52
 * @FilePath: \ProgramDaily\bulk\matrixReset.cpp
 * @Description: 将矩阵内含0的行和列全部置零。时间复杂度O(m*n)，空间消耗O(1)。
 * @LastEditors: avert-win
 */
#include<iostream>
#include<vector>
using namespace std;
class Solution{
    
    public:
        void setZeroes(vector<vector<int>>& matrix){
            int m = matrix.size();
            int n = matrix[0].size();
            bool firDim = false;
            bool secDim = false;
            // 查询第一行与第一列是否有0
            for(int i=0; i<m; i++){
                if(matrix[i][0]==0){
                    firDim = true;
                    break;
                }
            }
            for(int i=0; i<n; i++){
                if(matrix[0][i]==0){
                    secDim = true;
                    break;
                }
            }
            // 查找中间的0并记录在第一行和第一列中
            for(int i=1; i<m; i++){
                for(int j=1; j<n; j++){
                    if(matrix[i][j] == 0){
                        matrix[i][0] = 0;
                        matrix[0][j] = 0;
                    }
                }
            }
            // 根据第一行和第一列的信息置零
            for(int i=1; i<m; i++){
                for(int j=1; j<n; j++){
                    if(matrix[i][0] == 0 || matrix[0][j] == 0) 
                        matrix[i][j] = 0;                   
                }
            }
            // 对第一行和第一列置零
            if(firDim){
                for(int j=0; j<n; j++){
                    matrix[j][0] = 0;
                }
            }
            if(secDim){
                for(int j=0; j<m; j++){
                    matrix[0][j] = 0;
                }
            }
        }
};

int main(){
    Solution solu;
    vector<vector<int>> matrix{{1,0,3}};
    solu.setZeroes(matrix);
}