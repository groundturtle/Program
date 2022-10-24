/*
 * @Author: avert-win
 * @Date: 2022-10-17 19:55:50
 * @LastEditTime: 2022-10-17 20:33:56
 * @FilePath: \ProgramDaily\bulk\listKfromEnd.cpp
 * @Description: 简介
 * @LastEditors: avert-win
 */
#include<bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* curr = head->next;
        ListNode* pre = head;
        int i = 0;
        while(curr){
            // 防止一直进入这个循环导致错误
            if(++i && i>=k)
                pre = pre->next;     // 按这种 pre = pre->next 在 pre = head 之下的写法，无法返回链表的第一个节点
            curr = curr->next;
        }
        return pre;
    }
};

int main(){
    ListNode* head = new ListNode{1};
    ListNode* curr = head;
    curr->next = new ListNode{2};
    curr = curr->next;
    // curr->next = new ListNode{3};
    // curr = curr->next;
    // curr->next = new ListNode{4};
    // curr = curr->next;
    // curr->next = new ListNode{5};
    Solution solu;
    cout<<solu.getKthFromEnd(head, 1)->val;
}