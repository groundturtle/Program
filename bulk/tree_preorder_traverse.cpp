/*
 * @Author: avert
 * @Date: 2022-03-09 22:59:27
 * @LastEditTime: 2022-03-10 00:08:28
 * @Description: 给出一棵树的中序和后续排列，求先序排列。
 */

// 2022.03.10, 0:08

/**
 * 后序遍历：左、右、中(父)
 * 中序遍历：左、中、右
 * 前序遍历：中、左、右
 * 后序遍历的最后一个节点是根节点，在中序排列中找出这个节点，
 * 就能够区分左子树和右子树。假设其分别有n个和m个节点，
 * 则在后序序列中，前n个和紧接着的m个分别属于该左子树和右子树。
 * 将以上过程封装成函数，递归进行。
 */

/**
 * 传参左子树和右子树；
 * 传参指针，后序序列的最后一个就加进去。
 * 最后采取的方式是定义一个全局变量。这是一种不安全的方法，只需要改函数接口就能避免。
 */

#include<iostream>
#include<assert.h>

std::string pre_tree = "";

void findroot(std::string mid_traversal, std::string post_traversal)
{

    if(post_traversal.length() == 0)
    {
        return ;
    }
    if(post_traversal.length() == 1)
    {
        pre_tree += post_traversal;
        return ;
    }

    size_t post_index = mid_traversal.length();
    size_t mid_index = mid_traversal.find_first_of( post_traversal[post_index-1] );
    size_t lef_len = mid_index;
    size_t right_len = post_index - lef_len - 1;
    std::string lef_mid = mid_traversal.substr(0, lef_len);
    std::string right_mid = mid_traversal.substr(mid_index + 1, right_len);   // mid_index is already an index.
    std::string lef_post = post_traversal.substr(0, lef_len);
    std::string right_post = post_traversal.substr(lef_len, right_len);

    assert(lef_len + right_len == post_index -1);

    pre_tree += post_traversal[post_index-1];

    findroot(lef_mid, lef_post);
    findroot(right_mid, right_post);
}


int main()
{
    std::string mid_traversal, post_traversal;
    std::cin>>mid_traversal>>post_traversal;
    findroot(mid_traversal, post_traversal);
    std::cout<<pre_tree;
}