//数组描述的线性表
//缺少迭代器的使用
#ifndef ARRAYLIST
#define ARRAYLIST

#include "mylinerList.h"

template<class T>
class arrayList : public linearList<T>
{
    public:
        //构造函数、复制构造函数和析构函数
        arrayList(int initialCapacity = 10);

        arrayList(const arrayList<T>&);

        ~arrayList() {delete [] element; }

        //ADT方法
        bool empty() const {return listSize == 0; }

        int size() const {return listSize; }

        T& get(int theIndex) const;

        int indexOf(const T& theElement) const;

        void erase(int theIndex);

        void insert(int theIndex, const T& theElement);

        //void output(ostream& out) const;

        //其他方法
        int capacity() const {return arrayLength; }

    private:
        void checkIndex(int theIndex) const;    //若索引无效则抛出异常
        void changeLength1D(T*& a, int oldLength, int newLength);   //改变一维数组的长度

        T* element;         //存储线性表元素的一维数组
        int arrayLength;    //一维数组的容量
        int listSize;       //线性表的元素个数



};

#endif