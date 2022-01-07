#include <iostream>

#include "arrayQueue/arrayQueue.h"

int main()
{
    arrayQueue<int> a(5);
    a.push(10);
    a.push(11);
    a.push(12);

    std::cout << a.back() << std::endl;


    a.pop();
    a.pop();
    a.pop();
    a.pop();

}