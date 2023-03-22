#include<algorithm>
#include<vector>
#include<deque>
#include<iostream>

/**
 * vector<bool>实际上不是按bool类型的大小存储的，而是进行了压缩；
 * 中括号运算符的重载使用了代理类，因此不是标准容器。尽量不要使用。
 * vector<bool> vb(3);  
 * bool* bp = &vb[0];       // 报错；标准容器必须实现此语句。
 */
std::vector<int> vi = {1, 1, 2, 2, 3, -6};

void func(int& i){
    i = i*i;
    std::cout<<i<<" ";
}

bool cmp(const int& a, const int& b){
    return a < b;
}

bool predic(const int& x){
    return x == 4;
}

int main(){
// 1. 不要手写循环，使用算法库。
    // 逐个元素执行函数
    std::for_each(vi.begin(), vi.end(), func);      
    // 取最小值
    std::cout<<*std::min_element(vi.begin(), vi.end(), cmp)<<std::endl;    
    // 返回第一个不小于参数的元素迭代器（注意此函数要求序列必须有序，使用二分查找方法！）
    std::cout<<*std::lower_bound(vi.begin(), vi.end(), 2, cmp)<<std::endl;
    std::cout<<std::endl;

// 2. 判断是否全部或至少有元素符合条件
    std::cout<<std::any_of(vi.begin(), vi.end(), predic)<<std::endl;
    std::cout<<std::all_of(vi.begin(), vi.end(), predic)<<std::endl;
    std::cout<<std::endl;

// 3. 计算满足条件的元素数量
    std::cout<<std::count_if(vi.begin(), vi.end(), predic);
    std::cout<<std::endl;

// 4. 复制符合条件的全部元素到指定位置（必须预申请空间）
    std::copy_if(vi.begin(), vi.end(), vi.begin(), predic);  // vi后续结果不会被删除
    for(auto x : vi) std::cout<<x<<" "; std::cout<<std::endl;
}