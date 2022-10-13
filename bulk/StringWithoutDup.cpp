/*
 * @Author: avert-win
 * @Date: 2022-08-04 18:01:35
 * @LastEditTime: 2022-09-21 11:25:04
 * @FilePath: \ProgramDaily\bulk\StringWithoutDup.cpp
 * @Description: 寻找字符串中连续的无重复字符的最长子串。
 * @LastEditors: avert-win
 */
/**
 * 使用滑窗法，左边窗沿固定，右边窗沿向右扩张。
 * 当发生重复时，记录当前窗口长度，然后将左窗沿向右直到不重复，接着回到第一步右窗沿向右扩张。
 * 通过判断去除左窗沿到末尾的长度不超过现有记录、右窗沿已然到达末尾两种情况之后的计算，大幅减小时间复杂度。
 */

#include<string>
#include<iostream>
#include<unordered_set>
using namespace std;

unordered_set<char> windows;
string input = "acdadbc0012345";

int main()
{
    int length = input.length();
    int left = -1, right = 0;        // 左右闭区间。
    int result = 0;
    while(true)
    {
        try
        {
            windows.erase(input[left]);
        }
        catch(...)
        {
            cout<<"exception.\n";
        }
        left ++;
        int win_size = right - left + 1;
        // 左窗沿与右窗沿之间只有一个字符时必不重复，因此左窗沿比不可能超过右窗沿。
        while (right++ && right<length)
        {
            // 如果新进来的导致重复，要把新进来的退出(终止此次窗口扩大)并更新现有记录。
            if(windows.count(input[right]))
            {
                // debug: 窗口边沿
                cout<<left<<"  "<<right<<endl;
                //
                right --;
                break;
            }
            // 新进来的与此前的不重复，将字符插入窗口字符串、更新长度。
            else
            {
                windows.insert(input[right]);
                win_size++;
            }
        }

        // 若新进来的有重复，退回去之后再加判断，因为无法确定新进来的就是与将要退出去的第一个相同而导致重复。
        // 比对更新现有记录
        result = result>win_size ? result:win_size;
        // 直接结束整个过程的条件：右窗沿到尾，以及右窗沿到尾的长度都不如现有记录大
        if(right == length)
            break;
        if((length - (left+1)) < result)
            break;
    }
    cout<<result;
    return 0;
}