/*
 * @Author: avert-win
 * @Date: 2022-11-14 20:39:04
 * @LastEditTime: 2022-11-14 20:40:10
 * @FilePath: \ProgramDaily\dp\countBits.cpp
 * @Description: 给定正整数n，计算[0,n]中每个整数的二进制表示中包含1的个数，返回一个数组。
 * 
 * @LastEditors: avert-win
 */

#include<bits/stdc++.h>
using namespace std;

/*
    对于单个数的判断，利用 x & (x - 1)，最多耗时32（移位稳定耗时32）；
    由于n为int型，因此O(logn)实际上就是32，因此使用朴素的算法时间复杂度为O(n*logn)。

    动态规划方法
    法一：最低有效位
        一个数右移一位之后含1的个数，加上移出那一位中1的个数；
        由于答案需要使用一个数组存储，并且动态规划所需要保存的信息与答案相同，因此空间复杂度可记为1.
    法二：最高有效位
        与法一类似，在遍历过程中记录当前最高有效位b（当前数为i, i<2^b && i>=2^(b-1)），令i-2^(b-1)即去掉了最高有效位，则i含有的1的个数为1加上该差所含有的1个个数。
        由于从小到大遍历，且2^(b-1)大于0，因此i-2^(b-1)中所包含的1的个数已知。 
*/
class Solution {
public:
    // 法一
    vector<int> countBits(int n) {
        vector<int> ans;
        ans.push_back(0);
        for(int i=1; i<=n; i++){
            ans.push_back(ans[i>>1] + i%2);
        }
        return ans;
    }

    // 法二
    vector<int> countBits(int n){
        vector<int> ans;
        ans.push_back(0);
        int highestOne = 1;         // 2的0次方，应初始化为1，不要被名字迷惑
        for(int i=1; i<=n; i++){
            if(i == 2*highestOne){           // 最高有效位发生变化
                highestOne *= 2;
                ans.push_back(1);
                continue;
            }
            else{
                ans.push_back(ans[i-highestOne] + 1);
            }
        }
        return ans;
    }
};