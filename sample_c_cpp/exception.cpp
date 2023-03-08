/**
 * @file exception.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-11-28
 * @LastEditTime
 */

#include<bits/stdc++.h>
using namespace std;

// 可以在函数声明中指定函数异常时抛出指定类型的异常，在函数实现中抛出的异常类型必须与此相符；
// 如果执意要抛出一个声明中不允许的类型对象，则程序运行到此时终止。编译期并不能检查出来。

// int func() throw(int, double, int*) { 
int func(){ 
    int* x;
    // throw(x);
    // throw(1.2);
    // throw(10);      // 抛出的对象必须可复制，因此不能是数组、函数等。
    // throw('c');
    // throw(std::bad_alloc());
    throw(std::bad_cast());
}

int main(){
    try{
        func();
    }
    catch(int x){
        cout<<"an int exception caught: "<<x<<endl;
    }
    catch(double x){
        cout<<"a double exception caught: "<<x<<endl;
    }
    catch(char c){
        cout<<"a char exception caught: "<<c<<endl;
    }
    // 捕捉标准库中异常类型（exception是所有异常类的基类）
    catch(exception& e){
        cout<<e.what()<<endl;
    }
    // 检测任意异常，无法捕获对象，但可以提供最后一层保障。
    //! 若用此方法，必须终止程序或跳转到其它部分进行后续处理，切不可忽视！
    //! 也可以将异常再抛出：直接throw。
    catch(...){
        cout<<"what?"<<endl;
        throw;              // 将刚捕获到的异常原样抛出！
    }
}