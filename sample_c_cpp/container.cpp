/*
 * @Author: avert-win
 * @Date: 2022-10-27 09:33:09
 * @LastEditTime: 2022-11-17 22:24:56
 * @FilePath: \ProgramDaily\sample_c_cpp\container.cpp
 * @Description: set, map, 及其变种的特性，及迭代器的使用。
 * @LastEditors: avert-win
 */
#include<iostream>

/**
map、set等使用树结构，插入和搜索时间都是O(logn);

由于并非线性结构，set和map等结构的迭代器并不支持与整数相加减。
迭代器实际上是个被加以限制和扩展的指针，因此
    非线性结构的迭代器不会随着其它节点的插入、删除等操作而改变指向内容，
    线性结构的迭代器同样不改变指向地址，但指向的内容可能发生变化。
*/

// set 和 map 由于其有序结构(树)，无法直接修改节点的值，只能用迭代器访问；
// 修改节点的操作只能由删除和插入两个接连动作来完成。
#include<vector>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>

using namespace std;

map<int, int> m;        // 自动排序，不允许相同键
multimap<int, int> mm;  // 自动排序，相同键按顺序稳定存储

unordered_map<int, int> um;     // 哈希，不允许相同键
unordered_multimap<int, int> umm;   // 哈希，相同键按顺序稳定存储

set<int> s;        // 自动排序，不允许相同键
multiset<int> ms;   // 自动排序，稳定

unordered_set<int> us;     // 哈希
unordered_multiset<int> ums;
/* pari<Tkey, Tvalue> unordered_map::equal_range();  返回某键值对应的键值对范围*/


// vector<T>(int);  // 此种构造方式不但确定了向量的空间大小，而且可以提前使用范围内的下标索引了。

int main(){
    // 向树插入：若（键）值已经存在，旧的不会被替换，而是新的被忽略
    for(int i=3; i>=0; i--){
        m.insert({i,i});
        m.insert({i,i+1});      
        mm.insert({i,i});
        mm.insert({i,i+1});
    }
    // 删除
    m.erase(0);
    mm.erase(1);        // 一次删除全部
    // 查找
    auto it = m.find(1);
    cout<<"{"<<it->first<<", "<<it->second<<"}"<<endl;
    for(auto i : m){
        cout<<"{"<<i.first<<", "<<i.second<<"}, ";
    }
    cout<<endl;
    for(auto i : mm){
        cout<<"{"<<i.first<<", "<<i.second<<"}, ";
    }
    cout<<endl;


    vector<int> v1 = {1,2,3,4,5};
    auto v1it = v1.begin() + 1;     // 应是指向2
    v1.insert(v1.begin(), -2);      // 若就地插入（整体后移），v1it应指向1，但实际上整个vector的位置都可能发生变化，因此无法确定。迭代器失效。
    cout<<"vector::iterator was changed: "<<*v1it<<endl;

    set<int> s1{1,2,3,4};
    auto s1it = s1.begin();
    s1it++; s1it++;             //  应是指向3
    cout<<*s1it<<endl;
    s1.insert(-2);              // 逻辑上向前向后插入，都不改变迭代器指针指向的固定地址，而该地址又专属于一节点直到该节点被删除，因此迭代器始终有效。
    s1.insert(12);
    cout<<*s1it<<endl;
}