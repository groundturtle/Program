/*
 * @Author: avert-win
 * @Date: 2022-04-19 18:46:56
 * @LastEditTime: 2022-10-13 18:11:27
 * @Description: 最长公共子串问题，通过滚动哈希在O(1)时间内求任意子串哈希值，用空间换时间。 
 *    也可以用动态规划方法，更为简单，两种方法时间复杂度同为O(M*N)，空间复杂度同为O(M+N)。
 *         字符串匹配时，hash[i:j]*pow(p, i-1) = hash[j] - hash[i-1]，
 *         因此判断两个字符串是否相等需要一个额外的数，使得所有hash[i:j]右侧所乘的数相等，从而把一个哈希值变为另一个哈希值。
 */

#include<vector>
#include<set>
#include<iostream>
#include<ctime>
#include<algorithm>
#include<unordered_map>

static int m = 1e9+9, p=31;

long long compute_entire_hash(const std::string& s)
{
    int m = 1e9 + 9;
    int p = 31;
    int n = s.length();
    long long p_pow = 1;
    long long hash;
    // for(size_t i=0; i<n; i++)
    for(char c : s)
    {
        hash = (p_pow * (c - 'a' + 1)) % m;
        p_pow = (p*p_pow) % m;
    }
    return hash;
}

/**
 * @brief Compute the hashes of substring whose indices from 0 to i, i<n.
 * 
 * @param s         string.
 * @param p_pows    long long p_pows[n] to recieve powers of p.
 * @param hashes    long long hashes[n+1] to recieve hashes of substrings.
 */
void compute_rolling_hash(const std::string& s, long long* p_pows, long long* hashes, int& p, int& m)
{
    int n = s.length();

    hashes[0] = 0;
    for(size_t i=1; i<=n; i++)
    {
        // hashes[i] = compute_entire_hash(s.substr(0, i));
        hashes[i] = (hashes[i-1] + (s[i-1] - 'a' + 1) * p_pows[i-1]) % m;
    }

    return ;
}

/**
 * @brief Get two strings, return length and the head of common substring.
 * 
 * @param a 
 * @param b 
 * @return std::pair<int, int> 
 */
std::pair<int, int> overlap(std::string& a, std::string& b)
{
    int length_a = a.size(), length_b = b.size(), length_max = length_a > length_b?length_a : length_b;
    long long hashes_a[length_a+1], hashes_b[length_b+1], p_pows[length_max];
    std::unordered_map<long long, int> hash_a;
    long long hash_b = 0;
    p_pows[0] = 1;
    for(size_t i=1; i<length_max; i++)
        p_pows[i] = (p_pows[i-1]*p) % m;
    compute_rolling_hash(a, p_pows, hashes_a, p, m);
    compute_rolling_hash(b, p_pows, hashes_b, p, m);

    long long temp = 0;
    // len
    for(int l=std::min(length_a, length_b); l>=1; l--)
    {
        // start index
        for(int i=0; i<=length_a-l; i++)
        {
            temp = (hashes_a[i+l] - hashes_a[i] + m) % m;
            temp = temp * p_pows[length_max-i-1] % m;
            hash_a[temp] = i;
        }
        for(int i=0; i<=length_b-l; i++)
        {
            hash_b = (hashes_b[i+l] - hashes_b[i] + m) % m;
            hash_b = hash_b * p_pows[length_max-i-1] % m;
            if(hash_a.find(hash_b)!=hash_a.end())
            {
                return std::pair<int,int>(l,i);
            }
        }
    }
    return std::pair<int,int>(0,-1);
}

int main()
{
    std::string s = "abcab-x80xcdeabss[";
    std::string s2 = "cdeab";
    std::string s3 = "-x80cdesss]";

    std::cout<<overlap(s, s2).first<<std::endl;
    std::cout<<overlap(s, s3).first<<std::endl;
    std::cout<<overlap(s2, s3).first<<std::endl;
}