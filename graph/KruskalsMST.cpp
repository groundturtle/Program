/*
 * @Author: avert-win
 * @Date: 2022-04-23 15:30:53
 * @LastEditTime: 2022-04-23 23:16:24
 * @FilePate: /ProgramDaily/greedy/KruskalsMST.cpp
 * @Description: 将各边按权重由小到大顺序排列，然后依次选择边，只要不构成环就采纳，直至采纳的边数E_accepted达到节点数V的减一，即E_accepted=V-1.
 * 				 本例中，没有使用边数达到要求的判断，而是直接遍历全部。
 * 				 判断是否构成环的方法为使用并查集、联合-搜索方法，详见'\ProgramDaily\greedy\Union_Find_Cycle_in_Graph_1.cpp'和'\ProgramDaily\greedy\Union_Find_Cycle_in_Graph_2.cpp'
 * 		
 %  Time Complexity: O(ElogE) or O(ElogV). 
 * 	Sorting of edges takes O(ELogE) time. After sorting, we iterate through all edges, 
 *  and apply the find-union algorithm. The find and union operations can take at most O(LogV) time. 
 *  So overall complexity is O(ELogE + ELogV) time. The value of E can be at most O(V2), so O(LogV) is O(LogE) the same. 
 *  Therefore, the overall time complexity is O(ElogE) or O(ElogV).
 */

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// 并查集类
// path compression + rank by union
// Has function DSU(), find(), and unite().
class DSU
{
	int* parent;
	int* rank;

public:
    // Get vertices' number, initialize parent(itself) and rank(any number).
	DSU(int n)
	{
		parent = new int[n];
		rank = new int[n];

		for (int i = 0; i < n; i++) 
        {
			parent[i] = i;
			rank[i] = 1;
		}
	}

	// Find and set parent for every node in the road.
	int find(int i)
	{
		if (parent[i] == i)
			return i;

		return parent[i] = find(parent[i]);
	}

	// union nodes by rank.
	void unite(int x, int y)
	{
		int s1 = find(x);
		int s2 = find(y);

		if (s1 != s2) 
        {
			if (rank[s1] < rank[s2])
			{
				parent[s1] = s2;
				rank[s2] += rank[s1];
			}
			else 
			{
				parent[s2] = s1;
				rank[s1] += rank[s2];
			}
		}
	}
};

/**
 * @brief 图类，含有：
 * 1. 一个边向量，每条边用一个向量表示；
 * 2. 添加边的函数addEdge();
 * 3. 节点数量，根据构造函数参数初始化；
 * 4. 一个生成树的函数kruskals_mst()，
 */
class Graph 
{
	vector<vector<int> > edgelist;
	int V;

public:
	Graph(int V) { this->V = V; }

	void addEdge(int x, int y, int w)
	{
		edgelist.push_back({ w, x, y });
	}

	void kruskals_mst()
	{
		// 1. Sort all edges
		sort(edgelist.begin(), edgelist.end());

		// Initialize the DSU. 
		// DSU s(V);  Use way below to get comment of construct function.
		DSU s = DSU(V);	
		int ans = 0;
		cout << "Following are the edges in the "
				"constructed MST"
			<< endl;
		for (auto edge : edgelist) 
		{
			int w = edge[0];
			int x = edge[1];
			int y = edge[2];

			// Take that edge in MST if it doesn't form a cycle
			// Otherwise, drop it and get the next one.
			if (s.find(x) != s.find(y)) 
			{
				s.unite(x, y);
				ans += w;
				cout << x << " -- " << y << " == " << w
					<< endl;
			}
		}
		cout << "Minimum Cost Spanning Tree: " << ans;
	}
};

int main()
{
	/* Let us create following weighted graph
				10
			0--------1
			| \	     |
		   6|  5\    |15
			|	  \  |
			2--------3
				4	 */
	Graph g(2);
	g.addEdge(0, 1, 10);
	g.addEdge(1, 3, 15);
	g.addEdge(2, 3, 4);
	g.addEdge(2, 0, 6);
	g.addEdge(0, 3, 5);

	// int n, m;
	// cin >> n >> m;

	// Graph g(n);
	// for (int i = 0; i < m; i++)
	// {
	//	 int x, y, w;
	//	 cin >> x >> y >> w;
	//	 g.addEdge(x, y, w);
	// }

	g.kruskals_mst();
	return 0;
}
