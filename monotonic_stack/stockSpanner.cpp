/*
 * @Author: avert-win
 * @Date: 2022-11-18 11:21:32
 * @LastEditTime: 2022-11-18 11:31:25
 * @FilePath: \ProgramDaily\monotonic_stack\stockSpanner.cpp
 * @Description: 依次输入每天股票价格，在输入后立刻返回此前连续小于等于当天股价的天数（包含当天）。
 * @LastEditors: avert-win
 */

#include<bits/stdc++.h>
using namespace std;

class StockSpanner {
private:
    int index;
    stack<pair<int,int>> upIncrease;
public:
    StockSpanner() {
        index = -1;
    }
    
    int next(int price) {
        index++;
        int ret = 0;
        while(!upIncrease.empty() && upIncrease.top().second <= price)
            upIncrease.pop();
        if(upIncrease.empty())
            ret = 1;
        else
            ret = index - upIncrease.top().first;
        // 即便是已有类型的实参，仍然需要指明pair类型。 
        upIncrease.push(pair<int,int>{index, price});
        return ret;
    }
};

int main(){
    StockSpanner st = StockSpanner();
    cout<<st.next(100)<<"  ";
    cout<<st.next(10)<<"  ";
    cout<<st.next(100)<<"  ";
}