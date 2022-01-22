#ifndef MATRIX
#define MATRIX
//基于数组的二维矩阵实现

#include "myExceptions.h"

template<class T>
class matrix
{
    public:
        matrix(int theRows = 0, int theColumns = 0);
        matrix(const matrix<T>&);
        ~matrix() {delete [] element; }

        int rows() const {return theRows; }
        int columns() const {return theColumns; }

        T& operator() (int i, int j) const;
        matrix<T>& operator=(const matrix<T>&);
        //matrix<T> operator+() const;
        matrix<T> operator+(const matrix<T>&) const;
        matrix<T> operator-() const;
        matrix<T> operator-(const matrix<T>&) const;
        matrix<T> operator*(const matrix<T>&) const;
        matrix<T>& operator+=(const T&);

    private:
        int theRows;    //矩阵的行数
        int theColumns; //矩阵的列数

        T *element;
};

template<class T>
matrix<T>::matrix(int theRows, int theColumns)
{
    if(theRows < 0 || theColumns < 0)
        throw illegalParameterValue("Rows or Columns must be >= 0");
    if((theRows == 0 || theColumns == 0)
            && (theRows != 0 || theColumns != 0))
    {
        throw("Either both or neither rows and columns should be zeros");
    }

    this->theRows = theRows;
    this->theColumns = theColumns;
    element = new T[theRows*theColumns];
}

template<class T>
matrix<T>::matrix(const matrix<T> &m)
{
    theRows = m.theRows;
    theColumns = m.theColumns;
    element = new T[theRows*theColumns];

    copy(m.element, m.element + theRows*theColumns, element);
}

template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
    if(this != m)
    {
        delete [] element;
        theRows = m.theRows;
        theColumns = m.theColumns;
        element = new T[theRows*theColumns];

        copy(m.element, m.element + theRows*theColumns, element);
    }
    return *this;
}

template<class T>
T& matrix<T>::operator()(int i, int j) const
{
    if(i < 1 || i > theRows || j < 1 || j > theColumns)
        throw matrixIndexOutOfBounds();
    return element[(i - 1)*theColumns + j - 1];
}

template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m) const
{
    if(theRows != m.theRows || theColumns != m.theColumns)
        throw matrixSizeMismatch();

    matrix<T> w(theRows, theColumns);
    for(int i = 0; i < theRows*theColumns; ++i)
        w.element[i] = element[i] + m.element[i];
    
    return w;
}

template<class T>
matrix<T> matrix<T>::operator-(const matrix<T>& m) const
{
    if(theRows != m.theRows || theColumns != m.theColumns)
        throw matrixSizeMismatch();

    matrix<T> w(theRows, theColumns);
    for(int i = 0; i < theRows*theColumns; ++i)
        w.element[i] = element[i] - m.element[i];
    
    return w;
}

template<class T>
matrix<T> matrix<T>::operator-() const
{
    matrix<T> w(theRows, theColumns);
    for(int i = 0; i < theRows*theColumns; ++i)
        w.element[i] = -element[i];
    
    return w;
}

template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m) const
{//return w = (*this) * m
    if(theColumns != m.theRows)
        throw matrixSizeMismatch();
    
    matrix<T> w(theRows, m.theColumns); //相乘后的矩阵
    int ct = 0; //索引(*this)相乘处的量值
    int cm = 0; //索引m相乘处的量值
    int cw = 0; //相乘后矩阵的索引

    for(int i = 1; i <= theRows; ++i)
    {
        for(int j = 1; j <= m.theColumns; ++j)
        {
            T sum = element[ct] * m.element[cm];

            for(int k = 2; k <= theColumns; ++k)
            {
                ct++;
                cm += m.theColumns;
                sum += element[ct] * m.element[cm]; //(*this)的行向量乘以m的列向量
            }

            w.element[cw++] = sum;  //  保存w(i,j)
            ct -= theColumns - 1;
            cm = j;
        }//完成(*this)的一个行向量的相乘运算

        ct += theColumns;
        cm = 0;
    }

    return w;
}

template<class T>
matrix<T>& matrix<T>::operator+=(const T& x)
{
    for(int i = 0; i < theRows*theColumns; ++i)
        element[i] += x;
    return *this;
}

#endif