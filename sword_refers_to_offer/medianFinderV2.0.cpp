/*
 * @Author: avert-win
 * @Date: 2022-11-15 22:04:44
 * @LastEditTime: 2022-11-15 22:38:24
 * @FilePath: \ProgramDaily\sword_refers_to_offer\medianFinderV2.0.cpp
 * @Description: 简介
 * @LastEditors: avert-win
 */

/**
* 维护两个指针，分别指向中位数的组成（若只有奇数个数则指向同一个数）
* 插入一个数时，利用二分法使其时间复杂度为O(logn)，再判断插入位置为指针的左边、中间或右边；
* 插入的数在原数的左边、右边或中间，会导致中位数的指针发生不同变化；但对于向量来说，永远只有两种情况：偶数个或奇数个。

* &没有办法只从数据流中取出中位数而不保存这些数据。
*/

// 以下使用vector存储数据，因此简化了指针的移动步骤，但增加了时间消耗：
//      尽管运用二分法能够在O(logn)时间里找出应插入的位置，但vector的随机插入动作时间复杂度为O(n)；
//      而set等有序容器的插入时间仅为O(logn)。


#include<bits/stdc++.h>
using namespace std;

class MedianFinder {
    size_t lp;
    size_t rp;
    size_t size;
    vector<int> dataFlow;

    void adjustPointer(){
        switch(this->size){
            case 1:
                break;
            case 2:
                rp = 1;
                break;
            // 插入后数字总量大于3: 根据奇数或偶数，调整rp或lp。
            default:
                if(size%2)      // 插完为奇数
                    lp++;
                else            // 插完为偶数
                    rp++;
        }
    }

    // 二分法查找第一个大于num的数的位置（即num的插入位置）
    int findIndex(int num){
        if(this->dataFlow.empty())             // 尚未有数，直接将新数作为第一个；切不可访问dataFlow[0]!
            return 0;
        int left = 0;
        int right = this->size - 1;
        int mid = (left + right) / 2;       // 为了使mid指向中间偏左的数，right必须为闭区间
        while(left <= right){               // 因为最终要插入的位置可能为最后一个（等于size），因此要将此处条件设为 <= ，而非 < 。
            if(dataFlow[mid] <= num){
                left = mid + 1;
            }
            else{
                right = mid - 1;                // // 错误！与上面的结束条件相作用，导致死循环！ 右闭，因如果mid是第一个大于num的数则结果应返回mid，所以此处令right = mid而非right = mid + 1。            
            }
            mid = (left + right) / 2;
        }
        return left;
    }

public:
    /** initialize your data structure here. */
    MedianFinder() {
        lp = 0;
        rp = 0;
        size = 0;
    }
    
    void addNum(int num) {
        size_t index = this->findIndex(num);
        dataFlow.insert(dataFlow.begin()+index, num);
        this->size++;
        this->adjustPointer();
    }
    
    double findMedian() {
        return (dataFlow[lp] + dataFlow[rp]) / 2.0;
    }
};


int main(){
    MedianFinder finder = MedianFinder();
    finder.addNum(1);
    finder.addNum(2);
    finder.addNum(-2);
    cout<<finder.findMedian()<<endl;
    finder.addNum(3);
    cout<<finder.findMedian();
}