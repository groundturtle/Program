/**
 * @file rain_cut.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2023-03-18
 * @complexity:
 */

// 使用滑动窗口，在窗口左边界右移时更新结果。


#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, k;
    cin>>n>>k;
    int* t = new int[n];
    for(int i=0; i<n; i++)
        cin>>t[i];

    int ret = 0;

    // <颜色，数量>
    unordered_map<int, int> colors;
    int lp = 0;
    int nowk = 0;
    // lp = rp时长度为1，但更新计数时rp已经越界，所以又要减1
    for(int rp = 0; rp < n; rp++){
        // 右边界扩展到新颜色，要判断处理
        if(colors.find(t[rp]) == colors.end() || colors[t[rp]] == 0){     // 发现新色彩
            colors[t[rp]] = 1;
            nowk ++;
            while(nowk > k && lp <= rp){   // 超出了k，要移动左边界
                ret = max(rp - lp + 1 - 1, ret);
                colors[t[lp]] --;      // 左边界颜色计数减一
                if(colors[t[lp]] == 0)
                    nowk -- ;
                lp ++;          // 左边界右移
            }
        }
        // 旧颜色，更新计数即可
        else colors[t[rp]] ++;      // 增加颜色计数
    }
    cout<<ret;
}