#include<vector>
#include<iostream>
#include<math.h>

using namespace std;

class maxHeap{
private:
    vector<int> _vec;
    int _size; 
    void _sink(int ind);

public:
    /**
     * @brief Construct a new, empty max Heap object
     */
    maxHeap(){_size = 0;}
    /**
     * @brief Construct a new max Heap object with vector
     * @param vec
     */
    maxHeap(const vector<int>& vec);

    bool insert(int x);
    // pop the max one, without return value.
    bool pop();

    int top();
    int size(){ return _size;}
};

/**
 * 从底层开始，一层一层往上调整，实现时间复杂度O(n)的建堆。 \n 
 * 也可以不按层，去掉唯一无兄弟叶节点后直接从最后下标以2为步幅往下减。\n 
 * 自底向上处理每一层的节点；每个节点都要下沉，一路沉到底，才能保证高低有序。
 * \attention 从底部非叶节点开始逐层往上处理，每次处理过程都是往下不断沉！
 */
maxHeap::maxHeap(const vector<int>& v){
    _size = v.size();
    _vec.assign(v.begin(), v.end());
    int ind = _size/2 - 1;              // 从后往前，首个非叶子节点下标
    while(ind >= 0){
        // 下沉
        _sink(ind);
        ind -- ;
    }
}

bool maxHeap::insert(int x){
    _vec.push_back(x);
    if(!_size){         // 如果当前为首次插入，则不需要调整
        _size++;
        return true;
    }
    int p = _size;     // 最后一个数字，刚插入的
    while(p && _vec[ceil(p/2) - 1] < _vec[p]){       // p不为根节点（仍有父节点）且父节点值小于 x ，上浮
        int t = _vec[ceil(p/2) - 1];
        _vec[ceil(p/2) - 1] = _vec[p];      // x
        _vec[p] = t;
        p = ceil(p/2) - 1;      // 变当前节点为父节点
    }
    _size++;
    return true;
}

int maxHeap::top(){
    if(_size)
        return _vec[0];
    throw(exception());
}

/**
 * @brief 将指定节点往下沉，内部调用，不进行越界检测。
 * 
 * @param ind 要下沉的节点下标
 */
void maxHeap::_sink(int ind){
    int p = ind;
    while(2*p+1 < _size){        // 仍有至少一个子节点，继续下沉
        if(2*p+2 < _size && _vec[2*p+2] > _vec[2*p+1] && _vec[2*p+2] > _vec[p]){      // 有右子节点，且右子节点大于左子节点
            swap(_vec[2*p+2], _vec[p]);
            p = 2*p + 2;
        }
        else if(_vec[2*p+1] > _vec[p]){           // 左子节点大于当前节点，且没有右子节点，或者右子节点小于左子节点
            swap(_vec[2*p+1], _vec[p]);
            p = 2*p + 1;
        }
        else    
            return;         // 已经比子节点都大，无需下沉的情况也要return，否则死循环
    }
}

bool maxHeap::pop(){
    if(!_size){
        return false;
    }
    _vec[0] = _vec[_size-1];
    _vec.pop_back();
    _size--;
    _sink(0); 
    return true;
}

#include<random>

int main(){
    int n = 13;
    vector<int> test;
    for(int i=0; i<n; i++){
        test.push_back(rand() % 100);
    }
    maxHeap h(test);
    while(h.size()){
        cout<<h.top()<<" ";
        h.pop();
    }
}