//继承自二叉树linkedBinaryTree.h
//基于链表描述

#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE

#include "bsTree.h"
#include "linkedBinaryTree.h"

template<class K, class E>
class binarySearchTree : public bsTree<K, E>
                       , public linkedBinaryTree<pair<const K, E>>
{
    public:
        bool empty() const {return treeSize == 0; }
        int size() const {return treeSize; }
        pair<const K, E>* find(const K& theKey) const;
        void insert(const pair<const K, E>& thePair);
        void erase(const K& theKey);

        //void ascend() {inOrderOutput; } 
};

//返回匹配数对的指针
template<class K, class E>
pair<const K, E> binarySearchTree<K, E>::find(const K& theKey) const
{
    binaryTreeNode<pair<const K, E>> *p = root;
    while (p != NULL)
    {
        if(theKey < p->element.first)
            p = p->leftChild;
        else if(theKey > p->element.first)
            p = p->rightChild;
        else
            return &p->element;
    }

    //无匹配
    return NULL;
}

//将一个元素插入到搜索二叉树
/*若支持带有相同关键字元素
*insert中while循环内
*if(thePair.first < p->element.first)
    p = p->leftChild;
*else
    p = p->rightChild;
*/
template<class K, class E>
void binarySearchTree<K, E>::insert(const pair<const K, E>& thePair)
{
    binaryTreeNode<pair<const K, E>> *p = root, *pp = NULL;

    //寻找要插入的位置
    while(p != NULL)
    {
        pp = p; //跟踪p
        if(thePair.first < p->element.first)
            p = p->leftChild;
        else if(thePair.first > p->element.first)
            p = p->rightChild;
        else
        {   //取代旧值
            p->element.second = thePair.second;
            return;
        }
    }

    //插入节点
    binaryTreeNode<pair<const K, E>> *newNode = 
        new binaryTreeNode<pair<const K, E>>(thePair);
    if(root != NULL)
    {
        if(thePair.first < pp->element.first)
            pp->leftChild = newNode;
        else
            pp->rightChild = newNode;
    }
    else
        root = newNode; //空树

    treeSize++;
}

//删除关键字为theKey的节点
template<class K, class E>
void binarySearchTree<K, E>::erase(const K& theKey)
{
    //查找关键字为theKey的节点
    binaryTreeNode<pair<const K, E>> *p = root, *pp = NULL;
    while(p != NULL && p->element.first != theKey)
    {
        pp = p;
        if(theKey < p->element.first)
            p = p->leftChild;
        else
            p = p->rightChild;
    }
    if(p == NULL)
        return; //无匹配值

    //当p有两个孩子时的处理
    //使用左子树最大元素进行替换
    if(p->leftChild != NULL && p->rightChild != NULL)
    {
        //寻找最大元素位置
        binaryTreeNode<pair<const K, E>> *s = p->leftChild, *ps = p;
        while(s->rightChild != NULL)
        {
            ss = s;
            s = s->rightChild;
        }

        binaryTreeNode<pair<const K, E>> *q = 
            new binaryTreeNode<pair<const K, E>>
                (s->element, p->leftChild, p->rightChild);
        if(pp == NULL)
            root = q;   //目标节点是根节点
        else if(p == pp->leftChild)
            pp->leftChild = q;
        else
            pp->rightChild = q;
        
        if(ps == p)
            pp = q;
        else
            pp = ps;
        delete p;
        p = s;
    }

    //pp最多有一个孩子
    binaryTreeNode<pair<const K, E>> *c;
    if(p->leftChild != NULL)
        c = p->leftChild;
    else
        c = p->rightChild;

    if(p == root)
        root = c;   //根节点
    else
    {
        if(p == pp->leftChild)
            pp->leftChild = c;
        else
            pp->rightChild = c;
    }
    treeSize--;
    delete p;
}

#endif