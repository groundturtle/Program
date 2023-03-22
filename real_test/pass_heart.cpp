/**
 * @file pass_heart.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 给出选手得分、要求淘汰和晋级的人数的区间（共享），求分数线。
 *  满足要求的分数线不存在返回1，存在多个则返回最小值。
 * @date 2023-03-15
 * @complexity:
 */

/**
 */

#include<bits/stdc++.h>
using namespace std;


/**
 * @brief Get the Input object
 * 
 * @param n 
 * @param x 
 * @param y 
 * @param score 存储分数的指针，在函数内new赋值，因此需要传引用。
 */
void getInput(int &n, int &x, int &y, int *&score){
    cin>>n>>x>>y;
    score = new int[n];
    for(int i=0; i<n; i++){
        cin>>score[i];
    }
}


/**
 * @brief 排序，取中位数，往两边找不同的值，看是否有一种划分满足条件。
 *  如果向左有满足条件的，记录并继续向左，向右则不需要，因为求的是最小分值。
 */
int run(int &n, int &x, int &y, int *score){
    int result = -1;
    if(2*x > n || 2*y < n)      // 人数太少或太多，不可能在区间内
        return -1;
    sort(score, score+n);
    int mid_pl = n / 2;
    int mid_pr = (n+1) / 2;
    while((mid_pl+1) >= x && (n-mid_pl-1) <= y && mid_pl >= 0){
        if( score[mid_pl] != score[mid_pr] && (mid_pl+1) >= x && (n-mid_pl-1) <= y){
            result = result==-1 ? score[mid_pl] : min(result, score[mid_pl]);
        }
        mid_pl -- ;
    }
    mid_pl = n / 2;
    while(mid_pr+1 >= x && n-mid_pr-1 <= y && mid_pr < n){
        if( score[mid_pr] != score[mid_pl] && mid_pr+1 >= x && n-mid_pr-1 <= y){
            result = result==-1 ? score[mid_pr] : min(result, score[mid_pr]);
            break;
        }
        mid_pr ++;
    }
    return result;
}

int main(){
    int n, x, y;
    int *score = NULL;
    getInput(n, x, y, score);
    cout<<run(n, x, y, score);
}