/*
 * @Author: avert-win
 * @Date: 2022-04-28 10:04:42
 * @LastEditTime: 2022-04-28 21:56:49
 * @FilePath: \ProgramDaily\dfs_bfs\ocean_dfs_recur.cpp
 * @Description: 
 */

/*
 * 1. 深搜使用递归或者栈，直接把满足条件的进入递归或入栈即可。
 *    注意一定要在入栈或进入递归之后再标记完成探索，否则会自己把自己的路堵死！
 * 2. 深搜和广搜通常使用一个[4,2]的数组来定义上、下、左、右，以便在后续步骤中
 *    使用一个循环完成上下左右四个步骤的探索。由于需要判断是否越界、是否满足往前进的条件，这在一个一个方向上实现将会十分麻烦。         
 */

#include<vector>
#include<stack>
#include<iostream>

class Solution
{
public:

public:

    //! fatal!
    // std::vector<std::vector<int>>& heights;
    std::vector<std::vector<int>> heights;
    int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    int m, n;    

    // Solution(){
    //     std::vector<std::vector<int>> temp(1,std::vector<int>(1,1));
    //     this->heights = temp;
    //  }

    //每个起点深入搜寻一次，搜寻过程中向四面搜寻，一旦碰到底，就往回退，以回退的这个点为起点再度搜寻。
    std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>>& heights) 
    {
        m = heights.size();
        n = heights[0].size();
        this->heights = heights;
        std::vector<std::vector<bool>> pa_visited(m, std::vector<bool>(n,false));
        std::vector<std::vector<bool>> al_visited(m, std::vector<bool>(n,false));
        std::vector<int> start;
        for(int i=0; i<m; i++)
        {
            dfs(i, 0, pa_visited);
        }
        for(int i=0; i<n; i++)
        {
            dfs(0, i, pa_visited);
        }
        for(int i=0; i<m; i++)
        {
            dfs(0, n-1, pa_visited);
        }
        for(int i=0; i<n; i++)
        {
            dfs(m-1, i, al_visited);
        }

        std::vector<std::vector<int>> result;
        std::vector<int> temp;
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(pa_visited[i][j]&&al_visited[i][j])
                {
                    temp.clear();
                    temp.emplace_back(i);
                    temp.emplace_back(j);
                    result.emplace_back(temp);
                }
            }
        }
        return result;
    }

    void dfs(int x0, int y0, std::vector<std::vector<bool>>& visited)
    {
        if(!visited[x0][y0])
            visited[x0][y0] = true;
        else return;
        for(int i=0; i<4; i++)
        {
            int x = x0 + dirs[i][0];
            int y = y0 + dirs[i][1];
            if(x<m && y<n && x>=0 && y>=0 && !visited[x][y])
            {
                if(heights[x][y]>=heights[x0][y0])
                    dfs(x, y, visited);
            }
        }
    } 
};


int main()
{
    Solution solu;
    std::vector<std::vector<int>> heights = {{3,2},{2,2},{2,3}};
    std::vector<std::vector<int>> result;
    result = solu.pacificAtlantic(heights);
    for(int i=0; i<result.size(); i++)
    {
        std::cout<<result[i][0]<<", "<<result[i][1]<<std::endl;
    }
}