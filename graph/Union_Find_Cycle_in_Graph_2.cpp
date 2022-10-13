/*
 * @Author: avert-win
 * @Date: 2022-04-23 17:30:35
 * @LastEditTime: 2022-04-23 23:48:00
 * @Description: 
 *      Union-Find by rank and path compression, 
 *      to check whether an undirected graph contains an cycle.
 * See Union_Find_Cycle_in_Graph_2.cpp first.
 */

/**
 * Rank by the number of children a node has, compress in recursion in function Union().
 * ?Compare function `find()` and `Union()`. That's what mainly different.
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

struct subset
{
    int parent;
    int rank;
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
// Add: path compression.
int find(subset subsets[], int i)
{
    // By sentence `subsets[i].parent = find()`, path is to be compressed.
    // After recursion, every node's parent is the last node's parent -- the last node.
    if(subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Set the latter as parent of the former.
// Add: rank. Once add a son, rank++. By always making the higher rank
//      as the parent, the subset tree will be the shortest but widest one.
void Union(subset subsets[], int xroot, int yroot)
{
    if(subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if(subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    // If the ranks are same, randomly make one as parent and increment its rank.
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

bool containCycle(Graph* graph)
{

    subset* subsets = new subset[graph->V];

    for(int v=0; v<graph->V; v++)
    {
        // Now the initial parent is not -1 but it self.
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // i is the index of edge, while function find() need vertices.
    for(int i=0; i<graph->E; i++)
    {
        int x = find(subsets, graph->edge[i].src);
        int y = find(subsets, graph->edge[i].dst);
        
        // In fact the subset is not the correspending item in parent[], 
        // so you will never find -1.
        // if(x==y&&x!=-1)
        if(x==y)
            return true;
        Union(subsets, x, y);
    }
    return false;
}

int main()
{
    int V=2, E=1;
    std::cout<<V<<E;
    Graph* graph = createGraph(V,E);
    
    // // add edge 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dst = 1;
 
    // // add edge 1-2
    // graph->edge[1].src = 1;
    // graph->edge[1].dst = 2;
 
    // // add edge 0-2
    // graph->edge[2].src = 0;
    // graph->edge[2].dst = 2;
 
    if(containCycle(graph))
        std::cout<<"\nThe graph contains at least one cycle.\n";
    else
        std::cout<<"No cycle found.";

}
/**
 * @ref https://www.geeksforgeeks.org/union-find/.
 */