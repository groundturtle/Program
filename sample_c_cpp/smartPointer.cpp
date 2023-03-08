/**
 * @file smartPointer.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 智能指针
 * @version 0.1
 * @date 2022-12-01
 * @LastEditTime
 */

#include<memory>
#include<iostream>
using namespace std;

class A{
public:
    ~A(){cout<<"destruct B"<<endl;}
};

/** 
 * @brief 以值的形式返回一个独占式指针。
 * RVO优化: 函数返回的对象不会经构造、复制两个过程，而是直接在调用者栈上构造;
 * unique_ptr实现了move语义且编译器按照 move -> copy -> error 的顺序进行赋值;
 * 以上两点中的任意一个，都使函数可以返回一个unique_ptr类型对象而不破坏其独占性。
 */
unique_ptr<A> func(){
    unique_ptr<A> p(new A);
    return p;
}

/**
 * @brief 参数传递独占式指针。
 * 可以传递（常量）引用形式，也可以使用std::move()然后传递右值引用，
 * 不能直接传值，传值在进入函数前就已经发生错误：error: call to deleted constructor of 'unique_ptr<A>'
 */
void func2(unique_ptr<A>&& p){
    return;
}

int main(){

//1. shared_ptr
    // shared_ptr<A> pA = new A; // error: 类型错误
    shared_ptr<A> pA(new A);
    // shared_ptr<A> pB(pA);
    //! 弱指针不会影响计数，因此这个指针可能成为野指针。
    weak_ptr<A> pC(pA);     
    //& 若无其它引用，在pA.reset之后原对象就被析构；否则不会析构，直到pB被销毁。
    pA.reset(new A);    
    cout<<"reset done. "<<endl;

    cout<<"\n ------------------ \n\n";

//2. unique_ptr
    unique_ptr<A> upA(new A);
    //! 不能使用拷贝构造函数构造新的独占式指针！
    // unique_ptr<A> upB(upA);
    // 使用移动语义就可以。
    unique_ptr<A> upC = std::move(upA);
    unique_ptr<A> upf = func();

    func2(std::move(upA));

    cout<<"\n -------------------\n\n";
}