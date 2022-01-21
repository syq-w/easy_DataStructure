#include "arrayList.h"
#include "myExceptions.h"

#include <sstream>
#include <algorithm>

using std::ostringstream;
using std::ostream;
using std::find;

template<class T>
arrayList<T>::arrayList(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << "Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}

template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    copy(theList.element, theList.element + listSize, element);
}

//检查索引是否超出数组范围
template<class T>
void arrayList <T>::checkIndex(int theIndex) const
{
    if(theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "Index = " << theIndex << "size = " << listSize;
        throw illegalIndex(s.str());
    }
}

//扩大数组长度一倍
template<class T>
void arrayList<T>::changeLength1D(T*& a, int oldLength, int newLength)
{
    if(newLength < 0)
        throw illegalParameterValue("new length must be >= 0 ");
    T* temp = new T[newLength];
    int number = min(oldLength, newLength); //需要复制的元素个数
    copy(a, a + number, temp);
    delete [] a;    //释放老数组的内存空间
    a = temp;        
}

template<class T>
T& arrayList<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    return element[theIndex];
}

template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{
    int theIndex = find(element, element + listSize, theElement)-element;
    if(theIndex == listSize)
        return -1;
    else return theIndex;
}

template<class T>
void arrayList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    copy(element + theIndex + 1, element + listSize, element + theIndex);
    element[--listSize].~T();
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
    if(theIndex < 0 || theIndex > listSize)
    {
        ostringstream s;
        s << "Index = " << theIndex << "Size = " << listSize;
        throw illegalIndex(s.str());
    }

    if(listSize == arrayLength)
    {
        changeLength1D(element, arrayLength, arrayLength*2);
        arrayLength *= 2;
    }
    copy_backward(element + theIndex, element + listSize, element + listSize + 1);
    element[theIndex] = theElement;
    listSize++;
}
