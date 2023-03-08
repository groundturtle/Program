/**
 * @file frequenceStack.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 实现一个栈，只需要支持push()和pop()，但pop()应返回当前栈中数量占比最大的数字；
 *      如多个数字在目前栈中出现频数相同，则返回最后入栈的（最接近栈顶的）。
 *      pop()同时还将该数字的最后一个从栈中清除。
 * @version 0.1
 * @date 2022-12-01
 * @LastEditTime
 */

/**
 * @brief 同时利用多个栈，每个栈对应一个不同的出现频数，再用一个哈希表存储每个数字当前在所有栈中的频数。
 * 利用以下两个性质，可以在常数时间内实现push()和pop()。
 * 1. 从后往前出栈，每一个现在出栈的数字都刚好使得下一个将要出栈的数字所拥有的频数与其所处栈相吻合；
 *      因此在一个数字的后续副本入栈时，无需调整前面的数。
 * 2. 每一个数字n的多个副本，其入栈时的频数一定是按步幅1递增的，若n目前最高出现在栈x上，则栈x-1, x-2, ... 1上一定都会有一个n；
 *      所以出栈时可以根据当前栈空与否确定最大频率要么不变，要么减一。
 */

class FreqStack {
private:
    unordered_map<int,int> num_fre;
    vector<stack<int>*> ss;
    int maxfre = 0;
public:
    FreqStack() {

    }
    
    void push(int val) {
        if(num_fre.count(val))
            num_fre[val]++;
        else
            num_fre[val] = 1;
        maxfre = max(maxfre, num_fre[val]);
        if(ss.size()>=num_fre[val])
            ss[num_fre[val] - 1]->push(val);     // 该栈已存在向量中，直接入栈
        else{
            stack<int>* s = new stack<int>;          // 建栈再入栈
            s->push(val);            
            ss.push_back(s);
        }
        return ;
    }
    
    int pop() {
        int ret = (*ss.rbegin())->top();
        (*ss.rbegin())->pop();
        num_fre[ret] -- ;       // 出栈后该数的频率要更新，否则影响maxfre。
        if((*ss.rbegin())->empty()){       // 如果出栈后最高频次栈已空，则更新最高频次，且将该栈清除。
            delete *ss.rbegin();
            ss.pop_back();
            maxfre --;
        }
        return ret;
    }

    /**
     * 优化版本：即使栈空也不清除栈，留待下次使用
     * 注意用于在ss中索引栈指针的下标应是maxfre-1，因为栈的fre从1开始，而下标从0开始。
     */
    // int pop() {
    //     int ret = ss[maxfre-1]->top();
    //     ss[maxfre-1]->pop();
    //     num_fre[ret] -- ;
    //     if(ss[maxfre-1]->empty()){
    //         maxfre --;
    //     }
    //     return ret;
    // }
};
