/*
 * @Author: avert-win
 * @Date: 2022-04-26 10:57:34
 * @LastEditTime: 2022-04-26 11:53:33
 * @FilePath: \ProgramDaily\greedy\jobSequence_DisjointSet.cpp
 * @Description: 
 * 简介
 */
#include<bits/stdc++.h>
using namespace std;
 
// A structure to represent various attributes of a Job
struct Job
{
    // Each job has id, deadline and profit
    char id;
    int deadLine, profit;
};
 
// A Simple Disjoint Set Data Structure
struct DisjointSet
{
    int *parent;
 
    // Constructor
    DisjointSet(int n)
    {
        parent = new int[n+1];
 
        // Every node is a parent of itself
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }
 
    // Path Compression
    int find(int s)
    {
        /* Make the parent of the nodes in the path
           from u--> parent[u] point to parent[u] */
        if (s == parent[s])
            return s;
        return parent[s] = find(parent[s]);
    }
 
    // Makes u as parent of v.
    void merge(int u, int v)
    {
        //update the greatest available
        //free slot to u
        parent[v] = u;
    }
};
 
// Used to sort in descending order on the basis
// of profit for each job
bool cmp(Job a, Job b)
{
    return (a.profit > b.profit);
}
 
// Functions returns the maximum deadline from the set
// of jobs
int findMaxDeadline(struct Job arr[], int n)
{
    int ans = INT_MIN;
    for (int i = 0; i < n; i++)
        ans = max(ans, arr[i].deadLine);
    return ans;
}
 
int printJobScheduling(Job arr[], int n)
{
    sort(arr, arr + n, cmp);
 
    //生成并查集，个数与可用时间单元数相等。
    int maxDeadline = findMaxDeadline(arr, n);
    DisjointSet ds(maxDeadline);
 
    // 按利润从大到小遍历任务，如果有可用时间片，就执行这个任务，并合并这个被用掉的时间片（结束时刻指向开始时刻）
    // 每个任务执行完成的时间都尽量是自己的任务截止时间，否则按照并查集查找往前。
    for (int i = 0; i < n; i++)
    {
        int availableSlot = ds.find(arr[i].deadLine);
 
        if (availableSlot > 0)
        {
            ds.merge(ds.find(availableSlot - 1),
                             availableSlot);
            cout << arr[i].id << " ";
        }
    }
}
 
// Driver code
int main()
{
    Job arr[] =  { { 'a', 2, 100 }, { 'b', 1, 19 },
                   { 'c', 2, 27 },  { 'd', 1, 25 },
                   { 'e', 3, 15 } };
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Following jobs need to be "
         << "executed for maximum profit\n";
    printJobScheduling(arr, n);
    return 0;
}