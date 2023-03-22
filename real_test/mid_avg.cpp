
/**
 * @brief 数据不断流入的过程中实时求中位数和平均数。
 *  利用multiset容器自动排序，且允许重复值，实现求中位数时只需排序、无需额外遍历。
 * 
 * 迭代器移动：
 *  - 插入大于右节点，指针同时或单独右指针右移；
 *  - 插入大于左节点，指针同时或单独左指针左移；
 * 移动一个指针还是两个指针根据移动前指针是否在一起判断。
 */
#include<bits/stdc++.h>

int sheru(double x){
    if(x - floor(x) >= 0.5)
        return ceil(x);
    return floor(x);
}

int run(){
    int n = 0; std::cin>>n;

    std::multiset<int> q;
    int size_q = 0;

    int mid = 0;
    int tmp = 0;
    std::vector<int> mids;
    std::vector<int> avgs;
    // 先输入三个，防止主循环中指针到达头尾。
    for(int i=0; i<3; i++){
        std::cin>>tmp;
        q.insert(tmp);
        ++size_q;
    }
    auto lfp = q.begin()++;
    auto rip = q.begin()++;
    // 主循环
    for(int i=1; i<n; i++){
        std::cin>>tmp;
        q.insert(tmp);
        ++size_q;
        if(lfp == rip && tmp >= *rip){
            rip++;
        }
        else if(lfp == rip && tmp < *lfp){
            lfp--;
        }
        mid = sheru( (*rip + *lfp) / 2);
    }
}