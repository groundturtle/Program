/**
 * @file stackFromscartch.cpp
 * @author avert-goose
 * @brief 用数组实现栈
 * @version 0.1
 * @date 2023-03-23
 */
#include<iostream>
#include<assert.h>
#include<cstring>

namespace my{

class stack
{
private:
    int* _arr;
    size_t _size;
    size_t _capability;
    static const int _Interval = 100;       // 一次开多少

private:
    /**
     * @brief 扩大空间，失败返回-1
     * 
     * @return  
     */
    void _increase();

public:
    stack();
    ~stack();

public:
    void clear();
    int size();
    void push(int);
    void pop();
    // int top() throw(std::out_of_range);      // c++11 depre .
    int top();
};

void stack::_increase(){
    assert(_size == _capability);
    int *tmp = new int[_size + _Interval];
    memmove(tmp, _arr, _size);
    delete[] _arr;
    _arr = tmp;
    _capability += _Interval;
    return;
}

stack::stack(){
    _arr = new int[_Interval];
    _size = 0;
    _capability = _Interval;        // 注意初始化容量不为0
}

stack::~stack(){
    delete[] _arr;
}

void stack::clear(){
    delete[] _arr;
    _arr = new int[_Interval];
    _size = 0;
    _capability = _Interval;
}

void stack::push(int x){
    if(_size == _capability)
        _increase();
    _arr[_size] = x;
    _size ++;
}

void stack::pop(){
    if(!_size){
        throw(std::out_of_range("empty stack"));
    }
        _size --;
}

int stack::top(){
    if(!_size){
        throw(std::out_of_range("empty stack"));
    }
    return _arr[_size-1];
}

int stack::size(){
    return _size;
}
    
} // namespace my