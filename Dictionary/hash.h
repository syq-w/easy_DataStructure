//一个hash函数将类型K转换为非负整数

#ifndef HASH
#define HASH

#include <string>

using namespace std;

namespace std{
template<class K> class hash;
}
/*
template<>
class hash<string>
{
    public:
        size_t operator()(const string theKey) const
        {
            unsigned long hashValue = 0;
            int length = theKey.length();
            for(int i = 0; i < length; ++i)
                hashValue = 5 * hashValue + theKey[i];

            return size_t(hashValue);
        }
};

template<>
class hash<int>
{
    public:
        size_t operator()(const int theKey) const
        {return size_t(theKey); }
};

template<>
class hash<long>
{
    public:
        size_t operator()(const long theKey) const
        {return size_t(theKey); }
};
*/
#endif