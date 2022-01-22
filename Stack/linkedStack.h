//基于链表实现的栈
//先进后出

#ifndef LINKEDSTACK
#define LINKEDSTACK

#include "stack.h"
#include "myExceptions.h"
#include <sstream>

using std::ostringstream;

/*
template<class T>
struct chainNode
{
    //数据成员
    T element;
    chainNode<T> *next;

    //实现方法
    chainNode() {}
    chainNode(const T& element)
    {
        this->element = element;
    }
    chainNode(const T& element, chainNode<T> *next)
    {
        this->element = element;
        this->next = next;
    }
};
*/

template<class T>
class linkedStack : public stack<T>
{
    public:
        linkedStack(int initialCapacity = 10) {stackTop = NULL; stackSize = 0; }
        ~linkedStack();

        bool empty() const {return stackSize == 0; }
        int size() const {return stackSize; }

        T& top();
        void pop();
        void push(const T& theElement);

    private:
        chainNode<T> *stackTop; //  指向栈顶
        int stackSize;  //栈中的元素个数
};

template<class T>
linkedStack<T>::~linkedStack()
{
    while(stackTop != NULL)
    {
        chainNode<T> *nextNode = stackTop->next;
        delete stackTop;
        stackTop = nextNode;
    }
}

template<class T>
T& linkedStack<T>::top()
{
    if(stackSize == 0)
        throw stackEmpty();
    return stackTop->element;
}

template<class T>
void linkedStack<T>::pop()
{
    if(stackSize == 0)
        throw stackEmpty();
    
    chainNode<T> *nextNode = stackTop->next;
    delete stackTop;
    stackTop = nextNode;
    stackSize--;
}

template<class T>
void linkedStack<T>::push(const T& theElement)
{
    stackTop = new chainNode<T>(theElement, stackTop);
    stackSize++;
}

#endif