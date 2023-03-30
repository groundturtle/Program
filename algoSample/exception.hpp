#include<iostream>
#include<exception>
#include<string>

namespace my
{

class get_from_empty : public std::exception{

public:
    /**
     * @brief 重写父类what()方法，本身不会再抛出异常，且不修改变量。
     * 
     * @return const char* 
     */
    virtual const char* what(void) const noexcept override{
        return "[ERROR]: trying to get element from empty object.\n";
    };
};

class pop_from_empty : public std::exception{

public:
    /**
     * @brief 重写父类what()方法，本身不会再抛出异常，且不修改变量。
     * 
     * @return const char* 
     */
    virtual const char* what(void) const noexcept override{
        return "[ERROR]: trying to pop element from empty object.\n";
    };
};
    
}; // namespace my
