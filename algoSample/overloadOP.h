/**
 * @file overloadOP.cpp
 * @author avert-goose (avert-goose@hnu.edu.cn)
 * @brief 用一个二维整型矩阵类进行运算符重载示例。
 * @version 0.1
 * @date 2023-03-25
 */
#include<vector>
#include<iostream>
#include<cstring>

/**
 * @defgroup operator 运算符重载
 * @{
 * 运算符重载时，为参数声明命名空间后，调用时不需要再显式指明命名空间。\n 
 * 类的方法可以调用作用域内的该类实例（如参数）的私有成员，并不局限于调用者本身。\n
 */



namespace my
{
/**
 * 矩阵类，存储一个二维矩阵，用于重载运算符的示例学习。\n 
 * 重载的运算符包括：\n 
 * `==`: 比较矩阵大小和内部数据是否全部相等     \n 
 * `>>`, `<<`: 输入/输出流，输入多余的数据会停留在缓冲区，若缺少数据则阻塞。\n 
 */
class Matrix
{
private:
    int _d1, _d2;     // 一维，二维度数
    int *_data;        // 矩阵数据存储，涉及深拷贝时不能使用默认拷贝构造函数，否则会造成double free()

public:
    Matrix() : _d1(0), _d2(0), _data(nullptr){}
    Matrix(int d1, int d2) : _d1(d1), _d2(d2), _data(new int[d1*d2]){ 
        memset(_data, 0, d1*d2);
    }

    /**
     * @brief 拷贝构造函数，深拷贝，不能使用默认生成的。\n 
     * 初始化列表写在定义处，不在声明里。
     * 
     * @param m 
     */
    Matrix(const Matrix&);

    /**
     * @brief 移动构造函数，编译器可以自动实现，\n 
     * 一旦手动实现，默认构造函数就必须跟着手动实现。\n
     * 必须将参数对象的成员变量置为初始状态，保证不再被引用（已经被移动）。
     */
    Matrix(Matrix&&); 
    ~Matrix(){ delete[] _data; }

    /**
     * @brief 获取矩阵尺寸，返回一个长度为2的向量。
     * 
     * @return std::vector<int> 
     */
    std::vector<int> size(){
        std::vector<int> ret = {_d1, _d2};
        return ret;
    }

    /**
     * @brief 重载输出运算符，将矩阵输出。开头不进行格式化，结尾有换行。\n 
     * 
     * @return std::ostream& 返回引用，以使符号能在一个表达式中连续使用。
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix&);

    /**
     * @brief 重载输入运算符，阻塞等待足够多的输入；不会开拓空间接收输入。
     * 
     * @param os 
     * @return std::ostream& 
     */
    friend std::istream& operator>>(std::istream& is, const Matrix&);

    /**
     * @brief 赋值运算符，必须作为成员函数，且调用`=`为一个对象初始化时实际上会转为对拷贝构造函数的调用。
     * 
     * @param m 
     * @return Matrix& 
     */
    Matrix &operator=(const Matrix& m);

    bool operator==(const Matrix& m);
};

Matrix::Matrix(Matrix&& src) : _d1(src._d1), _d2(src._d2), _data(src._data){
    src._d1 = 0;
    src._d2 = 0;
    src._data = nullptr;
}

Matrix::Matrix(const Matrix& m) : _d1(m._d1), _d2(m._d2), _data(new int[m._d1*m._d2]){
    for(int i=0; i<_d1; i++){
        for(int j=0; j<_d2; j++)
            _data[i*_d1 + j] = m._data[i*_d1 + j];
    }
}

Matrix &Matrix::operator=(const Matrix& m){
    _d1 = m._d1; 
    _d2 = m._d2;
    _data = new int[_d1*_d2];
    for(int i=0; i<_d1; i++){
        for(int j=0; j<_d2; j++){
            _data[i*_d1 + j] = m._data[i*_d1 + j];
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m){
    int d1 = m._d1;
    int d2 = m._d2;
    os<<"[ ";
    for(int i=0; i<d1; i++){
        for(int j=0; j<d2; j++){
            os<<m._data[i*d1 + j]<<" ";
        }
        if(i != d1-1)
        os<<std::endl;
    }
    os<<"]";
    return os;
}

std::istream& operator>>(std::istream& is, const Matrix& m){
    for(int i=0; i<m._d1; i++)
        for(int j=0; j<m._d2; j++)
            is>>m._data[i*m._d1 + j];
    return is;
}

bool Matrix::operator==(const Matrix& m){
    if(m._d1 != _d1 || m._d2 != _d2)
        return false;
    for(int i=0; i<_d1; i++){
        for(int j=0; j<_d2; j++){
            if(m._data[i*m._d1 + j] != _data[i*m._d1 + j])
                return false;
        }
    }
    return true;
}

/**
 * @}
 */
    
} // namespace my