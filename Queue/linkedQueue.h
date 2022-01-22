//基于链表实现的简单队列
//插入元素的一端为队尾(back)
//删除/取出元素的一端为队首(front)

#ifndef LINKEDQUEUE
#define LINKEDQUEUE

#include "myqueue.h"
#include "myExceptions.h"


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


template<class T>
class linkedQueue : public myqueue<T>
{
    public:
        linkedQueue(int initialCapacity = 10) {queueFront = NULL; queueSize = 0; }
        ~linkedQueue();

        bool empty() const {return queueSize == 0; }
        int size() const {return queueSize; }

        T& front();
        T& back();
        void pop();
        void push(const T& theElement);

    private:
        chainNode<T> *queueFront;   //队首
        chainNode<T> *queueBack;    //队尾
        int queueSize;  //队列长度

};

template<class T>
linkedQueue<T>::~linkedQueue()
{
    while(queueFront != NULL)
    {
        chainNode<T> *nextNode = queueFront->next;
        delete queueFront;
        queueFront = nextNode;
    }
}

template<class T>
T& linkedQueue<T>::front()
{
    if(queueSize == 0)
        throw queueEmpty();
    
    return queueFront->element;
}

template<class T>
T& linkedQueue<T>::back()
{
    if(queueSize == 0)
        throw queueEmpty();
    
    return queueBack->element;
}

template<class T>
void linkedQueue<T>::pop()
{//在队首处删除一个元素
    if(queueFront == NULL)
        throw queueEmpty();

    chainNode<T> *nextNode = queueFront->next;
    delete queueFront;
    queueFront = nextNode;
    queueSize--;
}

template<class T>
void linkedQueue<T>::push(const T& theElement)
{//在队尾处添加一个新元素
    chainNode<T> *newNode = new chainNode<T>(theElement, NULL);

    if(queueSize == 0)
        queueFront = newNode;
    else
        queueBack->next = newNode;
    queueBack = newNode;

    queueSize++;
}

#endif