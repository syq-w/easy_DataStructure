//字典的简单实现
//形如<K,V>的数对的集合，K为关键字，V为与关键字对应的值

#ifndef DICTIONARY
#define DICTIONARY

#include <utility>

using std::pair;

template<class K, class E>
class dictionary
{
    public:
        virtual ~dictionary() {}

        virtual bool empty() const = 0;

        virtual int size() const = 0;   //返回字典中数对的数目

        virtual pair<const K, E>* find(const K&) const = 0; //返回匹配数对的指针

        virtual void erase(const K&) = 0;   //删除匹配的数对

        virtual void insert(const pair<const K, E>&) = 0;   //往字典里插入一个数对

};

#endif