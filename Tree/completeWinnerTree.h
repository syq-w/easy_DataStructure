//

#ifndef COMPLETEWINNERTREE
#define COMPLETEWINNERTREE

#include "winnerTree.h"
#include "myExceptions.h"

template<class T>
class completeWinnerTree : public winnerTree<T>
{
    public:
        completeWinnerTree(T *thePlayer, int theNumberOfPlayers);
        ~completeWinnerTree() {delete [] tree; }

        void initialize(T*, int);
        int winner() const {return tree[1]; }
        int winner(int i) const {return (i < numberOfPlayers) ? tree[i] : 0; }

        void rePlay(int);  

    private:
        int lowExt; //最低级别的外部节点
        int offset; //最底层最左端内部节点
        int *tree;  //赢者树
        int numberOfPlayers;    //外部节点数目
        T *player;  //外部节点数组

        void play(int, int, int);
};

template<class T>
completeWinnerTree<T>::completeWinnerTree(T *thePlayer, int theNumberOfPlayers)
{
    tree = NULL;
    initialize(thePlayer, theNumberOfPlayers);
}

template<class T>
void completeWinnerTree<T>::initialize(T *thePlayer, int theNumberOfPlayers)
{
    //创建一个赢者树
    int n = theNumberOfPlayers;
    if(n < 2)
        throw illegalParameterValue("Must have at least 2 player");
    player = thePlayer;
    numberOfPlayers = n;
    delete [] tree;
    tree = new int[n];

    //计算s = 2^log2(n-1)
    int i, s;
    for (s = 1; 2 * s <= n - 1; s += s);
    lowExt = 2 * (n - s);
    offset = 2 * s - 1;

    //最低级别的外部节点进行比赛
    for(i = 2; i <= lowExt; i += 2)
        play((offset + i) / 2, i - 1, i);

    //处理剩余的外部节点
    if (n % 2 == 1)
    {
        play(n/2, tree[n - 1], lowExt + 1);
        i = lowExt + 3;
    }
    else
        i = lowExt + 2;

    //i为最左边的剩余外部节点
    for(; i <= n; i += 2)
        play((i - lowExt + n - 1) / 2, i - 1, i);
}

//进行比赛
template<class T>
void completeWinnerTree<T>::play(int p, int leftChild, int rightChild)
{
    tree[p] = (player[leftChild] <= player[rightChild]) ? leftChild : rightChild;

    //如果是竞赛树的右孩子
    while(p % 2 == 1 && p > 1)
    {
        tree[p / 2] = (player[tree[p - 1]] <= player[tree[p]]) ? tree[p - 1] : tree[p];
        p /= 2; //定位到父节点
    }
}

//重新比赛
template<class T>
void completeWinnerTree<T>::rePlay(int thePlayer)
{
    int n = numberOfPlayers;
    if(thePlayer <= 0 || thePlayer > n)
        throw illegalParameterValue("Player index is illegal");

    int matchNode,  //下一个比赛的节点
        leftChild, rightChild;
    
    //寻找第一次比赛的节点
    if(thePlayer <= lowExt)
    {
        matchNode = (offset + thePlayer) / 2;
        leftChild = 2 * matchNode - offset;
        rightChild = leftChild + 1;
    }
    else
    {
        matchNode = (thePlayer - lowExt + n - 1) / 2;
        if(2 * matchNode == n - 1)
        {
            leftChild = tree[2 * matchNode];
            rightChild = thePlayer;
        }
        else
        {
            leftChild = 2 * matchNode - n + 1 + lowExt;
            rightChild = leftChild + 1;
        }
    }

    tree[matchNode] = (player[leftChild] <= player[rightChild]) ? leftChild : rightChild;

    //特殊情况
    if(matchNode == n - 1 && n % 2 == 1)
    {
        matchNode /= 2;
        tree[matchNode] = (player[tree[n - 1]] <= player[lowExt + 1]) ? tree[n - 1] : lowExt + 1;
    }

    //向根节点重赛
    matchNode /= 2;
    for(; matchNode >= 1; matchNode /= 2)
        tree[matchNode] = (player[tree[2 * matchNode]] <= player[tree[2 * matchNode + 1]])
        ? tree[2 * matchNode] : tree[2 * matchNode + 1];
}

#endif