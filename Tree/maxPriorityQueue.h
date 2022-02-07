//简单的最大优先级队列描述

#ifndef MAXPRIORITYQUEUE
#define MAXPRIORITYQUEUE

template<class T>
class maxPriorityQueue
{
    public:
        virtual ~maxPriorityQueue() {}

        virtual bool empty() const = 0;
        virtual int size() const = 0;

        virtual const T& top() = 0; //返回优先级最大的元素
        virtual void pop() = 0; //删除优先级最大的元素/队首元素
        virtual void push(const T& theElement) = 0;

};

#endif