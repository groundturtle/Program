/*
 * @Author: avert-win
 * @Date: 2022-11-10 21:01:37
 * @LastEditTime: 2022-11-11 10:50:16
 * @FilePath: \ProgramDaily\bulk\nextPalindrome.cpp
 * @Description: 寻找大于等于给定数的回文素数中最小的一个数。
 *      注意这题中，使用回文根翻转映射生成回文的方法，只要寻找的是大于等于给定值的数，
 *      就无需考虑如9,99等棘手的进位问题，整个问题都得到了简化。
 *      要得到严格大于当前数的回文，只需要在传入参数时将其加一即可，其最终效果是一样的。
 * @LastEditors: avert-win
 */
#include<bits/stdc++.h>
using namespace std;

class Solution{
    bool isSymmetry(string num){
        int len = num.length();
        for(int i=0,j=len-1; i<j; i++,j--){
            if(num[i] != num[j])
                return false;
        }
        return true;
    }

    // 构造大于等于当前数的最小回文，将数字切半，加一，然后映射到右边即可（注意有最后一位共用和独享的区别，最小的肯定是共用中间位，但要保证大于原数）。
    string nextSymmetry(string num){
        if(isSymmetry(num))
            return num;
        string root = "";
        int len = num.length();
        if(len % 2)  root = num.substr(0, len/2+1);
        else root = num.substr(0, len/2);
        int rl = root.length();                 // 根的长度
        string result1, result2;
        // 奇数位 
        if(len%2){
            string ret = root;
            // 根不加一，直接翻转复制过去
            for(int i=1; i<rl; i++){                
                ret += root[rl-i-1];
            }
            if(stoi(ret) >= stoi(num))          // 令等于满足条件，则避免了如99的数进入加一阶段。
                return ret;
            // 根必须加一，否则生成数不大于原数。加一后总有效位数不变（不溢出）
            root = to_string(stoi(root) + 1);
            ret = root;
            for(int i=1; i<rl; i++){                
                ret += root[rl-i-1];
            }
            return ret;
        }
        // 偶数位，不能共用根的最后一位
        else{
            string ret = root;
            // 根不加一，直接翻转复制过去
            for(int i=1; i<=rl; i++){                
                ret += root[rl-i];
            }
            if(stoi(ret) >= stoi(num))
                return ret;
            // 根必须加一，否则生成数反而小
            root = to_string(stoi(root) + 1);
            ret = root;
            for(int i=1; i<=rl; i++){                
                ret += root[rl-i];
            }
            return ret;
        }
    }

    // 判断是否是素数
    bool isPrime(int n){        // 从k开始，则顶多与n/k相乘，不可能再多
        for(int i=2; i<=n/2; i++){
            if(!(n % i)){            // 如果可整除，则说明非素数（因i<=n/2，余数至少为2）
                return false;
            }
        }
        if(n==1)   return false;
        return true;
    }

public:

    int primePalindrome(int n){
        if(isPrime(n) && isSymmetry(to_string(n)))
            return n;
        int ret = stoi(nextSymmetry(to_string(n)));
        while(!isPrime(ret)){
            cout<<ret<<"  ";
            ret = stoi(nextSymmetry(to_string(ret+1)));       // 寻找的是大于等于的，因此要在调用时手动加一
        }
        return ret;
    }
};

int main(){
    int a = 102;
    Solution solu = Solution();
    cout<<endl<<solu.primePalindrome(a);
}