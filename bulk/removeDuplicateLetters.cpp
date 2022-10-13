/*
 * @Author: avert-win
 * @Date: 2022-04-23 10:46:21
 * @LastEditTime: 2022-04-24 02:26:39
 * @Description: 给定字符串，要求去除重复字符并使最后的字符串字典序最小。字符串只由小写字母组成。
 */

/**
 * @brief 本题浪费了很长时间，其实关键在于两点，一是字符串的字典序如何计算，这一点没搞清楚却想下手，完全是徒劳；
 *        二是字符的动态更新决定去留：按照我最初的做法，字符只和后面一个比较，一旦入栈就不再动弹，这样就导致没有
 *        处理前面一段顺序但是全部需要删除的情况。官方解法则不同，进行了栈的回溯，而非仅根据当前状况决定是否入栈。
 *        官方的解答思想就在于弹栈。
 */

#include<iostream>
#include<vector>
#include<unordered_map>
#include<stack>
using namespace std;

class Solution {

private:
    string result;
    int *sum;
    bool *flag;
    stack<char> chars;

public:
    Solution()
    {
        sum = new int[26];
        flag = new bool[26];
        for(size_t i=0; i<26; i++)
        {
            sum[i] = 0;
            flag[i] = false;
        }
    }
    string removeDuplicateLetters(string s) 
    {
        for(auto c:s)
        {
            sum[c-'a']++;
        }
        for(size_t i=0; i<s.size(); i++)
        {
            sum[s[i]-'a']--;
            if(chars.empty())
            {
                chars.push(s[i]);
                flag[s[i]-'a']=true;
            }
            else
            {
                // 栈不空，字符未入栈，字符逆序，栈顶字符有剩余
                while(!chars.empty()&&!flag[s[i]-'a']&&s[i]<chars.top()&&sum[chars.top()-'a']!=0)
                {
                    flag[chars.top()-'a'] = false;
                    chars.pop();
                }
                // 字符未入栈，且能弹的都弹了，则入栈。
                // 入栈之后可以再删，如果中间有唯一字符阻挡着，说明这个唯一字符比(栈内其自身与其往下另一唯一字符之间的全部可弹字符)都要大，也能保证正确。
                if(!flag[s[i]-'a'])
                {
                    chars.push(s[i]);
                    flag[s[i]-'a'] = true;
                }
            }
        }
        while(!chars.empty())
        {
            result = chars.top() + result;
            chars.pop();
        }
        return result;
    }

/* 在入栈之前和后面字符作比较，无法处理前面全为顺序但应该删的情况。
    string removeDuplicateLetters(string s) 
    {
        for(auto c:s)
        {
            sum[c-'a']++;
        }
        for(size_t i=0; i<s.size(); i++)
        {
            times[s[i]-'a'] ++;
            if(i!=s.size()-1)
            {
                //正序，且前面未有入栈，则入栈、计数，此后这个字符永远不必再管，只要设置已入栈标志即可。
                if(s[i]-s[i+1]<0 && !flag[s[i]-'a'])
                {
                    chars.push(s[i]);
                    // times[s[i]-'a'] ++;
                    flag[s[i]-'a'] = true;
                }
                //逆序或同序，且前面未有入栈(若有入栈一定是顺序的或字符串中最后一个的，永远不必再管)，
                //则判断后面还有无，无则不得不入栈，此时连同入栈标志也不必再管；若后面还有则不入栈。
                //因为字典序是只看前面，前面相同才看后面，，所以一旦发现逆序直接倒过来准没错。不需要严格的数学公式或证明。
                if(s[i]-s[i+1]>=0 && !flag[s[i]-'a'])
                {
                    if(sum[s[i]-'a']-times[s[i]-'a'] == 0)
                        chars.push(s[i]);
                }
            }
            if(i==s.size()-1)
            {
                //最后一个字符未入栈，则直接送入，否则不用管（因为前面入栈已经保证后面没有或者当时是正序，而现在后面有，说明前面一定是正序，所以不必再管。
                if(!flag[s[i]-'a'])
                    chars.push(s[i]);
            }
        }
        while(!chars.empty())
        {
            result = chars.top() + result;
            chars.pop();
        }
        return result;
    }
*/
};

int main()
{
    string s = "bcabc";
    Solution solu;
    std::cout<<solu.removeDuplicateLetters(s);
}