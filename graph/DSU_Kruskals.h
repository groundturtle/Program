/*
 * @Author: avert-win
 * @Date: 2022-04-23 19:56:00
 * @LastEditTime: 2022-04-23 21:31:46
 * @FilePath: \ProgramDaily\greedy\Graph_DSU_Kruskals.h
 * @Description: 请填写简介
 */
#pragma once
#include<algorithm>
#include<vector>
#include<iostream>
#include<string.h>

// int root, rank;
struct subset
{
    int root;
    int rank;
};

// int weight, vertex, vertex
struct Edge
{
    int w;
    int x;
    int y;
};

// function find(vectex), unite(vertex, vertex)
class DSU
{
private:
    int V;
    subset* subsets;

public:
    DSU(int V);
    int find(int i);
    void unite(int x, int y);
};

class Graph
{
private:
    DSU* dsu;
    std::vector<Edge> Edges;
    std::vector<Edge> remainEdges;

public:
    Graph(int V);
    void addEdge(int w, int x, int y);
    void KruskalsMST();
};