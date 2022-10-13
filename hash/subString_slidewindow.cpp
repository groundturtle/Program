/*
 * @Author: avert-win
 * @Date: 2022-04-22 12:27:55
 * @LastEditTime: 2022-04-22 18:37:39
 * @Description: 用滑窗法写的字符串哈希，求最长公共子串长度。
 */
#include<iostream>
#include<set>
#include<unordered_map>

/**
 * @brief 本程序共有两重循环，第一重从大到小循环，最差情况为遍历完最小长度的字符串没有找到，时间复杂度O(n)，n为较短字符串的长度；
 *        第二重循环有四个，其中两个为计算第一个滑窗的哈希值，时间复杂度为O(l)，另外两个为滑动滑窗，时间复杂度为O(n-l)，
 *        集合用红黑树实现，时间复杂度O(logN)，取消集合，改用unorder_map存储滑窗中字符串的哈希值之后，
 *        时间复杂度降低到上述两个循环的程度，最多不超过O(n^2).
 * 
 *        *使用二分法，时间复杂度能降到O(nlogN).
 *  
 *        *目录下subString_align.cpp实现了另一种方法，其中同样采用滑窗法进行字符串匹配，但在计算哈希值时使用对齐方式而非利用滑窗。
 * 
 *        哈希方法也采用滑窗匹配，但是省去了对每个子串的逐字匹配，大大减小了时间复杂度。
 * 
 *        !本次变成存在大量低级错误、因最初不愿意交换以确定字符串长短，导致后续需要双份代码，更增添了调试和修改难度！
 */

/**
 * @brief For both string, doing 1 to 5:
 * @todo 1. compute pow[]
 * First loop:
 * @todo 2. set the width of window.                            
 * @todo 3. compute the hash value of the first window.
 * Second loop:
 * @todo 4. slide the window step by step.                      
 * @todo 5. minus the first char's value, multiply power, plus the new tail.
 * 
 * @brief For the longer string, doing 6:
 * @todo 6. insert the value to an unorthered_map.
 * 
 * @brief For the shortest string, doing 7 and 8:
 * @todo 7. find above value in the map.
 * @todo 8. record the width of window if the value is already in the map.
 */

// #define DEBUGshort
// #define DEBUGlong

static int m = 1e9+9;
static int p = 31;

/**
 * @brief Make sure that string s1 is longer than string s2.
 * @param s1 
 * @param s2 
 * @return int 
 */
int common_Substring_Length(std::string s1, std::string s2)
{
    size_t len1 = s1.size(), len2 = s2.size();
    // 用滑窗法，最多需要较短字符串的长度，没错。
    long long pows[len2];
    pows[0] = 1;
    // size_t 类型的中断条件不能为负！
    for(size_t i=1; i<len2; i++)
    {
        pows[i] = (pows[i-1]*p % m);
    }

    std::set<long long> hash_values;
    long long hash_value = 0;
    for(size_t l=len2; l>=1; l--)
    {
        hash_value = 0;
    //* For the longer one:
        // Compute the hash value of the first window.
        for(size_t i=0; i<l; i++)
        {
            hash_value = (hash_value + (s1[i]-'a'+1)*pows[l-1-i]) % m;
        }
#ifdef DEBUGlong
        std::cout<<"string:  "<<s1.substr(0,l)<<std::endl;
        std::cout<<"hash_value:  "<<hash_value<<" "<<std::endl;
#endif // DEBUG
        hash_values.insert(hash_value);
        // Slide the windows from left to right.
        for(size_t i=1; i<=len1-l; i++)
        {
            // Minus the first one.
            // It shouldn't be pows[l-1-i]! It should be the last one power instead.
            // !Delete s1[i-1] instead of s1[i]!
            hash_value = (hash_value - (s1[i-1]-'a'+1)*pows[l-1]) % m;
            // Multiply the remain (l-1).
            hash_value = (hash_value*p) % m;
            // Plus the new one.
            hash_value = ((s1[i+l-1]-'a'+1) + hash_value) % m;
            // Insert the hash value.
            hash_values.insert(hash_value);
#ifdef DEBUGlong
        if(l==3)
        {
            std::cout<<"l: "<<l<<"    i:"<<i<<std::endl;
            std::cout<<"string:  "<<s1.substr(i,l)<<std::endl;
            std::cout<<"hash_value:  "<<hash_value<<std::endl;
        }
#endif // DEBUG
        }

        hash_value = 0;
    //* For the shorter one:
        for(size_t i=0; i<l; i++)
            hash_value = (hash_value + (s2[i]-'a'+1)*pows[l-1-i]) % m;
        if(hash_values.find(hash_value)!=hash_values.end())
            return l;
#ifdef DEBUGshort
        std::cout<<"string:  "<<s2.substr(0,l)<<std::endl;
        std::cout<<"hash_value:  "<<hash_value<<" "<<std::endl;
#endif // DEBUGshort
        for(size_t i=1; i<=len2-l; i++)
        {
            // Minus the first one.
            hash_value = (hash_value - (s2[i-1]-'a'+1)*pows[l-1]) % m;
            // Multiply the remain (l-1).
            hash_value = hash_value * p % m;
            // Plus the new one.
            hash_value = ((s2[i+l-1]-'a'+1) + hash_value) % m;
            if(hash_values.find(hash_value) != hash_values.end())
                return l;
#ifdef DEBUGshort
        if(l==3)
        {
            std::cout<<"l:  "<<l<<"    i:"<<i<<std::endl;
            std::cout<<"string:   "<<s2.substr(i,l)<<std::endl;
            std::cout<<"hash_value:  "<<hash_value<<std::endl;
        }
#endif // DEBUGshort
        }
    }
    return 0;
}


int commonLength_2(const std::string& s1, const std::string& s2)
{
    std::unordered_map<std::string, int> hash_map;
    return 0; 
}

int main()
{
    std::string s1 = "abcsssde";
    std::string s2 = "bab23cdsse4sssd";
    int result = s1.size()>s2.size()?common_Substring_Length(s1,s2):common_Substring_Length(s2,s1);
    std::cout<<"result:  "<<result;
}