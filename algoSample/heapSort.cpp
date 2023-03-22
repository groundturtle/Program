#include<vector>
#include<iostream>
#include<math.h>

using namespace std;

class maxHeap{
private:
    vector<int> vec;
    int _size; 

public:
    /**
     * @brief Construct a new, empty max Heap object
     * 
     */
    maxHeap(){_size = 0;}
    /**
     * @brief Construct a new max Heap object with vector
     * @param vec
     */
    maxHeap(const vector<int>& vec);
    bool insert(int x);
    int size(){ return _size;}
    int top();
    bool pop();
};

/**
 * 从底层开始，一层一层往上调整，实现时间复杂度O(n)的建堆。 \n 
 * 也可以不按层，去掉唯一无兄弟叶节点后直接从最后下标以2为步幅往下减。
 */
maxHeap::maxHeap(const vector<int>& v){
    _size = v.size();
    vec.assign(v.begin(), v.end());
    int p = _size --;
    if(p % 2){          // 去掉无兄弟叶节点，生成满二叉树
        if(vec[p] > vec[p/2]){
            swap(vec[p], vec[p/2]);
        }
        p--;
    }
    while(p > 0){
        int pt = vec[p] > vec[p-1] ? p : p-1;
        if(vec[pt] > vec[p/2]){         // 选取大的子节点后，还要和父节点比较大小
            swap(vec[pt], vec[p/2]);
        }
        p -= 2;
    }
    // int lev = ceil(log(_size));       // 层数
    // for(int i = lev; i > 0; i++){
    //     int st = pow(2, i) - 1;              // 每层的起始节点
    // }
}

bool maxHeap::insert(int x){
    vec.push_back(x);
    if(!_size){         // 如果当前为首次插入，则不需要调整
        _size++;
        return true;
    }
    int p = _size;     // 更新前的size
    while(p && vec[p/2] < vec[p]){       // p不为根节点（仍有父节点）且父节点值小于 x ，上浮
        int t = vec[p/2];
        vec[p/2] = vec[p];      // x
        vec[p] = t;
        p = p/2;
    }
    _size++;
    return true;
}

int maxHeap::top(){
    if(_size)
        return vec[0];
    throw(exception());
}

bool maxHeap::pop(){
    if(!_size){
        return false;
    }
    vec[0] = vec[_size-1];
    _size--;
    int p = 0;
    while(2*p+1 < _size){        // 仍有至少一个子节点，继续下沉
        if(2*p+2 < _size && vec[2*p+2] > vec[2*p+1]){      // 有右子节点，且右子节点大于左子节点
            int t = vec[p];
            vec[p] = vec[2*p+2];
            vec[2*p+2] = t;
            p = 2*p+2;
        }
        else{           // 没有右子节点，或者右子节点小于左子节点
            int t = vec[p];
            vec[p] = vec[2*p+1];
            vec[2*p+1] = t;
            p = 2*p+1;
        }
    }
    return true;
}

#include<random>

int main(){
    int n = 5;
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