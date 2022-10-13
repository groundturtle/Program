/*
 * @Author: avert-win
 * @Date: 2022-04-23 21:22:49
 * @LastEditTime: 2022-04-29 22:54:16
 * @FilePath: \ProgramDaily\graph\DSU_Kruskals.cpp
 * @Description: 
 */
#pragma once
#include"DSU_Kruskals.h"
#include<algorithm>
#include<vector>
#include<iostream>
#include<string.h>

// Sort edges by weight. 
bool sortEdges(Edge& a, Edge& b)
{
    return a.w < b.w;
}

DSU::DSU(int V)
{
    this->V = V;
    subsets = new subset[V];
    for(size_t i=0; i<V; i++)
    {
        subsets[i].root = i;
        subsets[i].rank = 0;
    }
}

int DSU::find(int i)
{
    if(subsets[i].root!=i)
        // subsets[subsets[i].root].root = find(subsets[i].root);
        // subsets[i].root = find(subsets[subsets[i].root].root);
        subsets[i].root = find(subsets[i].root);
    return subsets[i].root;
}

// 不是联合这两个节点，而是联合这两个节点所属的子树！
void DSU::unite(int x, int y)
{
    x = find(x);
    y = find(y);
    // 直接把根置为对面的根，相当于在联合时也进行了一定的路径压缩。性能不会提升。
    // rank 的增加不应该是1，而是另一方的rank，得到的是整个子树。
    if(subsets[x].rank >= subsets[y].rank)
    {
        subsets[y].root = subsets[x].root;
        subsets[x].rank += subsets[y].rank;
    }
    else
    {
        subsets[x].root = y;
        subsets[y].rank += subsets[x].rank;
    }
}

Graph::Graph(int V)
{
    dsu = new DSU(V);
}

void Graph::addEdge(int w, int x, int y)
{
    Edges.emplace_back(Edge{w,x,y});
}

void Graph::KruskalsMST()
{
    std::sort(Edges.begin(), Edges.end(), sortEdges);
    for(auto edge : Edges)
    {
        if(dsu->find(edge.x) != dsu->find(edge.y))
        {
            dsu->unite(edge.x, edge.y);
            remainEdges.emplace_back(Edge({edge.w, edge.x, edge.y}));
            std::cout<<edge.x<<" ---> "<<edge.y<<",  weigth: "<<edge.w<<std::endl;
        }
        else continue;
    }
}