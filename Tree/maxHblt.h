//一个简单的高度优先左高树

#ifndef MAXHBLT
#define MAXHBLT

#include "maxPriorityQueue.h"
#include "linkedBinaryTree.h"
#include "binaryTreeNode.h"
#include "myExceptions.h"
#include "arrayQueue.h"
#include <sstream>
#include <utility>

using std::pair;
using std::ostringstream;

template<class T>
class maxHblt : public maxPriorityQueue<T>, 
                public linkedBinaryTree<pair<int, T>>
{
    public:
        bool empty() const {return treeSize == 0; }
        int size() const {return treeSize; }

        const T& top();
        void pop();
        void push(const T&);
        void initialize(T*, int);

        void meld(maxHblt<T>& theHblt);

    private:
        void meld(binaryTreeNode<pair<int, T>>* &,binaryTreeNode<pair<int, T>>* &);

};

template<class T>
const T& maxHblt<T>::top()
{
    if(treeSize == 0)
        throw queueEmpty();
    return root->element.second;
}

template<class T>
void maxHblt<T>::pop()
{
    if(root == NULL)
        throw queueEmpty();

    binaryTreeNode<pair<int, T>> *left = root->leftChild,
                                *right = root->rightChild;
    delete root;
    root = left;
    meld(root, right);
    treeSize--;
}

template<class T>
void maxHblt<T>::push(const T& theElement)
{
    binaryTreeNode<pair<int, T>> *q = 
        new binaryTreeNode<pair<int, T>>(pair<int, T>(1, theElement));
    meld(root, q);
    treeSize++;
}

template<class T>
void maxHblt<T>::initialize(T* theElement, int theSize)
{
    arrayQueue<binaryTreeNode<pair<int, T>>* > q(theSize);
    erase();    //是的*this为空

    for(int i = 1; i <= theSize; ++i)
        q.push(new binaryTreeNode<pair<int, T>>(pair<int, T>(1, theElement[i])));

    //重复调用合并节点
    for(int i = 1; i <= theSize - 1; ++i)
    {
        binaryTreeNode<pair<int, T>> *b = q.front();
        q.pop();
        binaryTreeNode<pair<int, T>> *c = q.front();
        q.pop();
        meld(b, c);
        q.push(b);
    }
    if(theSize > 0)
        root = q.front();
    treeSize = theSize;
}

template<class T>
void maxHblt<T>::meld(maxHblt<T>& theHblt)
{
    meld(root, theHblt.root);
    treeSize += theHblt.treeSize;
    theHblt.root = NULL;
    theHblt.treeSize = 0; 
}

template<class T>
maxHblt<class T>::meld(binaryTreeNode<pair<int, T>>* &x,
                        binaryTreeNode<pair<int, T>>* &y)
{
    if(y == NULL)   //保持
        return;
    else(x == NULL)
    {
        x = y;
        return;
    }

    //比较元素值大小
    if(x->element.second < y->element.second)
        swap(x, y);
    meld(x->rightChild, y);

    //根据高度交换判断是否交换左右树
    if(x->leftChild = NULL)
    {
        x->leftChild = x->rightChild;
        x->rightChild = NULL;
        x->element.first = 1;
    }
    else
    {
        if(x->leftChild->element.first < x->rightChild->element.first)
            swap(x->leftChild, x->rightChild);
        x->element.first = x->rightChild->element.first + 1;
    }    
}

#endif