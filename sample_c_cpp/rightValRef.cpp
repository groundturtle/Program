/*
 * @Author: avert-win
 * @Date: 2022-11-23 19:47:46
 * @LastEditTime: 2022-11-23 21:25:37
 * @FilePath: \ProgramDaily\sample_c_cpp\rightValueReference.cpp
 * @Description: 右值引用
 * @LastEditors: avert-win
 */

/**
 * @brief 右值只能出现在赋值表达式的右边，且不能取地址；
 * 右值可以作为const引用，或者使用c++11引入的新特性：右值引用，而不能作为常规引用；
 * 可以重载函数`void f(int&)`：`void f(int&&)`，编译器能够区分并正确选择；
 * 
 * @brief 应用场景: 实现移动语义(拷贝、交换对象不用申请新的空间)、
 * 使用引用作为函数参数的返回值能节省开销（尤其涉及深拷贝时），但临时对象不能返回引用，于是使用move语义：
 *      将一个对象中的资源直接移动到另一个对象，不进行任何中间过程。
 * 
 * @brief 完美转发：保持传入和传出的变量类型相同（左值与右值、引用与复制）
 * 
 * &lambda表达式可以用`auto&&`来声明参数，
 */

#include<bits/stdc++.h>
using namespace std;

// 在测试时注意，编译器会自动生成默认构造函数和默认拷贝构造函数，
class testA{
public:
    int* arr;
    int size;
    // 为使临时对象参数可用，必须加上const或删去&。
    testA(const int& s){
        cout<<"construction."<<endl;
        arr = new int[s];
        size = s;
    }
    /** 
     * 通常拷贝构造函数的参数不只有右值，因此必须有此形式。
     * 进行深拷贝。
    */
    testA(const testA& OB){
        cout<<"copy construction."<<endl;
        size = OB.size;
        arr = new int[size];
        for(int i=0; i<size; i++)
            arr[i] = OB.arr[i];
    }
    testA &operator=(const testA& OB){
        cout<<"equality operator."<<endl;
        if(this == &OB){
            return *this;
        }
        size = OB.size;
        arr = new int[size];
        for(int i=0; i<size; i++)
            arr[i] = OB.arr[i];
        return *this;
    }
    /**
     * @brief move constructor，因为确定右值在传参之后不会再使用，因此直接移动，不必申请新的空间。
     * !若实现了move constructor，编译器会隐式删除默认拷贝构造函数，因此必须手动实现。
     */
    testA(testA&& OB){
        cout<<"move constructor."<<endl;
        this->size = OB.size;
        this->arr = OB.arr;
    }
    void print(){
        cout<<this->size<<endl;
    }
};

testA func(int& s){
    testA t(s);
    return t;
}


int main(){
    int s = 100;
    // 编译器会对这一行进行优化（最终目的只是构造一个对象），因此省略了一次拷贝。不会调用移动构造函数。
    testA OA(func(s));      
    // 使用std::move()将变量强制转化为右值，即可观察到移动构造函数的调用。
    testA OB(std::move(OA));
    // OA = func(s);
}