/*
 * @Author: avert-win
 * @Date: 2022-10-27 11:12:04
 * @LastEditTime: 2022-11-15 22:36:45
 * @FilePath: \ProgramDaily\sword_refers_to_offer\medianFinder.cpp
 * @Description: 读取数据流，找出中位数。
 * @LastEditors: avert-win
 */
#include<bits/stdc++.h>
using namespace std;

class MedianFinder {

private:
    int size;
    multiset<int>::iterator mid, pre, next;
    multiset<int> nums;

public:
    /** initialize your data structure here. */
    MedianFinder() {
        size = 0;           // 没有初始化，造成致命错误！
    }
    
    // O(logn)
    void addNum(int num) {
        size++;
        nums.insert(num);
    }
    
    //todo: 根据num插入的位置，合理调整指针走向，从而避免每次size/2的时间消耗。
    double findMedian() {
        cout<<size<<endl;
        mid = nums.begin();
        for(int i=0; i<size/2; i++){
            cout<<"mid++: "<<i<<endl;
            mid++;
        }
        // 有偶数个，且非空，则将左指针向左一位
        if(size%2 == 0 && size){
            mid --;
            pre = mid;
            mid ++;
        }
        else
            pre = mid;
        return ((double)(*mid) + double(*pre)) / 2.0;
    }
};

int main(){
    MedianFinder finder = MedianFinder();
    finder.addNum(1);
    finder.addNum(2);
    cout<<finder.findMedian()<<endl;
    finder.addNum(3);
    cout<<finder.findMedian();
}