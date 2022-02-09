//赢者树的抽象数据结构

#ifndef WINNERTREE
#define WINNERTREE

template<class T>
class winnerTree
{
    public:
        virtual ~winnerTree() {}
        virtual void initialize(T* thePlayer, int theNumberOfPlayers) = 0;
        virtual int winner() const = 0; //返回赢者
        virtual void rePlay(int thePlayer) = 0; //根据变化重新竞赛
};

#endif