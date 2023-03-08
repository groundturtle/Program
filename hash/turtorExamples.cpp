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
 * @ref string hashing: https://cp-algorithms.com/string/string-hashing.html
 * @ref modular multiplicative inverse: https://cp-algorithms.com/algebra/module-inverse.html 
 */

/**
 * @brief 字符串的子串哈希值计算步骤如下：
 * 1. 计算并存储 hash(s[0:i]), i = 0, 1, 2, ..., n;
 * 2. 生成（需要的）子串 s[i:j], 计算并存储 hash(s[i:j]) =( hash(s[0:j]) - hash(s[0:i]]) )* pow(p, n - i)
 * 3. 根据要求取出子串的哈希值进行比较。为防止冲突，可以在哈希值相同时用朴素的方法再进行一次确认。
 * 
 * @brief 若要比较不同来源的字符串，只需将上述步骤2中的因数 pow(p, n - i) 改为 pow(p, m - i), 其中 m 为两字符串中较长者的长度。
 * 
 * 步骤1的时间复杂度为O(n)，步骤二时间代价与子串数量数量级相同，步骤三常数时间复杂度。
 * 由于 pow() 函数本身具有一定的时间消耗，因此使用滚动数组形式，以节省时间。
 * 
 * 使用滚动哈希方法的时空复杂度主要取决于要生成的子串数量。
 * 
 * 以上步骤的推导见下方注释。
 */

/**
 * & hash(s[0:n]) = (s[0] + s[1]*p + ... + s[n]*pow(p, n)) % m
 * According to this formula, we have this:
 * & hash(s[i:j]) = (s[i]*pow(p, 0) + s[i+1]*pow(p, 1) ... + s[j]*pow(p, j-i)) % m
 * By multiplying pow(p,i):
 * & hash(s[i:j])*pow(p,i)          (f1)
 * &        = (s[i]*pow(p,0)*pow(p,i), s[i+1]*pow(p,1)*pow(p,i), ... +s[j]*pow(p,j-i)*pow(p,i))
 * &        = (s[i]*pow(p, i) + s[i+1]*pow(p, i+1) ... + s[j]*pow(p, j)) % m
 * &        = (hash(s[0:j]) - hash(s[0:i-1])) % m
 * 现在，上式相当于从完整的 hash(s[0:n]) 中截取出来的一部分，因此有可能与截取出来的另一部分进行比较。
 * 
 * 当比较两个子串 s[i:j] and s[k:r], 满足 i <= k, 运用以下公式：
 * &    hash(s[i:j]) *= pow(p, k - i)       (f2)
 * 在对两条子字符串分别运用公式 f1 之后，使用上式 f2 ，使得两边乘上了相同的一个因子：pow(p, k)，推导如下
 * &    pow(p, i) * pow(p, k-i)  ==  pow(p, i+k-i)  ==  pow(p, k)
 * 现在就可以不做乘法而直接比较两个字符串了。
 * 
 * 由于大多数时候需要进行比较的不只是一对字符串，因此一般将上述公式 f2 中的 k - i 改为 n - i，
 * 然后将哈希值存储起来，以便随时能取出任意数量的字符串进行比较。
 * 
 * 可以设置多个m，同步进行计算，从而减小哈希冲突概率；
 * 或者在哈希检测认为相同时，进行额外的比较，从而解决哈希冲突带来的问题。
 */


/**
 * @description: Calculating hash value of string.
 * This is for all usages of string hashing.
 * @return {long long} hash_value
 * @complexity: O(n)
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
 * @brief Given a string  of length n, consisting only of lowercase English 
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
     * @brief 子串的哈希值计算: 根据文件开头的公式（尤其f1和f2），
     *        在这里把最右侧的子串当作标准,每一个子串s[i:j]的哈希值都用以下两步计算:
     *     1.  hash(s[i:j]) = (hash(s[0:j]) - hash(s[0:i])) % m
     *     2.  hash(s[i:j]) *= p_pow[n-1] / p_pow[i]
     * 
     *     注意到以上第二步，hash(s[i:j]) 所乘的并非公式中的 pow(p, j-i)，而是换成了pow(p, n-i)，
     *      因此这个公式要对所有字符串同时使用，而且使所有字符串都能通过一次性计算的哈希值进行比较。
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

