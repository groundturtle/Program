/*
 * @Author: avert-win
 * @Date: 2022-04-26 10:10:08
 * @LastEditTime: 2022-04-26 10:56:51
 * @FilePath: \ProgramDaily\greedy\JobSequence.cpp
 * @Description: 
 *      Given an array of jobs where every job has a deadline and associated profit if the job is finished before the deadline. 
 *      It is also given that every job takes a single unit of time, so the minimum possible deadline for any job is 1. 
 *      How to maximize total profit if only one job can be scheduled at a time.
 */

/*
 * Solution2, time complexity O(nlogn)
 */

#include<vector>
#include<iostream>
#include<algorithm>
#include"_priority_queue.hpp"

struct Job
{
    char id;
    int deadline;
    int profit;
};

struct JobProfit
{
    bool operator()(Job const& a, Job const& b)
    {
        return a.profit < b.profit;
    }
};

void printScheduling(Job arr[], int n)
{
    std::vector<Job> result;
    std::sort(arr, arr+n, [](Job a, Job b){return a.deadline < b.deadline;});

    std::priority_queue<Job, std::vector<Job>, JobProfit> pq;

    // 无论时间如何，每次任务都入队，队内的任务即未完成的、可在当前时间段完成的任务；
    // 当出现时间段时将按照利润排序的、未过期的任务依次取出来完成，可用时间减一，并做好记录。
    // 如果任务已经完成而时间还没用完，则必须抛弃，因为其它任务必须到此时已经超过了deadline.
    for(int i=n-1; i>=0; i--)
    {
        pq.push(arr[i]);
        int slot_available;
        if(i==0)
        {
            slot_available = arr[i].deadline;
        }
        else
        {
            slot_available = arr[i].deadline - arr[i-1].deadline;
        }

        while(slot_available > 0 && pq.size() > 0)
        {
            Job job = pq.top();
            pq.pop();
            slot_available -= 1;
            result.push_back(job);
        }
    }

    std::cout<<std::endl;
    // std::sort(result.begin(), result.end(), [&](Job a, Job b){ return a.deadline < b.deadline; });
    for(int i=0; i<result.size(); i++)
        std::cout<<result[i].id<<"  ";
    std::cout<<std::endl;
}

int main()
{
    Job arr[] = { {'a', 2, 100}, {'b',1,19}, {'c',2,27}, {'d',1,25}, {'e',3,15} };
    int n = sizeof(arr)/sizeof(arr[0]);
    printScheduling(arr, n);
    return 0;
}