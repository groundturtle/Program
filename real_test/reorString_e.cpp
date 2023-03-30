#include<bits/stdc++.h>
using namespace std;

/**
 * @brief 
 * 可以先为每个字符串内部去重
 * 依次从N个字符串中抽取一个不相同的字符，然后数学方法排列。
 * 用哈希表存储提取的字符，再用哈希表存储生成的字符串。
 */

/**
 * @brief 从字符数组生成字符串
 */
string makestr(vector<char> chars){
    string ret;
    for(auto c : chars)
        ret += c;
    return ret;
}

/**
 * @brief 每一个串深入一层，提取一个与众不同的字符，当到达底层时计数加一并返回。
 */
void godeep(vector<string>& s, unordered_set<string>& substrs, vector<char>& chars, int& count, int level, int n){
    bool flag = false;
    for(auto c : s[level]){
        // 当前字符首次出现
        if(find(chars.begin(), chars.end(), c) == chars.end()){
            chars.push_back(c);
            flag = true;
            // 抽取到了，而且是最后一层
            if(level == n-1){      
                //排序
                sort(chars.begin(), chars.end());      
                string s = makestr(chars);                  // 生成
                if(substrs.find(s) == substrs.end()){           // 不重复
                    substrs.insert(s);                  // 记录生成的串，并增加计数
                    count ++;
                }                  
            }
        }
        if(flag && level != n-1){           // 找到了没到底，继续深入
            godeep(s, substrs, chars, count, level+1, n);          
        }
        if(flag){
            chars.pop_back();           // 有满足条件的字符，回溯或查找下一个字符之前将其删除，无论是不是到底
        }
        flag = false;       // 重置标志，防止无穷递归
    }
    return;
}

/**
 * @brief 计算阶乘，排序后的生成字符串乘以此函数返回值。
 * 
 * @return int 
 */
int jiecheng(int n){
    int ret = 1;
    for(int i=1; i<=n; i++){
        ret = ret * i;
    }
    return ret;
}

int func(){
    int n;
    cin>>n;
    vector<string> s(n);
    for(int i=0; i<n; i++){
        cin>>s[i];
    }
    
    unordered_set<string> substrs;
    vector<char> chars;
    int count = 0;
    godeep(s, substrs, chars, count, 0, n);

    // 子串的数量乘以长度的阶乘
    cout<<jiecheng(n)<<"  "<<substrs.size()<<endl;
    return jiecheng(n) * substrs.size();    
}

int main(){
    cout<<func();
}