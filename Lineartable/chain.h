//一个单向链表简单实现
#ifndef CHAIN
#define CHAIN

#include "mylinerList.h"

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
    chainNode(const T* element, chainNode<T> *next)
    {
        this->element = element;
        this->next = next;
    }
};

//缺少了迭代器的使用
//仅仅是单向链表的实现
//需要补充环形链表、双向链表等
template<class T>
class chain : public linearList<T>
{
    public:
        //构造函数、复制构造函数及析构函数
        chain(int initialCapacity = 10);
        chain(const chain<T>&);
        ~chain();

        //ADT方法实现
        bool empty() const {return listSize == 0; }

        int size() const {return listSize; }

        T& get(int theIndex) const;

        int indexOf(const T& theElement) const;

        void erase(int theIndex);

        void insert(int theIndex, const T& theElement);

    protected:
        void checkIndex(int theIndex) const;    //若索引无效则抛出异常
        chainNode<T> *firstNode;    //指向链表第一个节点的指针
        int listSize;   //链表元素个数


};

#endif