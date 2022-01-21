#ifndef MATRIX
#define MATRIX
//基于数组的二维矩阵实现

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

#endif