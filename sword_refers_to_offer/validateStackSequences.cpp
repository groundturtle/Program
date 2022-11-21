/*
 * @Author: avert-win
 * @Date: 2022-10-28 16:23:14
 * @LastEditTime: 2022-10-28 21:15:47
 * @FilePath: \ProgramDaily\sword_refers_to_offer\validateStackSequences.cpp
 * @Description: 给定一个入栈序列、一个出栈序列，判断后者是否可能属于前者。
 *      实现新的方法之前，首先采用最朴素的方法，分析其时空复杂度，再做判断。
 *      即便确实需要更简单的办法，往往也是从最朴素的方法中脱胎而来(例如各种组合)。
 * @LastEditors: avert-win
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> st;
        int n = pushed.size();
        for (int i = 0, j = 0; i < n; i++) {
            st.emplace(pushed[i]);
            while (!st.empty() && st.top() == popped[j]) {
                st.pop();
                j++;
            }
        }
        return st.empty();
    }
};

int main(){
    vector<int> pushed = {1,2,3,4,5};
    vector<int> poped = {4,5,3,2,1};
    Solution solu = Solution();
    if(solu.validateStackSequences(pushed, poped))
        cout<<" true ";
}