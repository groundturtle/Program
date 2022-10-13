/*
 * @Author: avert-win
 * @Date: 2022-04-23 15:59:01
 * @LastEditTime: 2022-04-23 20:00:12
 * @FilePath: \ProgramDaily\greedy\Union_Find_Cycle_in_Graph_1.cpp
 * @Description: Check whether an undirected graph contains a cycle or not with Union-Find method 1.
 */

/**
 * A disjoint-set data structure(并查集) is a data structure that keeps track of a 
 * set of elements partitioned into a number of disjoint (non-overlapping) 
 * subsets. A union-find(联合-搜索) algorithm is an algorithm that performs two useful 
 * operations on such a data structure:
 *  1. Find: Determine which subset an element is in. This can be used to determine if two elements are in the same subset.
 *  2. Union: Join two subsets into a single subset. Here first we have to check if the two subsets belong to same set.
 *  % 即用一个元素表征一个子集中的所有元素。
 *  In this part, if both the vertices of an edge are in the same subset, a cycle is found.
 *
 *  Implementation:
 *      1. Set an array for each node, indicating the subset it belong to.
 *      2. Check whether if the two vertices are in the same subset(-1 is not a set).
 *         If they are, union them: regard the latter one as the former one's parent.
 *      3. The method of step2 is finding parent, and then finding parent of parent, until
 *         the next parent are -1. The last parent is the subset(or treat it as a tree's root).
 * 
 *  Example: 
 *  0 1 2           In the left grah, the parent of 0 is 2 since 1->2->-1, and
 *  1 2 -1          the parent of 2 is 2 since 2->-1. So 0 and 2 is in the same subset.
 *                  Obiviously, you cann't set the last node's parent, or there will always be at least a cycle.
 * 
 *  The time complexity is O(E), in which E indicates the number of edges.
 *  In the next, with Union by Rank in a separate post, this will be O(logE).
 */

#include<iostream>
#include<string.h>

class Edge
{
public:
    int src, dst;    
};

class Graph
{
public:
    // Number of vertices and edges.
    int V, E;
    // Graph is represented as an array of edges.
    Edge* edge;
};

Graph* createGraph(int V, int E)
{
    Graph* graph = new Graph();
    graph->V = V;
    graph->E = E;
    // Isn't it the number of iterms in array? Is it a mistake?
    graph->edge = new Edge[graph->E];
    // graph->edge = new Edge[graph->E * sizeof(Edge)];
    return graph;
}

// Find the subset node i belong to.
int find(int parent[], int i)
{
    while(parent[i]!=-1)
    {
        i = parent[i];
    }
    return i;
}

// Set the latter as parent of the former.
void Union(int parent[], int x, int y)
{
    parent[x] = y;
}

bool containCycle(Graph* graph)
{
    int* parent = new int[graph->V];
    // Set an int value in particular size memory.
    memset(parent, -1, graph->V*sizeof(int));

    // i is the index of edge, while function find() need vertices.
    for(int i=0; i<graph->E; i++)
    {
        int x = find(parent, graph->edge[i].src);
        int y = find(parent, graph->edge[i].dst);
        
        // In fact the subset is not the correspending item in parent[], 
        // so you will never find -1.
        // if(x==y&&x!=-1)
        if(x==y)
            return true;
        Union(parent, x, y);
    }
    return false;
}

int main()
{
    int V=3, E=3;
    Graph* graph = createGraph(V,E);
    
    // add edge 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dst = 1;
 
    // add edge 1-2
    graph->edge[1].src = 1;
    graph->edge[1].dst = 2;
 
    // add edge 0-2
    graph->edge[2].src = 0;
    graph->edge[2].dst = 2;
 
    if(containCycle(graph))
        std::cout<<"\nThe graph contains at least one cycle.\n";
    else
        std::cout<<"No cycle found.";

}
/**
 * @ref https://www.geeksforgeeks.org/union-find/.
 */