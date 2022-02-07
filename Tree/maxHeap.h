//最大优先级队列的堆实现
//大根堆

#ifndef MAXHEAP
#define MAXHEAP

#include "myExceptions.h"
#include "maxPriorityQueue.h"
#include <sstream>

using std::ostringstream;

template<class T>
class maxHeap : public maxPriorityQueue<T>
{
    public:
        maxHeap(int initialCapacity = 10);
        ~maxHeap() {delete [] heap; }

        bool empty() const {return heapSize == 0; }
        int size() const {return heapSize; }

        const T& top();
        void pop();
        void push(const T&);
        void initialize(T*, int);

        void deactivateArray() {heap = NULL; arrayLength = heapSize = 0; }

    private:
        void changeLength1D(T*& a, int oldLength, int newLength);   //改变一维数组的长度

        int heapSize;   //队列中的元素个数
        int arrayLength;    //队列容量
        T *heap;

};

//扩大数组长度一倍
template<class T>
void maxHeap<T>::changeLength1D(T*& a, int oldLength, int newLength)
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
maxHeap<T>::maxHeap(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial Capacity = " << initialCapacity << "Must Be > 0 ";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity + 1;
    heap = new T[arrayLength];
    heapSize = 0;
}

template<class T>
const T& maxHeap<T>::top()
{
    if(heapSize == 0)
        throw queueEmpty();
    return heap[1];
}

template<class T>
void maxHeap<T>::push(const T& theElement)
{
    //队列为满
    if(heapSize == arrayLength - 1)
    {
        changeLength1D(heap, arrayLength, 2*arrayLength);
        arrayLength *= 2;
    }

    //通过比较向上寻找位置
    int currentNode = ++heapSize;   //初始插入位置
    while(currentNode != 1 && heap[currentNode / 2] < theElement)
    {
        heap[currentNode] = heap[currentNode / 2];
        currentNode /= 2;
    }
    heap[currentNode] = theElement;
}

template<class T>
void maxHeap<T>::pop()
{
    //队列为空
    if(heapSize == 0)
        throw queueEmpty();

    heap[1].~T();   //删除根节点
    T lastElement = heap[heapSize--];   //移除最后一个节点

    //寻找最后一个节点的放置位置
    int currentNode = 1,    //最后一个节点位置索引
        child = 2;  //要替换的节点索引
    while(child <= heapSize)
    {
        //比较较大的节点位置的子节点
        if(child < heapSize && heap[child] < heap[child + 1])
            child++;

        //最后一个节点的值最大
        if(lastElement >= heap[child])
            break;
        
        heap[currentNode] = heap[child];
        currentNode = child;    //下移
        child *= 2;
    }
    heap[currentNode] = lastElement;
}

template<class T>
void maxHeap<T>::initialize(T *theHeap, int theSize)
{
    delete [] heap;
    heap = theHeap;
    heapSize = theSize;

    //在root节点处比较
    for(int root = heapSize / 2; root >= 1; root--)
    {
        T rootElement = heap[root];
        int child = 2 * root;

        while(child <= heapSize)
        {
            if(child < heapSize && heap[child] < heap[child + 1])
                child++;
            if(rootElement >= heap[child])
                break;
            heap[child / 2] = heap[child];
            child *= 2;    
        }
        heap[child / 2] = rootElement;
    }
}

#endif