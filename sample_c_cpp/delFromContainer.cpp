/*
 * @Author: avert-win
 * @Date: 2022-10-31 21:53:16
 * @LastEditTime: 2022-10-31 22:23:48
 * @FilePath: \ProgramDaily\sample_c_cpp\deleteFromContainer.cpp
 * @Description: 各种容器的删除技巧及易错点
 *      vector、string和deque: 使用container::erase-std::remove（或remove_if）;
 *      list: 使用list::remove（或remove_if）
 *      关联容器：使用container::erase
 * @LastEditors: avert-win
 */

/**
 * 算法库中，std::remove()和std::remove_if()将序列指定范围内所有需要删除的元素移到末尾；
 *      该函数返回保留部分的end()迭代器（即需删除的第一个或空），时间复杂度O(n)；
 * 对于序列容器，使用remove()、再使用自身的成员函数erase()是最佳的，时间复杂度恒为O(n)。
 * 
 * 在删除时，尤其需要注意，基于节点的容器未被删除的节点所对应的迭代器不会失效，
 *     但是如果不慎采用了删除之后的节点的it++或it--形式，则会导致错误！
*/
#include<vector>
#include<list>
#include<algorithm>
#include<iostream>
using namespace std;

vector<int> v = {-2, -1, 0, 3, 6, 9};
bool pred(int x){
    return x < 0;
}
int main(){
    // vector::erase()只能删除整个区间，不可在区间内自动匹配删除。
    // v.erase(v.begin(), v.end(), -1);     // error: 没有与参数列表匹配的重载函数
    v.erase(remove_if(v.begin(), v.end(), pred), v.end());
    for(const auto& n : v){
        printf("%d ", n);
    }
    printf("\n");

    v.erase(remove(v.begin(), v.end(), 6), v.end());
    for(const auto& n : v){
        printf("%d ", n);
    }
}