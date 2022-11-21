/*
 * @Author: avert-win
 * @Date: 2022-10-31 21:13:02
 * @LastEditTime: 2022-10-31 21:26:02
 * @FilePath: \ProgramDaily\sample_c_cpp\for_each_auto_try.cpp
 * @Description: for_each(begin, end, func)将区域内的每个元素分别作为参数运行一次函数func。
 *      可以在函数内抛出异常，for_each不会擅自处理掉。
 * @LastEditors: avert-win
 */
#include<bits/stdc++.h>
using namespace std;

void func(int x){
    cout<<x<<"  ";
    if(x == -1){
        throw -12138;
    }
}

int arr[] = {1,2,3,4,-1};
vector<int> v = {1,2,3,4,-1};

int main(){
    try{
        for_each(arr, arr+5, func);
        cout<<endl;
        for_each(v.begin(), v.end(), func);
        cout<<endl;
    }
    catch(int i){
        printf("\ncatch %d\n", i);
    }
    // 尽管数组不能作为一个参数进行传递，但auto依然可分辨出来数组的长度。
    for(auto n : arr){
        printf("%d ", n);
        n -= 1;
    }
    cout<<endl;
    // auto可加修饰符，const或&，以达到传递引用但禁止修改、或传递引用并就地修改的目的。
    for(auto& n : arr){
        printf("%d ", n);
        n -= 1;
    }
    cout<<endl;
    for(const auto& n : arr){
        printf("%d ", n);
    }
}