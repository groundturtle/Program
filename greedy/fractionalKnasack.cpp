/*
  @Author: avert-win
  @Date: 2022-04-23 14:38:35
  @LastEditTime: 2022-04-23 15:24:22
  @Description: This method is called greedy algorithm.
  Given weights and values of n items, we need to put these items in a knapsack of capacity W to get the maximum total value in the knapsack.
  Compared with 0-1 Knapsack, in this problem you can break items into several parts.
 */

/**
input:
    50
    10 20 30 
    60 100 120 
output:
    get: 40   60
    get: 20   160
    ratio: 0.666667
    result: 240
 */

#include<vector>
#include<iostream>
#include<algorithm>

struct item
{
    int weight;
    int value;
};

bool sortItems(item& a, item& b)
{
    return float(a.value)/float(a.weight) 
                >   float(b.value)/float(b.weight);
}

int getInput(std::vector<item>& items)
{
    int capability;
    item temp;
    std::cin>>capability; 
    std::cin.get();
    std::cin>>temp.weight;
    items.emplace_back(temp);
    while(std::cin.get()!='\n')
    {
        std::cin>>temp.weight;
        items.emplace_back(temp);
    }

    auto it = items.begin();
    std::cin>>temp.value;
    it->value=temp.value;
    while(std::cin.get()!='\n')
    {
        it++;      
        std::cin>>it->value;
    }
    return capability;
}

int solveValue(std::vector<item>& items, int& capability)
{
    int result = 0;
    std::sort(items.begin(), items.end(), sortItems);
    for(auto it=items.begin(); capability>=0&&it!=items.end(); it++)
    {
        if(it->weight<=capability)
        {
            result += it->value;
            capability -= it->weight;
            std::cout<<"get: "<<capability<<"   "<<result<<std::endl;
        }
        else
        {
            float ratio = float(capability)/float(it->weight);
            std::cout<<"ratio: "<<ratio<<std::endl;
            result += it->value*ratio;
            break;
        }
    }
    return result;
}

int main()
{
    int capability;
    int result;
    std::vector<item> items;
    capability = getInput(items);
    result = solveValue(items, capability);
    std::cout<<"result: "<<result<<std::endl;
}