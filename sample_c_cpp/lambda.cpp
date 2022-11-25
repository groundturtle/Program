/**
 * @brief 
 * @LastEditTime: 2022-11-23 19:11:52
 */
/**
 * 1. lambda 表达式是一种内嵌式的、匿名的函数，常用于一次性使用的功能，可以减少函数、简洁代码；
 * 2. c++中不允许嵌套定义函数，使用lambda表达式可以达到类似于python中一个函数根据参数构造并返回不同函数的作用目的，见示例testA.
 * 3. lambda 可捕获的数据范围为该表达式自身所处的范围，如函数、循环。见示例testB.
 * 4. 类似于内联函数，增强了局部性（使调用者和被调用者更近
 * 范式：
 * &        [&](auto&& x){};   
 *其中'&'（引用）也可以替换成'='（复制）或具体的变量名，变量名后可加'&'，不用加'='。
*/
#include<bits/stdc++.h>
using namespace std;

/** testA
 * @brief 批量定义函数
 * 返回lambda表达式的函数，返回类型使用auto推导，实现一行代码定制函数。
 * lambda可以捕获引用的引用，但也许存在未定义行为?。
 */
auto make_function(int& x){
    return [&x](){
        cout<<x<<endl;
    };
}

/**
 * @brief lambda 表达式可捕获变量的范围
 */
void testB(){
    int x = 5;
    while(true){
        int y = 9;
        auto func = [=](){cout<<"(x, y): ("<<x<<", "<<y<<")"<<endl;};
        func();
        break;
    }
    // error: undeclared identifier 'y'; y在循环内定义，循环外部不可获取。
    auto func2 = [=](){cout<<"(x, y): ("<<x<<", "<<y<<")"<<endl;};
}

int main(){
    int x = 3;
    auto f = make_function(x);      // 传入引用、再捕获引用，则任何时刻调用lambda表达式f()所输出的x都是最新的x(在其生命周期内)。
    f();
    x = -999;
    f();

    testB();
}