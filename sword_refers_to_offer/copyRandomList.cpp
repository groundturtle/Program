/*
 * @Author: avert-win
 * @Date: 2022-10-08 15:56:23
 * @LastEditTime: 2022-11-14 18:09:50
 * @FilePath: \ProgramDaily\sword_refers_to_offer\copyRandomList.cpp
 * @Description: 复制一个复杂链表，该链表每个节点包括一个指向随机节点或NULL的指针。
 * @LastEditors: avert-win
 */
#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

/**
 * @brief 解法一：先生成next节点，并记录每个节点的指针，然后再遍历一遍生成random指针。
 *      寻找random指针的时间复杂度O(n^2)，存储节点指针的空间复杂度为O(n)。
 * @brief 解法二：用哈希表记录每个旧节点与新节点的对应关系，若在表中查找不到则生成并加入表。
 *      通过哈希表记录，避免了重复生成一个节点或指向不存在的节点
 *          （因为节点内部还包含指向其他节点的指针，因此对于逻辑上的同一节点不能存在两个实体）。
 *      时间复杂度O(n)，空间复杂度O(n)。
 */

// 解法二
class SolutionTwo{
public:
    Node* copyRandomList(Node* head){
        
        if(!head)
            return NULL;

        unordered_map<Node*, Node*> newNode;
        Node* newHead = new Node(head->val);
        // 头节点不要忘记送入集合！否则造成生成新的头节点
        newNode[head] = newHead;
        Node* curr = head;
        Node* newCurr = newHead;
        // 为当前节点生成下一节点以及随机节点，如果目标节点已经生成则直接从哈希表里取出赋值。
        while(curr){
            // next为NULL
            if(!curr->next){
                newCurr->next = NULL;
                newCurr->random = curr->random ? newNode[curr->random] : NULL;
                break;
            }
            // next节点
            if(!newNode.count(curr->next)){
                newCurr->next = new Node(curr->next->val);
                newNode[curr->next] = newCurr->next;
            }
            else
                newCurr->next = newNode[curr->next];

            // random为NULL
            if(!curr->random){
                newCurr->random = NULL;
                // 没有更新curr和newCurr指针而直接continue导致死循环
                curr = curr->next;
                newCurr = newCurr->next;
                continue;
            }
            if(!newNode.count(curr->random)){
                newCurr->random = new Node(curr->random->val);
                newNode[curr->random] = newCurr->random;
            }
            else
                newCurr->random = newNode[curr->random];

            curr = curr->next;
            newCurr = newCurr->next;
        }

        return newHead;
    }
};

// 解法一
class SolutionOne {
public:
    Node* copyRandomList(Node* head) {

        // 整个链表为空的情况
        if(!head)
            return NULL;

        vector<Node*> nodes;
        vector<Node*> newNodes;
        //生成新的头节点、将新旧头节点分别存入向量中
        Node* newHead = new Node(head->val);
        nodes.push_back(head);
        newNodes.push_back(newHead);

        Node* newCurr = newHead;
        Node* curr = head;
        // 生成只含有值的next节点，返回的地址存入当前节点的next中，再存入向量中。
        while(curr->next){
            newCurr->next = new Node(curr->next->val);
            newCurr = newCurr->next;
            curr = curr->next;
            nodes.push_back(curr);
            newNodes.push_back(newCurr);
        }

        newCurr = newHead;
        curr = head;
        // 为旧链表的每个节点的random指针找到相应的指向节点，然后根据索引为新链表生成random指针。
        while(curr){
            int i = 0;
            for(auto node : nodes){
                if(curr->random == node){
                    newCurr->random = newNodes[i];
                    break;
                }
                i++;
            }
            curr = curr->next;
            newCurr = newCurr->next;
        }
        
        return newHead;
    }
};