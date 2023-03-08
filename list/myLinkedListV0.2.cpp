/**
 * @file myLinkedListV0.2.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 实现以下接口的双向链表。
 * @version 0.2
 * @date 2022-12-02
 * @complexity:
 */

/**
 * @API:
 *   get(index),  如果索引无效，则返回-1。
 *   addAtHead(val), 
 *   addAtTail(val),         
 *   addAtIndex(index,val), 
 *   deleteAtIndex(index)
 * 其中addAtIndex()在链表中的第 index 个节点之前添加值为 val  的节点，如果 index 等于链表的长度，则该节点将附加到链表的末尾；
 * 如果 index 大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点。。
 */

/**
 * @step: 首先选定数据结构：结合使用指针和new，不使用STL。
 * 头节点为实际有值的节点，尾节点不存储值，但需存储前向指针；
 * 指定位置插入: 如果用序列容器则插入需O(n)时间，用指针寻找也需O(n)时间，因此维持原来的设计，采用顺序或逆序遍历方式寻找插入位置；
 * 指定位置删除和获取指定位置元素与指定位置插入同理。
 * 
 * 对于链表，一个简单的方法是牢记每次改动操作，都需要相应地分别处理新节点、新节点的前和后节点，共三个节点，
 */

#include<bits/stdc++.h>
using namespace std;

struct Node{
    int val;
    Node* prev;
    Node* next;
    // Node(){}
    // Node(int x) : val(x){}
    Node(int x, Node* prev, Node* next) : val(x), prev(prev), next(next){}
};

class MyLinkedList {

private:
    // 只在内部使用，不需要向外提供。
    Node *head, *tail, *curr;
    size_t size = 0;

public:
    MyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }
    
    // 获取指定节点的值
    int get(int index) {
        if(index < 0 || index >= size)
            return -1;
        curr = head;
        int i = 0;
        while(i < index){
            i++;
            curr = curr->next;
        }
        return curr->val;
    }
    
    // 往头部插入节点：需判断是否第一次插入节点，若是则需额外处理（此时表内没有任何一个节点的实体）
    void addAtHead(int val) {
        // 第一次插入：头尾节点都需要开辟空间
        if(size == 0){
            tail = new Node(0, nullptr, nullptr);      // 尾节点只有pre指针有意义
            head = new Node(val, nullptr, tail);    
            tail->prev = head;
            this->size++;
            return ;
        }
        // 非首次插入，但前节点为nullptr，不需要处理。
        curr = new Node(val, nullptr, head);    // 新节点；val, pre 和 next
        head->prev = curr;          // 后一个节点，即原本的头节点
        //! //head->next->prev = head;        // 后一个节点：pre
        head = curr;        // 替换头指针
        this->size ++;          // 计数
        return;
    }
    
    void addAtTail(int val) {
        // 同样需判断是否第一次插入
        if(this->size == 0){
            tail = new Node(0, nullptr, nullptr);      // 尾节点只有pre指针有意义
            head = new Node(val, nullptr, tail);
            tail->prev = head;
            this->size ++;
            return ;
        }
        curr = new Node(val, tail->prev, tail);    // 新节点
        tail->prev->next = curr;        // 前一个节点
        tail->prev = curr;        // 后一个节点
        this->size ++;
        return;
    }
    
    void addAtIndex(int index, int val) {
        // 插入头/尾
        if(index <= 0) { this->addAtHead(val);  return; }
        else if(index == this->size) { this->addAtTail(val);  return; }
        else if(index > this->size) { return ;}
        // 插入中间
        curr = head;
        int i = 1;       // 由于是作为旧有index的前一个，初始化i为1，然后向后插入。
        while(i < index){
            curr = curr->next;
            i++;
        }
        Node *newNode = new Node(val, curr, curr->next);        // 新节点
        curr->next->prev = newNode;      // 后一个节点
        curr->next = newNode;       // 前一个节点
        this->size++;
        return;
    }
    
    void deleteAtIndex(int index) {
        if(index >= size)   return;
        else if(index < 0) return;
        // 删除头
        if(index == 0){
            curr = head->next;
            curr->prev = nullptr;
            delete head;
            head = curr;
            this->size--;
            return ;        // 删除头之后没有返回，造成严重错误！
        }
        // 删除中间
        int i = 0;
        curr = head;
        while(i < index){
            curr = curr->next;
            i++;
        } 
        curr->next->prev = curr->prev;      // 后一个节点
        curr->prev->next = curr->next;        // 前一个节点
        delete curr;        // 当前节点
        curr = head;
        this->size--;
    }

    void print(){
        curr = head;
        while(curr != tail){
            cout<<curr->val<<" ";
            curr = curr->next;
        }
        cout<<endl;
    }

    void rprint(){
        curr = tail;
        while(curr != head){
            cout<<curr->prev->val<<" ";
            curr = curr->prev;
        }
        cout<<endl;
    }
};

int main(){
    MyLinkedList mylist;
    mylist.addAtHead(6);
    mylist.addAtHead(4);

    mylist.addAtTail(7);
    mylist.addAtTail(8);
    mylist.addAtTail(9);

    mylist.addAtIndex(1,5);

    mylist.addAtHead(3);
    mylist.addAtIndex(1,2);
    
    mylist.print();
    mylist.rprint();

    mylist.deleteAtIndex(1);

    mylist.print();
    mylist.rprint();
}