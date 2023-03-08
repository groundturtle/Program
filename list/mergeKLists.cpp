/**
 * @file mergeKLists.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 合并k个单调递增有序链表，并使其仍然单调递增。所有链表的节点个数之和为n。
 * @version 0.1
 * @date 2022-11-29
 * @LastEditTime
 */

/**
 * @brief 思路：先回顾两个有序链表的合并步骤。
 *  使用双指针同步遍历两个链表的节点，直到某一节点更小，则该处指针向后多走一步，然后继续同步遍历；
 *  以上方法的时间复杂度是O(n + m)，空间复杂度为答案空间复杂度。
 *  注意若其中一个链表已经结束遍历，则另一个链表无需再遍历，直接将后续整段接入即可。
 * 
 *  现有k个链表，且 0 <= k <= 10^4，则需要k个指针，额外空间复杂度为O(k);
 *  采用同样的方法遍历，需要首先求出最小值，接着将该最小值的后续节点加入，再求最小值，往复循环；
 *  因此需要建堆，并且堆中的每个元素必须标明其所属链表和结点指针，建堆时间复杂度为O(k)或O(klogk)，插入和取出一个元素时间复杂度为O(logk)
 *  总的时间复杂度为建堆加上每个节点一次插入和一次退出， 2*logk * n，
 *      O(k + n*logk)，根据题意不超过 10^4。
 * 
 * @brief 另一种很值得参考的思路：采用分治法，将k个链表两两配对，递归进行合并。
 *      根据递归树的形状，每一层所处理的节点总数都是n，一个logk层，因此时间复杂度 O(n*logk)；
 *      没有显式使用到额外空间，只有递归调用引起的栈空间消耗O(logk)。
 */

#include<bits/stdc++.h>
using std::vector;
using std::list;
using std::priority_queue;
using std::make_pair;
using std::for_each;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(): val(0), next(nullptr){};
    ListNode(int x): val(x), next(nullptr){};
    ListNode(int x, ListNode *next): val(x), next(next){}; 
};

typedef std::pair<int, ListNode*>  heapElem;

/**
 * @brief 优先队列的四种自定义比较排序方式见 ../sample_c_cpp/priorityQ_cmp.cpp 。
 */
bool cmpfunc(const heapElem& a, const heapElem& b){
    return a.first > b.first;
}
std::priority_queue<heapElem, vector<heapElem>, decltype(&cmpfunc)> Q(&cmpfunc);

class Solution {
    // 将空链表移到末尾，返回空链表的起始位置下标。时间复杂度O(k)
    int rmEmpty(vector<ListNode*>& lists){
        if(lists.empty())  return 0;
        int k = lists.size();
        int start = k-1;
        for(int i=0; i<k; i++){
            //todo: 将全部空的放到后面、非空放到前面，并返回第一个空的下标。
            //! 既然已经确定是空指针，就没必要交换，否则后面的非空被交换成了空指针，会造成错误删除！
            if(!lists[i]){
                while (!lists[start] && i<start){
                    start--;
                }
                if(start == i)
                    break;
                else{
                    lists[i] = lists[start];
                    lists[start] = nullptr;
                }
            }
        }
        return lists[start] ? start+1 : start;
    }
public:
    /**
     * @step: 
     *  1. 为每个链表初始化一个节点指针；
     *  2. 建堆；
     *  3. 将堆顶元素取出放到新链表表中，并将堆顶元素的指针向后移一位，将新元素加入堆中。
     *  4. 重复以上步骤。
     * 注意：步骤2建堆时链表为空的情况；步骤3某个链表遍历完的情况。
     *  可以在堆中直接插入节点指针，不使用堆以外的额外变量.
     */
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        std::priority_queue<heapElem, vector<heapElem>, decltype(&cmpfunc)> Q(&cmpfunc);
        // 将空链表移到末尾，然后清除
        int emptynum = rmEmpty(lists);
        lists.erase(lists.begin()+emptynum, lists.end());
        // 建堆，无需考虑空链表
        for(auto ptr : lists){
            Q.push(make_pair(ptr->val, ptr));
        }
        ListNode *head = nullptr;
        ListNode *newcurr = nullptr;
        // 队列非空时，一直循环将堆顶移出到新列表，并同时将该节点的后继节点放入堆中。
        while(!Q.empty()){                  
            auto top = Q.top();
            //! 应该新的加入之前删除，否则加入的是新的堆顶就会造成错误删除，进而死循环！
            Q.pop();
            if(newcurr == nullptr){         // 第一个节点，初始化head节点，令newcurr不为空
                newcurr = new ListNode(top.first);
                head = newcurr;
            }
            else{                   // 以后的节点，不改变head，但将newcurr->next（而非newcurr）指向新的节点。
                newcurr->next = new ListNode(top.first);
                newcurr = newcurr->next;
            }
            if(top.second->next){                // 如果当前堆顶的下一节点指针非空，将其加入堆中。
                Q.push(make_pair(top.second->next->val, top.second->next));
            }
            //!
            // Q.pop();
        }
        return head;
    }
};

int main(){
    Solution solu = Solution();
    ListNode *head1 = new ListNode(1);
    ListNode *head2 = new ListNode(2);
    head2->next = new ListNode(20);
    vector<ListNode*> lists;
    // vector<ListNode*> lists = {nullptr};
    // vector<ListNode*> lists = {nullptr, nullptr, head1, head2, nullptr, nullptr};
    ListNode *l = solu.mergeKLists(lists);
    while(l){
        std::cout<<l->val<<", ";
        l = l->next;
    }
}