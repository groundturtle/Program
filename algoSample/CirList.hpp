#include<exception>
#include<functional>

namespace my
{

/**
 * @brief 模板类内定义自身指针无需指明类型<T>
 * 
 * @tparam T 
 */
template <typename T>
class ListNode{
public:
    T val;
    ListNode* prev;
    ListNode* next;
    ListNode(T val) : val(val), next(nullptr), prev(nullptr) {}
    ListNode(T val, ListNode* prev, ListNode<T>* next) : val(val), next(next), prev(prev) {}
};

template <typename T>
class CirList{
private:
    size_t _size;
    ListNode<T>* _head;
    ListNode<T>* _tail;
public:
    CirList() : _size(0), _head(nullptr), _tail(nullptr){}

    void insert(const T& val);

    bool erase(const T& val);

    /**
     * @brief 遍历链表，每个元素使用函数 func() 处理一遍。
     * 
     * @param func void(T) 型函数。 
     * @param ahead 遍历方向。
     */
    bool traverse(std::function<void(T&)> func, bool ahead);

    size_t size();
};

template <typename T>
size_t CirList<T>::size(){
    return _size;
}

template <typename T>
void CirList<T>::insert(const T& val){
    if(!_size){     // 首次插入
        _head = new ListNode<T>(val);
        _head->next = _head;
        _head->prev = _head;
    }
    else{       // 即便此前只有一个节点，形成了自旋，也是没有问题的。
        ListNode<T>* tmp = new ListNode<T>(val, _head, _head->next);
        _head->next->prev = tmp;
        _head->next = tmp;
    }
    _size ++;
    return;
}

template <typename T>
bool CirList<T>::erase(const T& val){
    if(!_size)
        return false;
    ListNode<T>* tmp = _head;

    int i = 0;      // 转一圈找节点
    while(tmp->val != val && i < _size){       
        tmp = tmp->next;
        i++;
    }
    if(i == _size)      // 没找到节点
        return false;

    if(tmp == _head){       // 删除头节点
        // if(_head->next) || if(_size > 1)     // 因为是循环链表，所以等价。
        if(_head->prev){         // 如果有下一个节点，则要改变其prev指针。有下一节点必有上一节点。
            _head->prev->next = _head->next;
            _head->next->prev = _head->prev;
        }
        _head = _head->next;        // 无论是不是删除唯一一个元素，都不会有错，因为head = nullptr也没有问题。
        delete tmp;
        _size--;
        return true;
    }

    // 不是删除头节点，则此节点的 prev, next 必不为空
    _size--;
    tmp->next->prev = tmp->prev;
    tmp->prev->next = tmp->next;
    delete tmp;

    return true;
}

template <typename T>
bool CirList<T>::traverse(std::function<void(T&)> func, bool ahead){
    if(!_size)
        return false;
    ListNode<T>* tmp = _head;
    if(ahead){
        // 只要有一个节点存在，就可以使用while循环正确判断。
        func(tmp->val);     // 正向遍历，头节点最先处理
        tmp = tmp->next;
        while(tmp != _head){
            func(tmp->val);
            tmp = tmp->next;
        }
    }
    else{       // 逆向遍历时，把头节点（当前节点留到最后）
        tmp = tmp->prev;
        while(tmp != _head){
            func(tmp->val);
            tmp = tmp->prev;
        }
        func(tmp->val);         // 逆向遍历时，把头节点（当前节点留到最后）
    }
    return true;
}
    
}; // namespace my
