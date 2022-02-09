//二叉搜索树的抽象数据结构描述

#ifndef BSTREE
#define BSTREE

#include "Dictionary/dictionary.h"

template<class K, class E>
class bsTree : public dictionary<K, E>
{
    public:
        virtual void ascend() = 0;  //按关键字升序输出所有数对
};

#endif