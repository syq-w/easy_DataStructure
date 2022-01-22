//链表的单个节点的实现

#ifndef CHAINNODE
#define CHAINNODE

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

#endif