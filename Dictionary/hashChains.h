//简单的链式散列的实现

#ifndef HASHCHAINS
#define HASHCHAINS

#include <utility>
#include "dictionary.h"
#include "hash.h"

using std::pair;

template<class K, class E>
struct pairNode
{
    typedef pair<const K, E> pairType;
    pairType element;
    pairNode<K, E> *next;

    pairNode(const pairType &thePair) : element(thePair) {}
    pairNode(const pairType &thePair, pairNode<K, E> *theNext)
        :element(thePair)
    {
        next = theNext;
    }
};

template<class K, class E>
class sortedChain : public dictionary<K, E>
{
    public:
        sortedChain() {firstNode = NULL; dSize = 0; }
        ~sortedChain();

        bool empty() const {return dSize == 0; }
        int size() const {return dSize; }

        pair<const K, E>* find(const K&) const;
        void erase(const K&);
        void insert(const pair<const K, E>&);

    protected:
        pairNode<K, E> *firstNode;  //链表头节点
        int dSize;
};

template<class K, class E>
sortedChain<K, E>::~sortedChain()
{
    while(firstNode != NULL)
    {
        pairNode<K, E> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class K, class E>
pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const
{
    pairNode<K, E> *currentNode = firstNode;
    while(currentNode != NULL && currentNode->element.first != theKey)
        currentNode = currentNode->next;

    //判断是否找到元素
    if(currentNode != NULL && currentNode->element.first == theKey)
        return &currentNode->element;

    return NULL;
}

template<class K, class E>
void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
{
    pairNode<K, E> *p = firstNode, *tp = NULL;  //tp跟踪p

    while(p != NULL && p->element.first < thePair.first)
    {//p指向要插入或者要插入的下一个位置
        tp = p;
        p = p->next;
    }

    if(p != NULL && p->element.first == thePair.first)
    {
        p->element.second = thePair.second;
        return;
    }

    pairNode<K, E> *newNode = new pairNode<K, E>(thePair, p);
    if(tp == NULL)
        firstNode = newNode;    //插入到链表第一个节点
    else
        tp->next = newNode;

    dSize++;
    return;
}

template<class K, class E>
void sortedChain<K, E>::erase(const K& theKey)
{
    pairNode<K, E> *p = firstNode, *tp = NULL;

    while(p != NULL && p->element.first < theKey)
    {
        tp = p;
        p = p->next;
    }

    if(p != NULL && p->element.first == theKey)
    {
        if(tp == NULL)
            firstNode = p->next;
        else
            tp->next = p->next;

        delete p;
        dSize--;
    }
}

template<class K, class E>
class hashChains : public dictionary<K, E>
{
    public:
        hashChains(int theDivisor = 11)
        {
            divisor = theDivisor;
            dSize = 0;
            table = new sortedChain<K, E> [divisor];
        }

        ~hashChains() {delete [] table; }

        bool empty() const {return dSize == 0; }
        int size() const {return dSize; }

        pair<const K, E>* find(const K& theKey) const
            {return table[hash(theKey) % divisor].find(theKey); }
        
        void insert(const pair<const K, E> &thePair)
        {
            int matchBucket = hash(thePair.first) % divisor;
            int matchSize = table[matchBucket].size();
            table[matchBucket].insert(thePair);
            if(table[matchBucket].size() > matchSize)
                dSize++;    //字典数对总数+1
        }

        void erase(const K& theKey)
            {table[hash(theKey) % divisor].erase(theKey); }

    protected:
        sortedChain<K, E> *table;   //散列表
        hash<K> hash;   //把类型K映射到一个非整数
        int dSize;
        int divisor;    //散列函数除数

};

#endif