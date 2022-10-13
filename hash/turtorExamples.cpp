/*
 * @Author: avert-win
 * @Date: 2022-04-19 15:17:10
 * @LastEditTime: 2022-04-19 22:27:42
 * @Description: 字符串的滚动多项式哈希函数，polynomial rolling hash function.
 */
#include<vector>
#include<set>
#include<iostream>
#include<ctime>
#include<algorithm>

/**
 * vector.push_back()需要得到或根据数据构造一个实例,而emplace_back()只需要一个临时对象, 少了一次拷贝过程. 
 *      但是前者可以直接使用值自行构造相应类型,而后者不行,因此不能做到完全替代.
 *      对于错误使用emplace_back()的情况,编译不会通过,因此可以直接使用.
 */


/**
 * * hash(s) = (s[0] + s[1]*p + ... + s[n]*pow(p, n)) % m
 * According to this formula, we have this:
 * * hash(s[i:j])*pow(p, i) = (s[i]*pow(p, i-i) + s[i+1]*pow(p, i+1-i) ... + s[j]*pow(p, j-i)) % m
 * *             = (hash(s[0:j]) - hash(s[0:i-1])) % m
 * To remove the `pow(p, i)` on left but without any division, when we compare two substrings, we are doing this:
 * * hash(substring_left) *= pow(p, pow_substring_right - pow_substring_left)
 * In this way, two hashes have multiplied the same power of p, then we can compare it directly by comparing hash values.

 * Usually set p a prime near the number of different characters, and m a large prime number.
 * The probability of two random strings colliding is about 1/m, that's why m should be last. But why?
 *
 * To improve no-collision probability, use two or more hash function with different p and m.
 * By this way, the probability of collision is equivalent as having one function with m = m*m.
 */

/**
 * @description: Calculating hash value of string.
 * This is for all usages of string hashing.
 * @param str
 * @return {long long} hash_value
 */
long long compute_hash(std::string const& str)
{
    const int p = 31;
    const int m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for(char c:str)
    {
        hash_value = (hash_value + (c-'a'+1)*p_pow) % m;
        p_pow = (p_pow*p) % m;
    }
    return hash_value;
}

/**
 **Example 1
 * @description: Given a list of strings, each no longer than m characters, 
 *               find all the duplicate strings and divide them into groups.
 * @param strs
 * @return groups
 */
std::vector<std::vector<int>> group_identical_strings(std::vector<std::string>const& strs)
{

    // The number of strings inside the vector.
    int n = strs.size();

    // One pair for each string. 
    // What inside a pair are hash value and index.
    std::vector<std::pair<long long, int>> hashes(n);
    for(int i=0; i<n; i++)
    {
        hashes[i] = {compute_hash(strs[i]), i};
    }

    // Sort the hash values so that pairs of similar or the same strings will
    // be close in the vector `hashes`.
    std::sort(hashes.begin(), hashes.end());

    std::vector<std::vector<int>> groups;
    for(int i=0; i<n; i++)
    {
        if(i==0 || hashes[i].first!=hashes[i-1].first)
        {
            groups.emplace_back();
        }
        groups.back().push_back(hashes[i].second);
    }

    return groups;
}

/**
 * *Example 2.
 * @brief Given a string  of length , consisting only of lowercase English 
 *        letters, find the number of different substrings in this string.
 * 
 * @param s 
 * @return int 
 */
int count_unique_substrings(std::string const& s)
{
    int n = s.size();
    const int p = 31;
    const int m = 1e9 + 9;
    
    // Since this function is for comparing substrings, 
    // p_pow of every substring must be recorded according
    // to the formular in the begining of this file.
    std::vector<long long> p_pow(n);
    p_pow[0] = 1;
    for(int i=0; i<n; i++)
    {
        p_pow[i] = (p_pow[i-1]*p) % m;
    }
    
    // Hash values of substrings from s[0:1] to s[0:n].
    std::vector<long long> hashes(n+1, 0);
    for(int i=0; i<n; i++)
    {
        hashes[i+1] = (hashes[i] + (s[i]-'a'+1) * p_pow[i]) % m;
    }

    int cnt = 0;
    std::set<long long> hs;

    /**
     * @brief 从长度为1的字符串开始,计算子串的哈希值并填入集合中.
     *        由于集合的自动去重,每个尺度下的集合大小即为该尺度下不同字符串的数量. 
     * @brief 子串的哈希值计算: 根据文件开头的上述公式以及为避免除法而做的简化,
     *        在这里把最右侧的子串当作标准,每一个子串s[i:j]的哈希值都用以下两步计算:
     *     *  hash(s[i:j]) = (hash(s[0:j]) - hash(s[0:i])) % m
     *     *  hash(s[i:j]) *= p_pow[n]/p_pow[i]
     *        又由于在代码实现中, n是总数而i是从0开始的索引, p_pow的索引最大为n-1,
     *        因此第二步的因数写成了p_pow[n]/p_pow[i-1]的等价形式(实际上取了模,其值并非简单相除得到的.).
     */
    for(int len=1; len<=n; len++)
    {
        hs.clear();
        for(int i=0; i<=n-len; i++)
        {
            long long cur_h = (hashes[i+len] + m - hashes[i]) % m;
            cur_h = (cur_h * p_pow[n-i-1]) % m;
            hs.insert(cur_h);
        }
        cnt += hs.size();
    }
    return cnt;
}


int main()
{
    std::clock_t begin = clock();

    std::string s = "abcdeabcde0x80";
    long long hashes[15];
    std::cout<<"The number of unique substrings:"<<count_unique_substrings(s)<<std::endl;
    std::cout<<"Cost of counting unique substrings is: "<<float(1000*(clock()-begin)/CLOCKS_PER_SEC)<<"ms"<<std::endl;
    begin = clock();
}



/**
 * @ref string hashing: https://cp-algorithms.com/string/string-hashing.html
 * @ref modular multiplicative inverse: https://cp-algorithms.com/algebra/module-inverse.html 
 * @ref 
 */