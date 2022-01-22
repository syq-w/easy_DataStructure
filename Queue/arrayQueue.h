#ifndef ARRAYQUEUE
#define ARRAYQUEUE

#include <sstream>

#include "myqueue.h"
#include "myExceptions.h"

template<class T>
class arrayQueue : public myqueue<T>
{
    public:
        arrayQueue(int initialCapacity = 10);
        ~arrayQueue() {delete [] queue; }
        bool empty() const {return theFront == theBack; }
        int size() const
            {return (theBack-theFront+arrayLength) % arrayLength; }
        T& front();
        T& back();
        void pop();
        void push(const T& theElement);

    private:
        int theFront;
        int theBack;
        int arrayLength;
        T* queue;

};

template<class T>
arrayQueue<T>::arrayQueue(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial Capacity = " << initialCapacity << "Must be > 0";
        throw  illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    queue = new T[arrayLength];
    theFront = 0;
    theBack = 0;
}

template<class T>
T& arrayQueue<T>::front()
{
    if(theFront == theBack)
        throw queueEmpty();
    return queue[(theFront+1) % arrayLength];
}

template<class T>
T& arrayQueue<T>::back()
{
    if(theFront == theBack)
        throw queueEmpty();
    return queue[theBack];
}

template<class T>
void arrayQueue<T>::pop()
{
    if(theFront == theBack)
        throw queueEmpty();
    theFront = (theFront+1) % arrayLength;
    queue[theFront].~T();
}

template<class T>
void arrayQueue<T>::push(const T& theElement)
{
    if((theBack+1) % arrayLength == theFront)
    {
        T* newQueue = new T[2*arrayLength];

        int start = (theFront+1) % arrayLength;
        if(start < 2)
            copy(queue + start, queue + start + arrayLength - 1, newQueue);
        else
        {
            copy(queue + start, queue + arrayLength, newQueue);
            copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
        }

        theFront = 2 * arrayLength - 1;
        theBack = arrayLength - 2;
        arrayLength = arrayLength * 2;
        queue = newQueue;
    }

    theBack = (theBack + 1) % arrayLength;
    queue[theBack] = theElement;
}

#endif