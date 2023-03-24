#include<exception>
#include<vector>
#include<functional>
#include<assert.h>
#include<iostream>

namespace my
{


template <typename T>           // 需要指明这是一个类型，否则编译器无法识别这是某个类的成员或是什么。
using vecIter = typename std::vector<T>::iterator;

template <typename T>
size_t _partition(std::vector<T>& vec, size_t l, size_t r, std::function<bool(const T&, const T&)> cmp){
    T pivot = vec[r];
    size_t pit = r;
    while(l != r){          // 先在右边挖了坑，就得先从左边找东西填。
        while(cmp(pivot, vec[l]) && r > l){        // 当左边元素cmp(piv, vec[l])为真，不移动
            l++;
        }
        vec[pit] = vec[l];
        pit = l;        // 新的坑已经来到了左边
        while(!cmp(pivot, vec[r]) && r > l){       // 同样为真，右边元素就应该移动（所以为假时继续递减），这样才能交换到正确位置。
            r--;
        }
        vec[pit] = vec[r];
        pit = r;
    }
    assert(l == r);
    vec[pit] = pivot;
    return pit;         // 最终分界线
}

template <typename T>
void _quickSort(std::vector<T>& vec, int l, int r, std::function<bool(const T&, const T&)> cmp){
    int pit = _partition(vec, l, r, cmp);
    if(pit-1 > l){                  //! size_t 为 0 时 减一造成非法访问段错误！
        _quickSort(vec, l, pit-1, cmp);  
    }
    if(pit+1 < r){             
        _quickSort(vec, pit+1, r, cmp);
    }
    return;
}

template <typename T>
void quickSort(std::vector<T>& vec, std::function<bool(const T&, const T&)> cmp){
    if(vec.empty())
        return;
    _quickSort(vec, 0, vec.size()-1, cmp);
}

}; // namespace my