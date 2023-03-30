/**
 * @file BST_.cpp
 * @author avert-goose (avert-goose@hnu.edu.cn)
 * @brief 实现二叉搜索树，支持插入、删除和搜索。
 * @version 0.1 非递归版本，删除逻辑较为复杂，详见函数注释
 * @date 2023-03-29
 */
#include<bits/stdc++.h>

namespace my
{

struct Node{
    int key;        // 索引
    void* dataptr;          // 与索引绑定的其它数据
    Node* left;
    Node* right;
    Node() : left(nullptr), right(nullptr) {}
    Node(int key) : key(key), left(nullptr), right(nullptr) {}
    Node(int key, void *data) : key(key), left(nullptr), right(nullptr), dataptr(data) {}
};

class BST
{
private:
    Node* root;

public:         // 只需要浅拷贝，由编译器自动生成拷贝构造函数。
    BST() : root(nullptr) {}
    BST(Node* root) : root(root) {}
    ~BST() = default;

/**
 * @brief 用户接口
 * 二叉搜索树用于按key搜索，并不需要实现返回指定节点指针、通过下标索引值等功能。
 */
public:
    void insert(int key, void* data);
    bool search(int key, void*& data_recv);
    bool remove(int key);
};

// BST::~BST(){
//     //todo: 遍历销毁二叉树
// }

/**
 * @brief 分三种情况，一是首次生成节点然后直接返回，而是需要向右，三是需要向左。\n 
 * 可以循环，此处采用递归方式，在while()循环内完成后直接退出函数。
 * 
 * @param key 
 * @param data 
 */
void BST::insert(int key, void* data){
    if(root == nullptr){
        root = new Node(key, data);
        return;
    }
    // 循环向下，直到下一节点为空，插入并返回。
    Node* tmp = root;
    while(true){
        if(key < tmp->key){
            if(tmp->left == nullptr){        // 向左为空，可以插入。下同理。
                tmp->left = new Node(key, data);
                return;
            }
            tmp = tmp->left;
        }
        else{       // 不允许相等索引
            if(tmp->right == nullptr){
                tmp->right = new Node(key, data);
                return;
            }
            tmp = tmp->right;
        }
    }
    // cpu will never come here
}

bool BST::search(int key, void*& data_recv){
    if(root == nullptr)
        return false;
    Node* ret = root;
    while(ret != nullptr){
        if(key < ret->key)
            ret = ret->left;
        else if(key > ret->key)
            ret = ret->right;
        else{
            data_recv = ret->dataptr;        // 找到了返回数据指针，不要直接暴露节点。
            return true;
        }
    }
    return false;             // 找不到返回false。
}

/**
 * @brief 第一步先找节点并保留父节点信息，第二步，根据左右子节点是否存在，分情况进行相应处理。
 * 
 * @param key 欲删除节点的索引
 * @return bool 是否删除成功（节点是否存在）
 */
bool BST::remove(int key){
    Node* target = root;        // 欲删除的节点指针
    Node* father = nullptr;     // 保留父节点信息，当father为null时，代表删除根节点。
    bool leftson = true;
    while (target != nullptr){
        father = target;
        if(key < target->key){
            target = target->left;
            leftson = true;
        }
        else if(key > target->key){
            target = target->right;
            leftson = false;
        }
        else{
            if(target == root)          // 删除根结点
                father = nullptr;
            break;
        }
    }

    // 1. 要删除的节点不存在 
    if(target == nullptr)       
        return false;
    // 2. 左右子节点都存在，从左边往右下方向取最深节点substi，然后更改substi和target父节点共两个节点的相关指针。target即将被舍弃，无所谓。
    else if(target->left && target->right){        
        Node* deepest = target->left;
        while(deepest->right != nullptr){
            if(deepest->right->right == nullptr){        // 若right节点为最终目标，则交换后right应该为null。
                Node* temp = deepest->right;
                deepest->right = nullptr;
                deepest = temp;
            }
            deepest = deepest->right;
        }
        // 代替原target的孩子地位
        if(father && leftson)
            father->left = deepest;
        else if(father)
            father->right = deepest;
        else
            root = deepest;
        // 代替原target的父亲地位。由于本身没有子节点，因此可以直接赋值，无需交换。
        deepest->left = target->left;         // 可以直接赋值，因为本身没有子节点
        deepest->right = target->right;
        // 当target的地位完全被取代后，就可以释放这个节点了。
        delete target;
        return true;
    }
    // 3. target只有一个左子节点，直接改变父节点的子结点指针指向该节点即可。
    else if(target->left){
        if(father && leftson)
            father->left = target->left;
        else if(father)
            father->right = target->left;
        else    
            root = target->left;
    }
    // 4. target只有一个右子节点，同上。
    else if(target->right){
        if(father && leftson)
            father->left = target->right;
        else if(father)
            father->right = target->right;
        else    
            root = target->right;
    }
    return true;
}

} // namespace my


int main(){
    my::BST bst;
    int n = 10;
    for(int i=0; i<n; i++){
        int* data = new int(i);
        bst.insert((i+5), data);
    }
    std::cout<<(bst.remove(7) ? "remoev key." : " key not exists.")<<std::endl;
    std::cout<<(bst.remove(5) ? "remoev key." : " key not exists.")<<std::endl;

    void* recv_data = nullptr;
    std::cout<<(bst.search(14, recv_data) ? "key found." : " key not exists.")<<std::endl;
    std::cout<<"data: "<<(recv_data ? std::to_string(*(int*)recv_data) : "no data")<<std::endl;
}