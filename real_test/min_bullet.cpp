/**
 * @file min_bullet.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 拼多多，子弹攻击，A打两目标、一血，B秒杀一目标
 * @version 0.1
 * @date 2023-03-18
 * @complexity:
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 先用A弹攻击血量为1的两个，保证有赚，然后更新血量，再重复；
 * 只剩1个1血量，依然可以用A攻击，如果有一个2血的可能有赚，至少不亏；
 * 
 * 在每次更新血量的过程中，只要扫描到两个1血就可以直接更新了，不需要等待下一次扫描。
 */

void getinput(vector<int>& blood, int n){
    for(int i=0; i<n; i++)
        cin>>blood[i];
}

// 处理逻辑
void fire(vector<int>& blood, int n, int& result){
    int last_1b = -1;
    int ptr;
    bool get1b = false;
    for(ptr=0; ptr<n; ptr++){
        if(blood[ptr] == 1){
            // 两个1血，刷新血量
            if(get1b){
                blood[last_1b] = 0;
                blood[ptr] = 0;

                get1b = false;
                result++;
            }
            // 一个1血
            else{
                last_1b = ptr;
                get1b = true;
            }
        }
    }
    // 还有单独一个1血
    if(get1b){
        for(ptr=0; ptr<n; ptr++){
            if(blood[ptr] == 2){        // 找到2血，射击，2血变1血继续寻找。
                blood[ptr] = 1;
                blood[last_1b] = 0;
                last_1b = ptr;
                get1b = true;
                
                result++;
            }
        }
    }

    // 没有1血
    for(int j=0; j<n; j++){
        if(blood[j] != 0)
            result++;
    }
}

int main(){
    int t, n;
    cin>>t>>n;
    vector<int> blood(n);

    int result = 0;
    for(int i=0; i<t; i++){
        result = 0;
        blood.clear();
        getinput(blood, n);
        fire(blood, n, result);
        cout<<result<<endl;
    }
}