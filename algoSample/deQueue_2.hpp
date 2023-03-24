/**
 * @file queue.hpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 用数组实现双向队列
 * @version 0.2 头尾指针皆为指向实处，首次插入时需额外判断。
 * @date 2023-03-23
 */
#include<iostream>
#include<assert.h>

namespace my{

static const size_t InitCapa = 2;       // 初始化容量

/**
 * @brief 使用循环数组实现的双向队列，队满时扩容，不回收空间；\n 
 * front和rear皆为实，先移动指针后赋值；队列为空时属于例外情况，需加额外判断。
 */
template <typename T>
class deQueue
{
private:
    T *_data;        
    int _size;
    size_t _capacity;
    size_t _frontIdx, _rearIdx;    // 头指针为虚（先赋值后移动），尾指针为实（先移动后赋值）。
    static const size_t IncreFactor = 2;        // 扩容因子

public:
    deQueue();
    ~deQueue();

public:
    int size();
    /**
     * @brief 返回队列中元素的引用，允许修改。未加const修饰的对象将调用此函数。
     * 
     * @return T& 
     */
    // T& back();
    // T& front();
    /**
     * @brief 获取队列中的元素的引用，不能进行修改，函数内部亦不对队列进行修改。
     * \n const 修饰的对象将调用此函数。
     * @return const T& 
     */
    const T& back() const;
    const T& front() const;
    void push_front(const T&);
    void push_back(const T&);
    void pop_front();
    void pop_back();
    void clear();

    bool empty();

    /**
     * @brief 将队列的容量扩大为 n 
     */
    void resize(size_t n);
};

template <typename T>
int deQueue<T>::size(){
    return _size;
}

template <typename T>
deQueue<T>::deQueue(): _size(0), _capacity(InitCapa), _frontIdx(0), _rearIdx(0){
    // _size = 0;
    // _capacity = InitCapi;
    _data = new T[InitCapa];
}

template <typename T>
deQueue<T>::~deQueue(){
    delete[] _data;
}

/**
 * 开辟新的空间，复制数据，释放旧空间，然后将数据指针指向新空间并更新头尾索引。
 */
template <typename T>
void deQueue<T>::resize(size_t n){
    T *tmp = new T[_capacity * IncreFactor];
    for(int i=0; i<_size; i++){
        tmp[i] = _data[_rearIdx];
        _rearIdx = (_rearIdx + 1) % _capacity;
    }
    delete[] _data;
    _data = tmp;
    // 新的尾部在数组头部
    _rearIdx = 0;
    _frontIdx = _size - 1;
    _capacity *= 2;
}

template <typename T>
void deQueue<T>::pop_front(){
    if(!_size)
        throw(std::out_of_range("pop from empty queue"));
    _frontIdx = (_frontIdx + _capacity - 1) % _capacity;
    _size --;
}

template <typename T>
void deQueue<T>::pop_back(){
    if(!_size)
        throw(std::out_of_range("pop from empty queue"));
    _rearIdx = (_rearIdx + 1) % _capacity;
    _size --;
}

/**
 * @brief 插入前，判断是否需要扩容；先更新索引后插入，即不改变当前位置。\n
 * 为避免留下空位，需要额外判断是否是第一个插入则，若是则就地插入，不移动指针。
 */
template <typename T>
void deQueue<T>::push_back(const T& val){
    if(!_size){
        _data[_rearIdx] = val;
        _size ++;
        return;
    }
    if(_size == _capacity - 1)     
        resize(_capacity * IncreFactor);
    _rearIdx = (_rearIdx + _capacity - 1) % _capacity;
    _data[_rearIdx] = val;
    _size ++;
}

template <typename T>
void deQueue<T>::push_front(const T& val){
    if(!_size){
        _data[_frontIdx] = val;
        _size ++;
        return;
    }
    if(_size == _capacity - 1)
        resize(_capacity * IncreFactor);
    _frontIdx = (_frontIdx + 1) % _capacity;
    _data[_frontIdx] = val;
    _size ++;
}

template <typename T>
const T& deQueue<T>::back() const{
    if(!_size)
        throw(std::out_of_range("get from empty queue"));
    return _data[_rearIdx];
}

template <typename T>
const T& deQueue<T>::front() const{
    if(!_size)
        throw(std::out_of_range("get from empty queue!"));
    return _data[_frontIdx];
}

template <typename T>
void deQueue<T>::clear(){
    delete[] _data;
    T* tmp = new T[InitCapa];
    _data = tmp;
    _size = 0;
    _capacity = InitCapa;
    return;
}

template <typename T>
bool deQueue<T>::empty(){
    return _size == 0;
}

};  // namespace my