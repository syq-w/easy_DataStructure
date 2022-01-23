//简单的跳表实现->增加了额外的向前指针的链表

#ifndef SKIPLIST
#define SKIPLIST

#include "dictionary.h"
#include "myExceptions.h"

#include <cmath>
#include <sstream>

using std::ostringstream;

//为了满足跳表多指针域情况而设计的链表节点
template <class K, class E>
struct skipNode 
{
   typedef pair<const K, E> pairType;
   pairType element;
   skipNode<K,E> **next;   // 1D array of pointers

   skipNode(const pairType& thePair, int size)
            :element(thePair){next = new skipNode<K,E>* [size];}
};

template<class K, class E>
class skipList : public dictionary<K, E>
{
    public:
        skipList(K largeKey, int maxPairs = 10000, float prob = 0.5);
        ~skipList();

        bool empty() const {return dSize == 0; }
        int size() const {return dSize; }

        pair<const K, E>* find(const K&) const;
        void erase(const K&);
        void insert(const pair<const K, E>&);

    protected:
        float cutOff;   //用来确定层数
        int levels;     //当前最大的非空链表
        int dSize;      //字典的数对个数
        int maxLevel;   //允许的最大链表层数
        K tailKey;      //最大关键字
        skipNode<K, E> *headerNode; //头节点指针
        skipNode<K, E> *tailNode;   //尾节点指针
        skipNode<K, E> **last;      //last[i]表示i层的最后节点

        int level() const;
        skipNode<K, E>* search(const K&) const;        
};

template<class K, class E>
skipList<K, E>::skipList(K largeKey, int maxPairs, float prob)
{
    cutOff = prob * RAND_MAX;
    maxLevel = ceil(logf(maxPairs) / logf(1/prob)) - 1;
    levels = 0;
    dSize = 0;
    tailKey = largeKey;

    //生成头节点、尾节点和数组last
    pair<K, E> tailPair;
    tailPair.first = tailKey;
    headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);    //头节点
    tailNode = new skipNode<K, E>(tailPair, 0); //尾节点
    last = new skipNode<K, E> *[maxLevel + 1];

    //链表为空时，任意链表的头节点都指向尾节点
    for(int i = 0; i < maxLevel; ++i)
        headerNode->next[i] = tailNode;
}

template<class K, class E>
skipList<K, E>::~skipList()
{
    skipNode<K, E> *nextNode;
    while(headerNode != tailNode)
    {
        nextNode = headerNode->next[0];
        delete headerNode;
        headerNode = nextNode;
    }
    delete tailNode;

    delete [] last;
}

template<class K, class E>
pair<const K, E>* skipList<K, E>::find(const K& theKey) const
{
    //如果没有匹配的数对，返回空
    if(theKey >= tailKey)
        return NULL;
    
    //逐层查找
    skipNode<K, E> *beforeNode = headerNode;    //目标节点的前一个节点
    for(int i = levels; i >= 0; i--)
    {
        while(beforeNode->next[i]->element.first < theKey)
            beforeNode = beforeNode->next[i];
    }

    //检查节点值是否正确
    if(beforeNode->next[0]->element.first == theKey)
        return &beforeNode->next[0]->element;   //取目标地址

    return NULL;    //无匹配值
}

//级的分配方法
//返回一个表示链表级的随机数，该数<=maxLevel
template<class K, class E>
int skipList<K, E>::level() const
{
    int lev = 0;
    while(rand() <= cutOff)
        lev++;
    return (lev <= maxLevel) ? lev : maxLevel;
}

//搜索关键字theKey，并把每一级要查看的最后一个节点存储在last数组中
template<class K, class E>
skipNode<K, E>* skipList<K, E>::search(const K& theKey) const
{
    skipNode<K, E> *beforeNode = headerNode;
    for(int i = levels; i >= 0; i--)
    {
        while(beforeNode->next[i]->element.first < theKey)
            beforeNode = beforeNode->next[i];
        last[i] = beforeNode;   //每一级链表中最接近目标值的节点
    }
    return beforeNode->next[0];
}

template<class K, class E>
void skipList<K, E>::insert(const pair<const K, E>& thePair)
{
    if(thePair.first >= tailKey)
    {
        ostringstream s;
        s << "Key = " << thePair.first << "Must Be < " << tailKey;
        throw illegalParameterValue(s.str());
    }

    skipNode<K, E> *theNode = search(thePair.first);
    //存在相同关键字的节点
    if(theNode->element.first == thePair.first)
    {
        theNode->element.second = thePair.second;
        return;
    }

    //若不存在，确定新节点所在的级链表
    int theLevel = level(); //新节点的级
    if(theLevel > levels)
    {
        theLevel = ++levels;
        last[theLevel] = headerNode;
    }

    //在节点theNode之后插入新节点
    skipNode<K, E> *newNode = new skipNode<K, E>(thePair, theLevel + 1);    //新节点
    for(int i = 0; i <= theLevel; ++i)
    {
        newNode->next[i] = last[i]->next[i];
        last[i]->next[i] = newNode;
    }

    dSize++;
    return;
}

template<class K, class E>
void skipList<K, E>::erase(const K& theKey)
{
    if(theKey >= tailKey)
        return;

    //字典中没有匹配值
    skipNode<K, E> *theNode = search(theKey);
    if(theNode->element.first != theKey)
        return;

    for(int i = 0; i <= levels && last[i]->next[i] == theNode; ++i)
        last[i]->next[i] = theNode->next[i];

    //更新链表级
    while(levels > 0 && headerNode->next[levels] == tailNode)
        levels--;

    delete theNode;
    dSize--;
}

#endif