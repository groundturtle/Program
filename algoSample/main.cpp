/**
 * @file main.cpp
 * @author avert-goose (avert-goose@hnu.edu.cn)
 * @brief 测试堆，栈，双向队列，循环列表，快速排序
 * @version 0.1
 * @date 2023-03-25
 */
#include<iostream>
#include<random>

#include"heapSort.cpp"
#include"stackFromArr.hpp"
#include"deQueue_1.hpp"
#include"CirList.hpp"
#include"quickSort.hpp"

int n = 9;

void testHeap(){
    cout<<"\ntest heap: \n";
    vector<int> test;
    for(int i=0; i<n; i++){
        test.push_back(rand() % 100);
    }
    // 从向量构造大顶堆
    my::maxHeap mh(test);
    while(mh.size()){
        cout<<mh.top()<<" ";
        mh.pop();
    }
    std::cout<<std::endl;
    return;
}

void testStack(){
    cout<<"\ntest stack: \n";
    my::stack st;
    for(int i=0; i<n; i++){
        st.push(i);
    }
    for(int i=0; i<n; i++){
        std::cout<<st.top()<<" ";
        st.pop();
        if(i == n/2){
            st.clear();
            for(int j=0; j<n/2+1; j++){
                st.push(j - 100);
            }
        }
    }
    std::cout<<std::endl;
    return;
}

void testDeQueue(){
    cout<<"\ntest double queue: \n";
    my::deQueue<int> dq;
    for(int i=1; i<n; i++){
        dq.push_back(i * 2);
        dq.push_front(i * -2);
        // dq.pop_front();
    }
    while(!dq.empty()){
        // cout<<dq.front()<<" ";
        // dq.pop_front();
        cout<<dq.back()<<" ";
        dq.pop_back();
    }
    std::cout<<std::endl;
}

void lst_func(int& val){
    std::cout<<val<<" ";
    // val *= -2;
}

void testCirList(){
    std::cout<<"\ntest circular list: \n";
    my::CirList<int> lst;
    for(int i=0; i<n; i++){
        lst.insert(i * 2);
    }
    lst.erase(0);
    lst.traverse(lst_func, true);
    lst.erase(2);
    lst.erase(3);       // 删除不存在的
    lst.erase(12);
    std::cout<<"\nerase 2, 3(not exists), 12 and reverse:\n";
    lst.traverse(lst_func, false);
    std::cout<<std::endl;
}

void printVec(const std::vector<int> v){
    for(auto x : v)
        std::cout<<x<<" ";
    std::cout<<std::endl;
}

// 整型比较函数
bool cmpInt(const int& a, const int& b){
    if(a <= b)
        return true;
    return false;
}

void testQuickSort(){
    std::cout<<"\ntest Quick Sort:\n";
    std::vector<int> v;
    for(int i=0; i<n; i++)
        v.push_back(rand() % 30);
    //! 函数指针和std::function、lambda之间无法自动转换！
    // my::quickSort(v, [](const int& a, const int& b){return a < b;});
    my::quickSort(v, std::function<bool(const int&, const int&)>(cmpInt));
    printVec(v);
}

int main(){
    testHeap();
    testStack();
    testDeQueue();
    testCirList();
    testQuickSort();
    return 0;
}