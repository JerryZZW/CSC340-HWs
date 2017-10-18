#pragma once

#include <exception>
#include <vector>
#include <iostream>
#include <vector>

using namespace std;


template<typename T>
using twoD = std::vector<std::vector<T>>;
//more info on the above: http://stackoverflow.com/a/16861385/3255842

template<class T>
class Matrix {
private:
    int rows;
    int cols;
    twoD<T> matrix;
protected:
    void validSizeCheck(int rows, int cols);

public:
    Matrix(int rows, int cols);

    Matrix(int rows, int cols, twoD<T> newMatrix);

    twoD<T> getMatrix();

    int getRows();

    int getCols();

    void operator=(const Matrix<T> &);

    Matrix<T> &operator+=(const Matrix<T> &);

    Matrix<T> &operator-=(const Matrix<T> &);

    Matrix<T> &operator*=(const Matrix<T> &);

    Matrix<T> &operator*=(const T &);

    /*
    friend void operator<<(ostream &os, const Matrix<T> &m) {
        for (int i = 0; i < m.rows; i++) {
            for (int j = 0; j < m.cols; j++) {
                os << m.matrix[i][j] << " ";
            }
            os << endl;
        }
        os << endl;
        os << endl;
    }
     */

    void printMatrix();


    //T-O-D-O functions are below
    Matrix<T> operator+(const Matrix<T> &);

    Matrix<T> operator-(const Matrix<T> &);

    Matrix<T> operator*(const Matrix<T> &);

    Matrix<T> operator*(const T &);

};

template<class T>
void Matrix<T>::validSizeCheck(int rows, int cols) {
    //DO NOT MODIFY
    //This is a helper function for checking invalid size.
    if (rows < 1 || cols < 1) {
        throw exception();
    }
}


template<class T>
twoD<T> Matrix<T>::getMatrix() {
    //DO NOT MODIFY
    return matrix;
}

template<class T>
int Matrix<T>::getRows() {
    //DO NOT MODIFY
    return rows;
}

template<class T>
int Matrix<T>::getCols() {
    //DO NOT MODIFY
    return cols;
}


template<class T>
Matrix<T>::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    //DO NOT MODIFY
    validSizeCheck(rows, cols);
    matrix.resize(rows);
    for (int i = 0; i < rows; i++) {
        matrix[i].resize(cols);
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
            //cout << "Writing: i: " << i << " j: " << j << " val: " << matrix[i][j] << endl;
        }
    }

}

template<class T>
Matrix<T>::Matrix(int rows, int cols, twoD<T> newMatrix) : rows(rows), cols(cols) {
    //DO NOT MODIFY
    validSizeCheck(rows, cols);
    matrix.resize(rows);
    for (int i = 0; i < rows; i++) {
        matrix[i].resize(cols);
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = newMatrix[i][j];
        }
    }


}

template<class T>
void Matrix<T>::operator=(const Matrix<T> &rhs) {
    //DO NOT MODIFY

    if (rows != rhs.rows || cols != rhs.cols) {
        //throw exception
    }
    Matrix<T> newMatrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newMatrix.matrix[i][j] = rhs.matrix[i][j];
        }
    }
}

template<class T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &rhs) {
    //DO NOT MODIFY
    *this = *this + rhs;
    return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &rhs) {
    //DO NOT MODIFY
    *this = *this - rhs;
    return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &rhs) {
    //DO NOT MODIFY
    *this = *this * rhs;
    return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator*=(const T &rhs) {
    //DO NOT MODIFY
    *this = *this * rhs;
    return *this;
}



template<class T>
void Matrix<T>::printMatrix() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}

//TODO Implement the methods here
//Overload " + " operator
template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &rhs) {
    Matrix<T> newMatrix(rows, cols);
    if(rhs.rows != this->rows || rhs.cols != this->cols) {//When the number of the cols or rows of two matrices are not equal, throw exception
        throw exception();
    }
    else {
        for(int row = 0; row < newMatrix.rows; row++) {
            for(int col = 0; col < newMatrix.cols; col++) {
                newMatrix.matrix[row][col] = matrix[row][col] + rhs.matrix[row][col];
            }
        }
    }
    return newMatrix;
}

//Overload "-" operator
template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &rhs) {
    Matrix<T> newMatrix(rows, cols);
    if(rhs.rows != this->rows || rhs.cols != this->cols) {//When the number of the cols or rows of two matrices are not equal, throw exception
        throw exception();
    }
    else {
        for(int row = 0; row < newMatrix.rows; row++) {
            for(int col = 0; col < newMatrix.cols; col++) {
                newMatrix.matrix[row][col] = matrix[row][col] - rhs.matrix[row][col];
            }
        }
    }
    return newMatrix;
}

//Overload "*" operator
template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &rhs) {
    Matrix<T> newMatrix(rows, rhs.cols);
    if(rhs.rows != this->cols) {//When the number of the rows of the left matrix and the number of cols of right matrix  are not equal, throw exception
        throw exception();
    }
    else {
        for(int i = 0; i < rows; ++i)
            for (int j = 0; j < rhs.cols; ++j)
                for (int k = 0; k < cols; ++k) {
                    newMatrix.matrix[i][j] += matrix[i][k] * rhs.matrix[k][j];
                }
    }
    return newMatrix;
}

//Overload "*" operator
template<class T>
Matrix<T> Matrix<T>::operator*(const T &rhs) {
    Matrix<T> newMatrix(rows, cols);
    for(int row = 0; row < newMatrix.rows; row++) {
        for(int col = 0; col < newMatrix.cols; col++) {
            newMatrix.matrix[row][col] = matrix[row][col] * rhs;
        }
    }
    return newMatrix;
}


