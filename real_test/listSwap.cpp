#include<bits/stdc++.h>

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int val) : val(val), next(nullptr){}
};

// 组内不交换！
class Solution {
public:
    /**
     * 1. 使用数组pre[3]存储前面节点的指针，cnt为当前节点索引；\n 
     * 2. 每当一个节点处理完毕，就将其地址赋给pre[cnt % 3]，然后进入下一个节点；
     * 3. 根据上一步可知，前一个节点指针在数组中的索引为 (cnt-1) % 3，以此类推，前二即为(cnt-2) % 3；\n 
     * 要另外注意负值索引问题，且最后一个节点不能赋值给pre[cnt % 3]，否则退出循环后前三结点指针丢失。
     * 
     * @param head ListNode类 
     * @return ListNode类
     */
    ListNode* reorderList(ListNode* head) {
        ListNode* ret = head;
        int cnt = 0;
        ListNode* pre[3] = {nullptr};
        while(head){
            // // 第偶数个，和前一个交换
            // if(cnt % 2 && cnt){
            //     std::swap(pre[(cnt-1) % 3]->val, head->val);
            // }
            // 第4n个，前三个和前一个交换，前二个和当前交换
            if((cnt+1) % 4 == 0 && cnt){
                std::swap(pre[(cnt-3) % 3]->val, pre[(cnt-1) % 3]->val);
                std::swap(pre[(cnt-2) % 3]->val, head->val);
            }
            if(!head->next){        // 及时终止，为最后两组三个保留指针。
                break;
            }
            // cnt=2 - 3造成负索引！
            pre[cnt % 3] = head;        // 用自己替代前三
            // pre[(cnt-3) % 3] = head;        // 用自己替代前三
            cnt ++;
            head = head->next;
        }
        // 有奇数个完整组 && 不完整组有3个人，则需要交换最后这两组：前二变当前，前一变前二，当前变前一。
        // 注意此处head已经为空，
        if(((cnt+1) / 4) % 2 && (cnt+1) % 4 == 3){
            int t = pre[(cnt-1) % 3]->val;
            pre[(cnt-1) % 3] = pre[(cnt-2) % 3];
            pre[(cnt-2) % 3]->val = head->val;
            head->val = t;
        }
        return ret;
    }
};

#include<iostream>
int main(){
    int n = 13;
    ListNode* head = new ListNode(-1);
    auto tmp = head;
    for(int i=0; i<n; i++){
        tmp->next = new ListNode(i);
        tmp = tmp->next;
    }
    Solution solu;
    solu.reorderList(head);
    tmp = head;
    while(tmp){
        std::cout<<tmp->val<<" ";
        tmp = tmp->next;
    }
}