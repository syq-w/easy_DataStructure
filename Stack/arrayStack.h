//一个数组实现的栈
#ifndef ARRAYSTACK
#define ARRAYSTACK

#include "stack.h"
#include "myExceptions.h"
#include <sstream>

using std::ostringstream;

template<class T>
class arrayStack : public stack<T> 
{
    public:
        arrayStack(int initialCapacity = 10);
        ~arrayStack() {delete [] stack; }

        bool empty() const {return stackTop == -1; }
        int size() const {return stackTop + 1; }

        T& top();
        void pop();
        void push(const T &theElement);

    private:
        void changeLength1D(T*& a, int oldLength, int newLength);   //改变一维数组的长度

        int stackTop;   //栈顶元素索引
        int arrayLength;
        T *stack;
};

//扩大数组长度一倍
template<class T>
void arrayStack<T>::changeLength1D(T*& a, int oldLength, int newLength)
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
arrayStack<T>::arrayStack(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial Capacity = " << initialCapacity << "Must Be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    stack = new T[arrayLength];
    stackTop = -1;
}

template<class T>
T& arrayStack<T>::top()
{
    if(stackTop == -1)
        throw stackEmpty();
    
    return stack[stackTop];
}

template<class T>
void arrayStack<T>::pop()
{
    if(stackTop == -1)
        throw stackEmpty();

    stack[stackTop--].~T();
}

template<class T>
void arrayStack<T>::push(const T& theElement)
{
    if(stackTop == arrayLength - 1)
    {
        changeLength1D(stack, arrayLength, arrayLength*2);
        arrayLength *= 2;
    }

    stack[++stackTop] = theElement;
}

#endif