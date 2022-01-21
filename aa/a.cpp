#include "a.h"
#include <iostream>

aa::aa(int a)
{
    a1 = a;
}

aa::~aa()
{

}

void aa::print1(int a)
{
    std::cout << a + a1 << std::endl;
}