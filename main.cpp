#include <iostream>

#include "Queue/arrayQueue.h"
#include "Queue/linkedQueue.h"
#include "Lineartable/arrayList.h"
#include "Lineartable/chain.h"
#include "Matrix/matrix.h"
#include "Stack/arrayStack.h"
#include "Stack/linkedStack.h"
#include "Dictionary/skipList.h"
#include "Dictionary/hashTable.h"
#include "Dictionary/hashChains.h"
#include "Tree/linkedBinaryTree.h"
#include "Tree/maxHeap.h"

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
    //a.pop();

    arrayList<int> b(10);
    //b.insert(0,10);
    //b.insert(0,19);

    chain<int> c;

    matrix<int> d(1,2);

    arrayStack<int> e;
    e.push(1);
    e.push(2);
    e.push(3);

    std::cout << e.top() << std::endl;

    linkedStack<int> f;

    linkedQueue<int> g;

    skipList<int, int> h(100);

    hashTable<int, int> i(11);
    pair<int, int> p;
    p.first = 2; p.second = 10;
    i.insert(p);
    p.first = 3; p.second = 20;
    i.insert(p);
    std::cout << i.find(2)->second << std::endl;

    hashChains<int, int> j(11);

    //linkedBinaryTree<int> k;

    maxHeap<int> l(4);
    l.push(10);
    l.push(5);

}
