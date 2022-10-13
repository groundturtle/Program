/*
 * @Author: avert-win
 * @Date: 2022-04-23 21:33:03
 * @LastEditTime: 2022-04-29 22:53:36
 * @FilePath: \ProgramDaily\graph\main.cpp
 * @Description: 
 * 简介
 */
#include"DSU_Kruskals.h"
#include"DSU_Kruskals.cpp"

void KMST()
{
    Graph graph(4);
    graph.addEdge(10, 0, 1);
	graph.addEdge(15, 1, 3);
	graph.addEdge(4, 2, 3);
	graph.addEdge(6, 2, 0);
	graph.addEdge(5, 0, 3);
    graph.KruskalsMST();
    return ;
}

int main()
{
    KMST();
    return 0;
}