/*
 * @Author: avert-win
 * @Date: 2022-04-22 16:43:51
 * @LastEditTime: 2022-10-13 18:02:50
 * @Description: 使用滚动哈希方法，求解字符串包含问题。时间复杂度O(M+N)。
 */

#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;

static int m = 1e9+9;
static int p = 31;

vector<int> containing(const string& s1, const string& s2)
{
    assert(s1.size()>=s2.size());
    int len2 = s2.size();
    int len1 = s1.size();

    long long pows[len1];
    pows[0] = 1;
    for(size_t i=1; i<len1; i++)
        pows[i] = pows[i-1] * p % m;

    long long hash2 = 0;
    for(size_t i=0; i<len2; i++)
        hash2 = (hash2 + (s2[i]-'a'+1)*pows[i]) % m;

    long long hash1[len1+1];
    hash1[0] = 0;
    for(size_t i=1; i<=len1; i++)
    {   // !s1[i-1]*pows[i-1]
        hash1[i] = (hash1[i-1] + (s1[i-1]-'a'+1)*pows[i-1]) % m;
    }

    vector<int> result;
    long long cur_hash = 0;
    for(size_t i=0; i<=len1-len2; i++)
    {
        cur_hash = (hash1[i+len2] + m - hash1[i]) % m;
        // !cur_hash = cur_hash * pows[i] % m;
        if(cur_hash == hash2 * pows[i] % m)
            result.push_back(i);
    }
    return result;
}

int main()
{
    string s1 = "ababa";
    string s2 = "aba";
    vector<int> indices;
    indices = s1.size()>s2.size()?containing(s1,s2):containing(s2,s1);
    for(auto i : indices)
        cout<<i<<"  ";
}