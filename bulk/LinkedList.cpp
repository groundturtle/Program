/*
 * @Author: avert-win
 * @Date: 2022-09-23 16:59:27
 * @LastEditTime: 2022-09-24 11:12:18
 * @FilePath: \ProgramDaily\bulk\LinkedList.cpp
 * @Description: 功能不完备、表头表尾皆为空的双向链表，在力扣提交测试用例只对了一半。
 *              https://leetcode.cn/problems/design-linked-list/submissions/
 * @LastEditors: avert-win
 */
#include<bits/stdc++.h>

/**
 * @brief 类定义内可嵌套其它对象；类的私有成员变量在构造函数中初始化。
 * 在链表内进行根据索引的删除、插入等操作时，可根据index与size/2的关系，
 *  来决定是从前往后遍历还是从后往前遍历,以便节省时间。
 */
class MyLinkedList {
    struct Node{
        Node* prev;
        Node* next;
        int value;
    };
    Node* head;
    Node* tail;

public:
    int size;
    MyLinkedList() {
        // head 和 tail是节点，属于链表的成员；先初始化为null，再互相指向，即可避矛盾。
        this->head = new Node{nullptr, nullptr, 0};
        this->tail = new Node{nullptr, nullptr,0};
        head->next = tail;
        tail->prev = head;
        this->size = 0;
    }
    
    int get(int index) {
        if(index >= this->size)
            return -1;
        Node* curr = head;
        for (size_t i=0; i<=index; i++)
        {
            curr = curr->next;
        }
        return curr->value;
    }
    
    // head 与 tail一样为空
    void addAtHead(int val) {
        head->next->prev = new Node{head, head->next, val};
        head->next = head->next->prev;
        this->size ++;
    }
    
    void addAtTail(int val) {
        tail->prev->next = new Node{tail->prev, tail, val};
        tail->prev = tail->prev->next;
        this->size ++;
    }
    
    void addAtIndex(int index, int val) {
        if(index > this->size)
            return ;
        if(index == this->size)
            this->addAtTail(val);
        if(index <= 0)
            this->addAtHead(val);
        if(index>0 && index<this->size)
        {
            Node* curr = this->head;
            for (size_t i=0; i<index; i++)
            {
                curr = curr->next;
            }
            curr->next->prev = new Node{curr, curr->next, val};
            curr->next = curr->next->prev;
            this->size ++;
        }
    }
    
    void deleteAtIndex(int index) {
        if(index<0 || index >= size)
            return;
        Node* curr = this->head;
        for(size_t i=0; i<index; i++)
        {
            curr = curr->next;
        }
        curr->next = curr->next->next;
        curr->next->prev = curr;
        this->size --;
    }
};

int main()
{
    MyLinkedList* linkedList = new MyLinkedList();
    linkedList->addAtHead(1);
    linkedList->addAtTail(3);
    linkedList->addAtIndex(1,2);   //链表变为1-> 2-> 3
    linkedList->get(1);            //返回2
    linkedList->deleteAtIndex(1);  //现在链表是1-> 3
    linkedList->get(1);            //返回3
}

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */