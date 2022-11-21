/*
 * @Author: avert-win
 * @Date: 2022-11-21 18:16:33
 * @LastEditTime: 2022-11-21 18:46:59
 * @FilePath: \ProgramDaily\monotonic_stack\trapWater.cpp
 * @Description: 给出一串连续放置的不透水柱子高度，求该串柱子在侧面不漏水的情况下可接住多少雨水。柱子宽度为1.
 * @LastEditors: avert-win
 */

#include<bits/stdc++.h>
using namespace std;

/**
* 思路
* 一：观察图片，很容易得知需要先找出所有顶峰，然后在相邻两两之间取较低的，中间就是盛水的地方。
* 二：又或者找出低谷，然后该处所能盛水的高度，就是两侧最高点中较低的高度。非最低处亦是如此。注意若两侧最高点中只要有其一不比自身高，则该点不能盛水。

显然采用思路二更利于编程，因此设计程序，以顺序遍历、寻找右侧最高点为例：
    使用递减单调栈；由于同侧的较高关系可以传递(如a,b,c连续放置，若a>b, b>c, 则a>c)，因此只需要为每个元素找下一个更高，最后再进行一次逆向传导即可。
    然后，对于每一个点，根据以上两步形成的记录，取两者中较低者、与自身高度相减即为该点的盛水量。
*/

/**
* 对以上算法进行优化，首先考虑空间复杂度降到O(1)
    &左边最大和右边最大可以使用动态规划而非单调栈，因此去掉了单调栈的空间消耗；
    &利用滚动数组，可将两个数组去掉其一；
    &再利用返回值不计入空间消耗，即可去掉另一个数组。
    最终空间复杂度为O(1)。
*/

class Solution {
private:
    // 找出每个点的某一侧最高点的下标，若无高于自身的点，则赋予-1（初始化）. 第二个实参为true时寻找右侧最高点，否则向左侧寻找。
    vector<int> onesideBiggest(vector<int>& height, bool right){
        int n = height.size();
        vector<int> ret(n,-1);
        stack<int> decre;
        // 找右侧最高
        if(right){
            // 先找右侧下一个更高
            for(int i=0; i<n; i++){
                while(!decre.empty() && height[decre.top()] < height[i]){    // 等高不满足条件，应留在栈中。
                    ret[decre.top()] = i;
                    decre.pop();
                }
                decre.push(i);
            }
            // 再逆向传导，找出右侧最高。
            for(int i=n-1; i>=0; i--){
                // 为防止最高点将其余点导向-1(以下第二行)，将-1改为自身。
                if(ret[i] == -1)    ret[i] = i;
                else    ret[i] = ret[ret[i]];
            }
        }
        // 寻找左侧最高点
        else{
            // 先找左侧下一个更高
            for(int i=n-1; i>=0; i--){
                while(!decre.empty() && height[decre.top()] < height[i]){    // 等高不满足条件，应留在栈中。
                    ret[decre.top()] = i;
                    decre.pop();
                }
                decre.push(i);
            }
            // 再逆向传导，找出右侧最高。
            for(int i=0; i<n; i++){         // 终止条件设置错误，导致越界
                // 为防止最高点将其余点导向-1(以下第二行)，将-1改为自身。
                if(ret[i] == -1)    ret[i] = i;
                else    ret[i] = ret[ret[i]];
            }
        }
        return ret;
    }

public:
    int trap(vector<int>& height) {
        // 获取每个点左右两侧最高点的下标
        vector<int> rightBiggest = onesideBiggest(height, true);
        vector<int> leftBiggest = onesideBiggest(height, false);
        // 遍历，计算每个点的盛水量。
        int sum = 0;
        for(int i=0; i<height.size(); i++){
            // 两侧最高点中的最低点与当前点高度差，等于当前点盛水量。
            sum += min(height[rightBiggest[i]], height[leftBiggest[i]]) - height[i];    
        }
        return sum;
    }
};

int main(){
    Solution solu = Solution();
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout<<solu.trap(height);
}