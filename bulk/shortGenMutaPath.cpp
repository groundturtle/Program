/**
 * @file shortGenMutaPath.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 有八位基因，每次只许突变一次，给出基因池和初始基因、目标基因，求初始基因经基因池突变到目标基因的最短路径长度。
             目标基因保证在基因池内，突变路径必须在基因池内；若不存在这种路径，则路径长度为-1.
 * @version 0.2
 * @date 2022-12-02
 * @complexity: 
 */

/**
 * @brief 2022-05-07曾经提交。
 * 这次一开始的思路就是，根本没有任何算法可言，只有合适的数据结构可以用空间换时间。那么，
 * !!!
 * 既然一开始就觉得这道题没什么算法，就应该及时去确定，如果确实如此那么就应该直接使用暴力方法，之后再考虑优化；设计阶段的小小优化是毫无意义的，根本不能改变代价等级，反而会对自己造成困扰。
 * 
 * 第一次的思路是，使用广度优先搜索，将每次的起始基因可以变异到达的基因存储在同一个集合中，然后将集合里的全部基因作为下次突变的起始基因。
 * 在这个过程中，需要将每次加入集合的基因都存储起来，避免成为下一次突变的目的：因为突变到一个集合中的每个基因所需步数都相同，没有道理往回走。
 * 由于突变的目标也需要出现在基因库中，因此可以直接将划入起始基因集合的基因从基因库中删去，而无需另外创建集合。
 */

/**
暴力遍历：
 * 第一步与递归相同，产生最多24种结果，然后验证其是否在bank中，若在则加入一个队列；
 * 循环取出队列直到队列为空，将该序列重复第一步，但需另外确认变异后的基因是第一次入队。

递归：
 * 任选一位变异，若未曾变异、且在基因库中，就进入递归。
*/

#include<bits/stdc++.h>
using namespace std;

class Solution {
private:
    set<string> visited;
    set<string> bank;
    int ret = INT_MAX;
    string endGene = "";
    char mutateTo[4] = {'A', 'G', 'C', 'T'};

    // 注意这个函数不能传引用，因为同一个序列要多次用到这个函数。
    void mutate(string startGene, int step){

        // 先处理数据
        step++;
        visited.insert(startGene);          // 在递归内部刚进入时标记已探索
        
        // 开始逐个变异
        for(auto& c : startGene){       // 进入下一个之前要恢复原来的，否则造成一次改变多个基因的情况
            char tmp = c;
            // 探索每一种变异可能
            for(int i=0; i<4; i++){
                c = mutateTo[i];
                // 变异得到目标，更新最小步数然后返回，不进入递归
                if(startGene == endGene){
                    this->ret = min(this->ret, step);
                    return;
                }
                // 未探索过，且在基因库中
                if(visited.find(startGene) == visited.end() && bank.find(startGene) != bank.end()){
                    mutate(startGene, step);
                }
            }
            c = tmp;        // 恢复这一位，进行下一位的变异
        }
    }
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        this->endGene = endGene;
        for(const auto& s : bank)
            this->bank.insert(s);
        visited.insert(startGene);

        // 由于递归中不探索start == end的可能，因此要提前处理
        if(startGene == endGene)    return 0;
        // 如果end不在基因库中，递归可以解决，但直接返回更快
        if(this->bank.find(endGene) == this->bank.end())    return -1;
        mutate(startGene, 0);
        return this->ret == INT_MAX ? -1 : this->ret;
    }
};