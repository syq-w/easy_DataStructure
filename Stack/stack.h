//一个栈的抽样类
//先进后出

#ifndef STACK
#define STACK

template<class T>
class stack
{
    public:
        virtual ~stack() {}
        virtual bool empty() const = 0;
        virtual int size() const = 0;
        //返回栈顶元素
        virtual T& top() = 0;
        //删除栈顶元素
        virtual void pop() = 0;
        //在栈顶处添加一个新元素
        virtual void push(const T& theElement) = 0;
};

#endif