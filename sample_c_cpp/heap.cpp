/*
 * @Author: avert-win
 * @Date: 2022-10-26 11:28:28
 * @LastEditTime: 2022-10-26 21:55:42
 * @FilePath: \ProgramDaily\sample_c_cpp\heap.cpp
 * @Description: c++算法库<algorighm>中堆接口的使用。
 *      在c++中，优先队列priority_queue只能访问最大值，即一种最大堆。
 *      若需要最小堆，只需将相关数全部取反再存入，取出时重新取反即可（但负数需考虑取反后溢出）。
 * @LastEditors: avert-win
 */
/**
 * 堆：满足父节点一定大于/小于子节点的完全二叉树（兄弟节点无约束）。
 * 完全二叉树可用线性数组来实现，下标为n的节点，其子节点下标一定是2n+1和2n+2（如果未越界）。
 *      删除：一定是删除根节点（否则使用堆无意义），然后将尾部节点补上来，再逐步下沉；
 *      插入：插入节点时，插入到尾部，然后上浮（即不断与父节点比较、替换，直到满足约束）；
 *      建堆：将每个新节点插入，然后下沉即可。
 * 堆的删除和插入操作时间复杂度与下沉/上浮相同，都是O(logn)，
*/
#include<algorithm>     // heap
#include<vector>
#include<iostream>
using namespace std;

// 定义通用比较规则
bool cmp(int a, int b){
    if(a > b)
        return true;
    return false;
}

int main(){
    vector<int> v1 = {1,2,3,-5,9};

    // make_heap()将容器就地转化为堆
    make_heap(v1.begin(), v1.end(), cmp);

    // push_heap()在确保原容器已经是堆的前提下，在末尾加入一个数字后，重新排序（上浮）。
    v1.emplace_back(-2);
    push_heap(v1.begin(), v1.end(), cmp);

    // pop_heap()将最大值删除并重新排序，与插入不同，删除需在排序完成后再手动执行（比直接删除然后重新建堆更快）
    pop_heap(v1.begin(), v1.end(), cmp);
    v1.pop_back();

    for(auto n : v1)
        cout<<n<<"  ";

}