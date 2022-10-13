/*
 * @Author: avert-win
 * @Date: 2022-04-18 20:36:44
 * @LastEditTime: 2022-04-18 22:14:32
 * @Description: 请填写简介
 */

/**
 * @brief 这道题名叫迷你语法分析器，要求对于输入的一个用中括号包裹的列表，
 * 生成对应的一个NestedInteger对象；每个列表可能含有任意数量的数字成员和列表成员，
 * 可以为空。每个NestedInteger类实例以整数和列表为核心，用重载的add()添加。
 */
/**
 * find_if() 和 find_if_not() 用自定义规则查找可迭代数据类型(不止string!)中的特定数据，返回迭代器，找不到则为end().
 * add()含义不明，有重载。
 * 重在理解匹配过程和栈，以及静态成员指针、迭代器、find_if()等方法和思想。
 */
#include<bits/stdc++.h>
using namespace std;


// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
public:

    // Constructor initializes an empty nested list.
    NestedInteger();

    // Constructor initializes a single integer.
    NestedInteger(int value);

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    // bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Set this NestedInteger to hold a single integer.
    void setInteger(int value);

    // !这个add()含义不明，发现其中可以传整数，也可以传一个类的对象，搞不懂。
    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
    void add(const NestedInteger &ni);

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    // const vector<NestedInteger> &getList() const;
};

class Solution {
public:

    //error: reference to non-static member function must be called
    static bool isDigit(const char& c)
    {
        return c=='-'||isdigit(c);
    }

    NestedInteger deserialize(string s) 
    {
        stack<NestedInteger> stk;
        //首先数字，然后列表。由于不递归，不会有空列表和空字符串出现，除非自己剪裁。

        //开头就是数字，说明后面没有任何元素，不可能嵌套。
        if(isDigit(s.front()))
        {
            return stoi(s);
        }

        auto iter = s.begin();

        //timeout: 由于下面有iter = inEnd = s.end()的可能，最后又进行了iter++，因此如果用不等于作为循环条件可能会出现：运行时错误，或运行时间超出限制。
        while(iter < s.end())
        {
            //如果是数字。第一个也和上面不重叠，因为上面直接返回了，且没有递归。
            if(isDigit(*iter))
            {
                auto intEnd = find_if_not(iter, s.end(), isDigit);
                if(stk.empty())
                {
                    //string(begin(), end())是通过迭代器复制字符串，代替了substr().迭代器是指针。
                    stk.push(NestedInteger(stoi(string(iter, intEnd))));
                }
                else
                {
                    //stack.top() 返回的是引用，可以直接修改；
                    stk.top().add(stoi(string(iter, intEnd)));
                }
                //处理完一个数字，就要把下次处理的开始位置从这次结束的下一位开始。
                iter = intEnd;
            }
            //如果不是数字，是列表(括号)，分开始和结束两种。
            //开头需要新建列表，并插入上一个列表中。然后如果有数字要加数字，有列表再加列表，一步一步分开处理。
            else
            {
                if(*iter == '[')
                {
                    //top()返回的是引用，但是等号是拷贝构造。
                    stk.push(NestedInteger());
                }
                else if(*iter == ']')
                {
                    NestedInteger father = stk.top();
                    stk.pop();
                    if(stk.empty())
                    {
                        stk.push(father);
                    }
                    else
                    {
                        stk.top().add(father);
                    }
                }
                // 迭代器（指针）类型也可以++，编译器有保留符号表、变量类型等。
                iter++;
            }
            // 不能在这里iter++，否则因为iter = intEnd已经对齐了逗号(那么下次直接数数字，无妨)或中括号(将会导致错过这个往回收的括号)
            // iter++;
        }
        return stk.top();
    }
};