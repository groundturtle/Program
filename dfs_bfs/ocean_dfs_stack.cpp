/*
 * @Author: avert-win
 * @Date: 2022-04-28 20:53:19
 * @LastEditTime: 2022-04-28 20:53:19
 * @FilePath: \ProgramDaily\dfs_bfs\ocean_dfs_stack.cpp
 * @Description: 
 */
#include<vector>
#include<stack>
#include<iostream>

class Solution
{
public:

    //! fatal!
    // std::vector<std::vector<int>>& heights;
    std::vector<std::vector<int>> heights;
    int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    int m, n;    

    //每个起点深入搜寻一次，搜寻过程中向四面搜寻，一旦碰到底，就往回退，以回退的这个点为起点再度搜寻。
    std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>>& heights) 
    {
        m = heights.size();
        n = heights[0].size();
        this->heights = heights;
        std::vector<std::vector<bool>> pa_visited(m, std::vector<bool>(n,false));
        std::vector<std::vector<bool>> al_visited(m, std::vector<bool>(n,false));
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
            dfs(0, n-1, al_visited);
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
    }//pacificAtlantic()

    void dfs(int x0, int y0, std::vector<std::vector<bool>>& visited)
    {

        // printf("A new dfs from (%d, %d)\n", x0, y0);

        if(visited[x0][y0])
            return;

        std::stack<int> searching;
        searching.push(x0);
        searching.push(y0);

        while(!searching.empty())
        {
            y0 = searching.top();
            searching.pop();
            x0 = searching.top();
            searching.pop();
            visited[x0][y0] = true;

            for(int i=0; i<4; i++)
            {
                // std::cout<<"i: "<<i<<std::endl;
                int x = x0 + dirs[i][0];
                int y = y0 + dirs[i][1];
                // 只要不越界、高度大于等于可流入海洋的地区，就入栈，并标记可流入。
                if(x<m && y<n && x>=0 && y>=0 && !visited[x][y])
                {
                    if(heights[x][y]>=heights[x0][y0])
                    {
                        searching.push(x);
                        searching.push(y);
                        // visited[x][y] = true;
                    }
                }
            }
        } //searching loop while.
    
    }//dfs()

};//Solution


int main()
{
    Solution solu;
    std::vector<std::vector<int>> heights = {{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}};
    std::vector<std::vector<int>> result;
    result = solu.pacificAtlantic(heights);
    for(int i=0; i<result.size(); i++)
    {
        std::cout<<result[i][0]<<", "<<result[i][1]<<std::endl;
    }
}