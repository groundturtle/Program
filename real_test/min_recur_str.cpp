
/**
 * @file min_recur_str.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 美团，最多改变两个字符，使为回文串且字典序最小
 * @version 0.1
 * @date 2023-03-18
 * @complexity:
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 首先判断是不是回文字符串，
 * 若是则可以直接修改第一个非a字母；
 * 若不是，则有两种情况，
 * 1. 找到不对称的地方，并将这两个对称位置的字符都修改成a。
 * 2. 找到不对称的两组，分别为每组选择更改头为尾，或者更改尾为头。使用ASCII比较。
 */

int main(){

    string s;
    cin>>s;
    int len = s.length();
    int not_a = -1;
    int bad[2];
    int bad_count = 0;
    for(int i=0; i<=len/2; i++){
        int j = len - i - 1;
        if(s[i] != s[j]){
            bad[bad_count] = i;
            bad_count ++;
        }
        if(not_a == -1 && s[i] != 'a')
            not_a = i;
    }
    // 已经是回文，把第一组非'a'改成'a'
    if(bad_count == 0){
        s[not_a] = 'a';
        s[len - not_a - 1] = 'a';
    }
    // 有一组不同，可以选择更改这组两个，也可以只更改一个（若本身为'a'）
    // 但剩余的一次操作机会不足以做任何事情。
    if(bad_count == 1){
        if(s[bad[0]] == 'a'){

        }
        s[bad[0]] = 'a';
        s[len - bad[0] - 1] = 'a';
    }
    else for(int i=0; i<2; i++){
        if(s[bad[i]] < s[len - bad[i] - 1])
            s[len - bad[i] - 1] = s[bad[i]];
        else
            s[bad[i]] = s[len - bad[i] - 1];
    }
    cout<<s;
    return 0;

}