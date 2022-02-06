//简单的链表二叉树的节点结构

#ifndef BINARYTREENODE
#define BINARYTREENODE

template<class T>
struct binaryTreeNode
{
    //节点组成元素
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;

    //构造函数
    binaryTreeNode() {leftChild = rightChild = NULL; }
    binaryTreeNode(const T& theElement)
        :element(theElement)
    {
        leftChild = rightChild = NULL;
    }
    binaryTreeNode(const T& theElement, binaryTreeNode *theLeftChild, binaryTreeNode *theRightChild)
        :element(theElement)
    {
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }

};

#endif