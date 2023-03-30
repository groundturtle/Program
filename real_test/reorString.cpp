/**
 * @file reorString.cpp
 * @author avert-goose (avert-goose@hnu.edu.cn)
 * @brief 腾讯笔试第二题：输入多个字符串，依次从中抽取任意一个不相同的字符顺序放置，求最多可生成的不同字符串的个数。
 *  reorString_e.cpp 为字符来源与放置位置无关的解法，依次抽取后按升序排列（去重），一个升序字符串可生成n的阶乘个不同字符串。
 * @version 0.2
 * @date 2023-03-28
 */

#include<bits/stdc++.h>
using namespace std;

unordered_set<string> str_set;

/**
 * @brief 从第一个字符串开始，层层深入查找不同字符。
 * 退出条件：1. 遍历完最后一个字符串，简化为当前字符串越界；2. 没有找到任何一个未曾出现过的字符，简化为不进入递归；
 * 深入条件：1. 找到一个此前未曾出现过的字符
 * 
 * @param strs 
 * @param level 
 * @param deepest 
 * @param result 
 */
void godeep(vector<string>& strs, vector<char>& str, int level, const int& deepest, int& result){
    // 已经越界，负责检查是否重复并更新计数，然后返回。
    if(level > deepest){        
        result++;
        return;
    }
    // 在本层寻找不重复字符
    for(auto c : strs[level]){
        // 找到一个，进入，退出和更新留给下一层处理。
        if(find(str.begin(), str.end(), c) == str.end()){           
            str.push_back(c);           // 进入前把当前字符加上
            godeep(strs, str, level+1, deepest, result);
            str.pop_back();             // 退出后清除
        }
    }
    // 本层已经找完了
    return;
}

int main(){
    int n; cin>>n;
    vector<string> strs(n);

    string tstr;
    unordered_set<char> tset;
    for(int i=0; i<n; i++){
        tset.clear();
        strs[i] = "";
        cin>>tstr;
        for(auto c : tstr){      // 字符串内部字符去重
            if(tset.count(c)){
                continue;
            }
            strs[i] += c;
            tset.insert(c);
        }
    }
    int ret = 0;
    vector<char> str;
    godeep(strs, str, 0, n-1, ret);
    cout<<ret<<endl;
}