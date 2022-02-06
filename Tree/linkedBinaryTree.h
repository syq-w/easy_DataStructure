//简单的二叉树实现

#ifndef LINKEDBINARYNODE
#define LINKEDBINARYNODE

#include "binaryTree.h"
#include "binaryTreeNode.h"
#include "myExceptions.h"
#include <utility>

using std::pair;

template<class E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E>>
{
    public:
        linkedBinaryTree() {root = NULL; treeSize = 0; }
        ~linkedBinaryTree() {erase(); }

        bool empty() const {return treeSize == 0; }
        int size() const {return treeSize; }

        E* rootElement() const;
        void makeTree(const E& element, 
                linkedBinaryTree<E>&, linkedBinaryTree<E>&);
        linkedBinaryTree<E>& removeLeftSubtree();
        linkedBinaryTree<E>& removeRightSubtree();

        void preOrder(void(*theVisit)(binaryTreeNode<E>*))
            {visit = theVisit; preOrder(root); }
        void inOrder(void(*theVisit)(binaryTreeNode<E>*))
            {visit = theVisit; inOrder(root); }
        void postOrder(void(*theVisit)(binaryTreeNode<E>*))
            {visit = theVisit; postOrder(root); }
        //void levelOrder(void(*)(binaryTreeNode<E> *));

        void erase();
        int height() const {return height(root); }

    protected:
        binaryTreeNode<E> *root;    //指向根节点的指针
        int treeSize;   //树的的节点个数
        static void (*visit)(binaryTreeNode<E>*);   //访问函数
        static int count;   //计数子树上的节点
        static void preOrder(binaryTreeNode<E> *t);
        static void inOrder(binaryTreeNode<E> *t);
        static void postOrder(binaryTreeNode<E> *t);
        static void countNodes(binaryTreeNode<E> *t);
        static void dispose(binaryTreeNode<E> *t) {delete t; }

        static void addToCount(binaryTreeNode<E> *t) {count++; }
        static int height(binaryTreeNode<E> *t);

};

//显式声明
template<>
void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);
// void (*linkedBinaryTree<pair<int,int> >::visit)(binaryTreeNode<pair<int,int> >*);
// void (*linkedBinaryTree<pair<const int,char> >::visit)(binaryTreeNode<pair<const int,char> >*);
// void (*linkedBinaryTree<pair<const int,int> >::visit)(binaryTreeNode<pair<const int,int> >*); 

template<class E>
E* linkedBinaryTree<E>::rootElement() const
{//返回指向根节点元素的指针，若不存在则返回NULL
    if (treeSize == 0)
        return NULL;  
    else
        return &root->element;
}

template<class E>
void linkedBinaryTree<E>::makeTree(const E& element,
            linkedBinaryTree<E>& left, linkedBinaryTree<E>& right)
{//组合左右分支树和元素element创建新树
    root = new binaryTreeNode<E> (element, left.root, right.root);
    treeSize = left.treeSize + right.treeSize + 1;

    //清楚左右分支的访问权限
    left.root = right.root = NULL;
    left.treeSize = right.treeSize = 0;
}

template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeLeftSubtree()
{//移除并返回左子树
    if (treeSize == 0)
        throw emptyTree();

    linkedBinaryTree<E> leftSubtree;
    leftSubtree.root = root->leftChild;
    count = 0;
    leftSubtree.treeSize = countNodes(leftSubtree.root);
    root->leftChild = NULL;
    treeSize -= leftSubtree.treeSize;

    return leftSubtree;
}

template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeRightSubtree()
{//移除并返回右子树
    if (treeSize == 0)
        throw emptyTree();

    linkedBinaryTree<E> rightSubtree;
    rightSubtree.root = root->rightChild;
    count = 0;
    rightSubtree.treeSize = countNodes(rightSubtree.root);
    root->rightChild = NULL;
    treeSize -= rightSubtree.treeSize;
  
    return rightSubtree;
}

template<class E>
void linkedBinaryTree<E>::erase()
{
    postOrder(dispose);
    root = NULL;
    treeSize = 0;
}

template<class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E> *t)
{//前序遍历二叉树
    if (t != NULL)
    {
        linkedBinaryTree<E>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template<class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E> *t)
{//中序遍历二叉树
    if (t != NULL)
    {
        inOrder(t->leftChild);
        linkedBinaryTree<E>::visit(t);
        inOrder(t->rightChild);
    }
}

template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t)
{//后序遍历二叉树
    if (t != NULL)
    {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        linkedBinaryTree<E>::visit(t);
    }
}

/*
template <class E>
void linkedBinaryTree<E>::levelOrder(void(*theVisit)(binaryTreeNode<E> *))
{//层次遍历二叉树
    arrayQueue<binaryTreeNode<E>*> q;
    binaryTreeNode<E> *t = root;
    while (t != NULL)
    {
        theVisit(t);  //访问t

        //将t的孩子插入队列
        if (t->leftChild != NULL)
            q.push(t->leftChild);
         if (t->rightChild != NULL)
             q.push(t->rightChild);

        //提取下一个要访问的节点
        try {t = q.front();}
        catch (queueEmpty) {return;}
        q.pop();
    }
}*/

template<class E>
void linkedBinaryTree<E>::countNodes(binaryTreeNode<E> *t)
{
    visit = addToCount;
    count = 0;
    preOrder(t);
}

template <class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t)
{//返回树的高度
    if (t == NULL)
        return 0;                    
    int hl = height(t->leftChild);
    int hr = height(t->rightChild);
    if (hl > hr)
        return ++hl;
    else
        return ++hr;
}

#endif