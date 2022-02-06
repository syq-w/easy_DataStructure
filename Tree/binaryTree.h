//简单的二叉树的抽象类

#ifndef BINARYTREE
#define BINARYTREE

#include <functional>

template<class T>
class binaryTree
{
    public:
        virtual ~binaryTree() {}
        virtual bool empty() const = 0;
        virtual int size() const = 0;

        //void (*) (T *)是一种函数类型
        //函数返回值类型为void
        //函数参数类型为T*
        virtual void preOrder(void (*) (T*)) = 0;
        virtual void inOrder(void (*) (T*)) = 0;
        virtual void postOrder(void (*) (T*)) = 0;
        //virtual void levelOrder(void (*) (T*)) = 0;

};

#endif