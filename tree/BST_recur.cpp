/**
 * @file BST.cpp
 * @author chatGPT3.5
 * @brief 一棵没有析构函数的二叉树类和节点结构体
 * @version 0.1
 * @date 2023-03-29
 */
#include <iostream>

namespace my{


// 二叉搜索树节点的结构体
struct Node {
    int key;
    /* void* data  // 通过key索引的其它数据。*/
    Node* left;
    Node* right;
    Node(int v) : key(v), left(nullptr), right(nullptr) {}
};

/**
 * @brief 二叉树类，内保存根节点指针和操作函数。\n
 * 搜索，插入，删除统一使用递归方法，根据大小以左/右孩子节点为新的根节点进行递归。\n 
 * 1. insertHelper: 由于插入后该位置的父节点的孩子指针需要改变，需返回本节点指针，可为传入的root（不改变）或新建的节点。\n 
 * 2. searchHelper: 搜索同上，但不改变节点，需返回的是目标是否存在、以及目标节点内的数据（如果有）。此处没有数据，只返回bool型。\n 
 * 3. removeHelper: 搜索和返回同1，但删除节点是在非null处，因此根据有无左右子节点分四中情况处理。
 *      - 左右子节点均存在时，选取左子树的最右节点替换上来，然后进入左子树递归删除该节点；
 *      - 只有一个子结点时，直接将该节点整个替换过来即可。因为没有向上的指针，移动子节点不会影响除当前root节点以外任何结点的指针。
 *      - 无子节点时，直接删除。
 * 对于remove操作，当搜索到null时代表错误，需要throw()一个异常。
 */
class BST {
public:
    // 构造函数
    BST() {
        _root = NULL;
    }

    // 插入节点
    void insert(int key) {
        _root = insertHelper(_root, key);
    }

    // 查找节点
    bool search(int key) {
        return searchHelper(_root, key);
    }

    // 删除节点
    void remove(int key) {
        _root = removeHelper(_root, key);
    }

    void traverse();

private:
    // 根节点
    Node* _root;

    /**
     * @brief 递归深入查找，直到当前节点为空时new节点并返回指针。调用者将返回指针赋给子结点指针。
     * 
     * @param root 开始查找的节点
     * @param key 
     * @return Node* 开始查找的节点，可能由null被转为实节点，借由此返回值给新节点的父节点的成员指针赋值。
     */
    Node* insertHelper(Node* root, int key);

    bool searchHelper(Node* root, int key);

    Node* removeHelper(Node* root, int key);

    void inorder(Node* root);
};

Node* BST::insertHelper(Node* root, int key){
    if(!root)                   // 找到了位置，new一个返回。
        root = new Node(key);
    else if(key < root->key)
        root->left = insertHelper(root->left, key);
    else if(key > root->key)
        root->right = insertHelper(root->right, key);
    else        // 重复键
        std::__throw_bad_function_call();
    return root;
}

bool BST::searchHelper(Node* root, int key){
    if(!root)
        return false;
    else if(key < root->key)
        return searchHelper(root->left, key);
    else if(key > root->key)
        return searchHelper(root->right, key);
     // 全部if不通过，证明找到了key == root->key，应返回true
    return true;
}

Node* BST::removeHelper(Node* root, int key){
    // 只在进入时检查是否为空，递归返回值为null并不影响正确性。
    if(!root)       
        std::__throw_bad_function_call();
    else if(key < root->key)
        root->left = removeHelper(root->left, key);
    else if(key > root->key)
        root->right = removeHelper(root->right, key);
    else{
        /**
         * 抛出异常或递归深入，当前节点为目标节点，其中只能有一个真命题，因此要加else!
         * 找到了节点，开始按有无左右子节点分情况处理。
         */
        if(root->left && root->right){
            Node* tmp = root->left;
            while(tmp->right != nullptr)
                tmp = tmp->right;
            // 交换节点数据，避免修改任何指针，避免修改父结点指针的开发麻烦。
            root->key = tmp->key;
            // 现在，要删除的节点从root变成了tmp，递归进入，重新进行一次。
            root->left = removeHelper(root->left, tmp->key);
        }
        else if(root->left){            // 只有左子节点，把左子节点返回去给父节点赋值。
            Node* tmp = root->left;
            delete root;
            root = tmp;
        }
        else if(root->right){
            Node* tmp = root->right;
            delete root;
            root = tmp;
        }
        else{
            delete root;            // 没有子节点，直接删除后赋值为nullptr并返回，调用者的子节点指针即可得到正确清空。
            root = nullptr;
        }
    }
    // 无论是上述哪种情况，root作为返回值都能保证正确性。
    return root;            
}

void BST::traverse(){
    inorder(_root);
}

void BST::inorder(Node* root){
    if(root == nullptr)
        return;
    inorder(root->left);
    std::cout<<root->key<<" ";
    inorder(root->right);
    return;
}

};

int main(){
    my::BST bst;
    int n = 10;
    for(int i=0; i<n; i++){
        bst.insert(i+5);
        // std::cout<<bst.search(i+5)<<" ";        // 验证是否插入成功
        // std::cout<<(i+5)<<" ";
    }
    std::cout<<std::endl;
    try{
        bst.remove(5);
        bst.remove(6);
        bst.remove(7);
        // bst.remove(7);
    }
    catch(std::exception e){
        std::cout<<"key not exists, "<<e.what()<<std::endl;
        return 0;
    }

    bst.traverse();
}