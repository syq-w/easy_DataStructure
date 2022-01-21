#include "chain.h"
#include "myExceptions.h"

#include <sstream>
#include <string>

using std::ostringstream;

template<class T>
chain<T>::chain(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial Capacity = " << initialCapacity << "Must Be > 0";
        throw illegalParameterValue(s.str());
    }
    firstNode = NULL;
    listSize = 0;
}

template<class T>
chain<T>::chain(const chain<T> &theList)
{
    listSize = theList.listSize;

    if(listSize == 0)
    {
        firstNode = NULL;
        return;
    }

    //非空链表
    chainNode<T> *sourceNode = theList.firstNode;
    firstNode = new chainNode<T>(sourceNode->element);  //指向链表第一个节点
    sourceNode = sourceNode->next;
    chainNode<T> *targetNode = firstNode;   //跟随新建节点指针

    while(sourceNode != NULL)
    {
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    } 
    targetNode->next = NULL;    //终止节点
}

template<class T>
chain<T>::~chain()
{
    //delete前获取next指针
    while(firstNode != NULL)
    {
        chainNode<T> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

//检查索引是否超出数组范围
template<class T>
void chain<T>::checkIndex(int theIndex) const
{
    if(theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "Index = " << theIndex << "size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template<class T>
T& chain<T>::get(int theIndex) const
{
    checkIndex(theIndex);

    chainNode<T> *currentNode = firstNode;
    for(int i = 0; i < theIndex; i++)
        currentNode = currentNode->next;

    return currentNode->element;
}

template<class T>
int chain<T>::indexOf(const T& theElement) const
{
    chainNode<T> *currentNode = firstNode;
    int index;  //计数要查找值的索引

    while(currentNode != NULL && currentNode->element != theElement)
    {
        currentNode = currentNode->next;
        index++;
    }

    //确保正确找到匹配值
    if(currentNode == NULL)
        return -1;
    else
        return index;
}

template<class T>
void chain<T>::erase(int theIndex)
{
    checkIndex(theIndex);

    chainNode<T> *deleteNode;
    if(theIndex == 0)
    {//删除第一个节点的情况
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else
    {
        chainNode<T> *p = firstNode;
        for(int i = 0; i < theIndex - 1; ++i)
            p = p->next;    //指向到要删除节点的前一个节点
        deleteNode = p->next;
        p->next = p->next->next;
    }
    listSize--;
    delete deleteNode;
}

template<class T>
void chain<T>::insert(int theIndex, const T& theElement)
{
    if(theIndex < 0 || theIndex > listSize)
    {
        ostringstream s;
        s << "Index = " << theIndex << "size = " << listSize;
        throw illegalIndex(s.str());
    }

    if(theIndex == 0)
        //插入到首节点
        firstNode = new chainNode<T>(theElement, firstNode);
    else
    {
        chainNode<T> *p = firstNode;
        for(int i = 0; i < theIndex - 1; ++i)
            p = p->next;    //指向要插入节点位置的前一个节点
        p->next = new chainNode<T>(theElement, p->next);
    }
    listSize++;
}