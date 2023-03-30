/**
 * @file priorityQ_cmp.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 优先队列的模板参数，以及运用lambda和运算符重载的自定义比较方法。
 * @version 0.1
 * @date 2022-11-29
 * @LastEditTime
 */
#include<bits/stdc++.h>
using namespace std;

/* template <typename T, typename Container=std::vector<T>, typename Compare=std::less<T>> 
class priority_queue{}; */

/**
* priority_queue<>模板第三个参数是类型而不是值（是模板参数而不是函数参数）
* 因为lambda表达式是匿名类型，必须使用decltype()获取其类型以适配模板；函数指针亦同理，需用decltype()获取其类型；
* 由于这些非标准类型并没有与之适配的默认构造函数，因此需要给构造函数传入一个该类型的实例参数，使其能在实际排序过程中调用（如函数指针，仿函数对象）。
*/ 

/**
 * @brief 自定义优先队列的比较有四种方法，如果使用的是非标准类型，则需要向构造函数传入该类型的一个实例用于排序。
 * 1. 重载结构体的运算符`<`，然后使用标准的std::less<int>，
 * 2. 仿函数，即重载一个结构体或类的圆括号，用该结构/类模仿一个函数；
 * 3. lambda表达式实例化；
 * 4. 普通函数，将函数指针类型作为模板参数、函数指针作为构造函数参数。
 * 
 * 其中2，3，4本质相同，即声明一个类型作为模板参数，然后给构造函数传入一个该类型的实例。\n 
 * 并且，在2，3，4中，传入的类型参数可以用来声明变量，因此使用无参构造函数实际上也可以。
 */

typedef std::pair<int, char>  heapElem;

//& 1. 结构体重载 < 运算符，但该结构体必须作为优先队列存储的元素才有效。
struct node{
    int x;
    node(int a){x = a;}
    bool operator<(const node& b){
        return x < b.x;
    }
};
std::priority_queue<node> Q;

//& 2. 仿函数：重载()符号。注意需要传给构造函数的是一个该类型变量（不传也行）
struct cmpfunctor{
    bool operator()(const heapElem& a, const heapElem& b)const{
        return a.first < b.first;
    }
};
cmpfunctor cmp;
std::priority_queue<heapElem, vector<heapElem>, cmpfunctor> Q1; // Q1(&cmp) 都可以，下同

//& 3. lambda表达式
auto lambdacmp = [](const heapElem& a, const heapElem& b){
    return a.first < b.first;
};          // 赋值表达式，最后要加分号
// 模板参数要使用decltype()以获取lambda表达式的非匿名类型
std::priority_queue<heapElem, vector<heapElem>, decltype(lambdacmp)> Q2(lambdacmp);

//& 4. 函数(函数指针)
bool cmpfunc(const heapElem& a, const heapElem& b){
    return a.first < b.first;
}
// 模板参数要使用decltype()将函数地址转换为函数指针的类型
std::priority_queue<heapElem, vector<heapElem>, decltype(&cmpfunc)> Q3(&cmpfunc);

int main(){
    Q1.push(make_pair(3, 'c'));
    Q2.push(make_pair(3, 'c'));
}