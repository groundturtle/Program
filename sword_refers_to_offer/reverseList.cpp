/*
 * @Author: avert-win
 * @Date: 2022-10-05 17:24:37
 * @LastEditTime: 2022-10-05 18:08:39
 * @FilePath: \ProgramDaily\sword_refers_to_offer\reverseList.cpp
 * @Description: 翻转链表，返回头节点。
 *      为使空间复杂度为O(1)，调转节点间的指向是最好的方法。
 *      也可以直接使用栈遍历存储再遍历替换，空间复杂度O(n)。两者时间复杂度都为O(n)。
 * @LastEditors: avert-win
 */
#include<bits/stdc++.h>
using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL){}
};

class Solution{
public:
    ListNode* reverseList(ListNode* head) {

        ListNode* prev = NULL;
        ListNode* curr = head;
        ListNode* next = curr;

        // 若使用调转指针的方法，则返回的头为原来的尾！
        // 只输出一个并非形成闭环，而是只返回了最后一个节点！
        ListNode* newHead = NULL;

        while(curr){
            // 调转方向只有这一步，其余都是更新过程中使用到的变量
            newHead = curr;
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return newHead;
    }
};