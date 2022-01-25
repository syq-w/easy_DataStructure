//一个通过hash表实现的简单的散列
//该类使用了线性勘察法

#ifndef HASHTABLE
#define HASHTABLE

#include "hash.h"
#include "myExceptions.h"

template<class K, class E>
class hashTable
{
    public:
        hashTable(int theDivisor = 11);
        ~hashTable() {delete [] table; }

        bool empty() const {return dSize == 0; }
        int size() const {return dSize; }

        pair<const K, E>* find(const K&) const;
        void insert(const pair<const K, E>&);

    protected:
        int search(const K&) const;
        pair<const K, E> **table;   //hash表
        hash<K> hash;   //将类型K映射到非负整数
        int dSize;      //字典中的数对数量
        int divisor;    //hash函数除数
};

template<class K, class E>
hashTable<K, E>::hashTable(int theDivisor)
{
    divisor = theDivisor;
    dSize = 0;

    //分配和初始化散列表数组
    table = new pair<const K, E>* [divisor];
    for(int i = 0; i < divisor; ++i)
        table[i] = NULL;
}

//搜索一个公开地址散列表，查找关键字为theKey的数对
//如果匹配的数对存在，则返回它的位置；如果散列表不满，则可以返回可以插入数对的位置
template<class K, class E>
int hashTable<K, E>::search(const K& theKey) const
{
    int i = hash(theKey) % divisor; //起始桶
    int j = i;  //从起始桶开始
    do
    {
        if(table[j] == NULL || table[j]->first == theKey)
            return j;
        j = (j + 1) % divisor;  //下一个桶
    } while (j != i);
    
    return j;   //表满
}

//返回匹配数对的指针
//如果没有匹配，则返回NULL
template<class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey) const
{
    int b = search(theKey);

    if(table[b] == NULL || table[b]->first != theKey)
        return NULL;    //没有匹配

    return table[b];    //完成匹配
}

//将数对thePair插入数对，若存在相同关键字的数对则覆盖值
//若表满则返回异常
template<class K, class E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair)
{
    int b = search(thePair.first);

    if(table[b] == NULL)
    {//没有匹配值但是表也没有满
        table[b] = new pair<const K, E>(thePair);
        dSize++;
    }
    else
    {
        if(table[b]->first == thePair.first)
        {//存在匹配值，选择覆盖现有的值
            table[b]->second = thePair.second;
        }
        else//表已满
            throw hashTableFull();
    }
}

#endif