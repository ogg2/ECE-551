#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
//template <typename T> class Matrix;
//template <typename T> std::ostream & operator<<(std::ostream & s, const Matrix<T> & x);

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;
 public:
  Matrix() : numRows (0), numColumns (0), rows (0) {}
  Matrix(int r, int c);
  Matrix(const Matrix<T> & rhs);
  //~Matrix();
  Matrix<T> & operator=(const Matrix<T> & rhs);
  int getRows() const {return numRows;}
  int getColumns() const {return numColumns;}
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix<T> & rhs) const;
  Matrix<T> operator+(const Matrix<T> & rhs) const;
  //template<typename T>
  //friend std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs);
};

template<typename T>
Matrix<T>::Matrix(int r, int c) : numRows (r), numColumns (c),
                                  rows(numRows)  {
  for (int i = 0; i < numRows; i++) {
    rows[i].resize (numColumns);
  }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & rhs) : numRows (rhs.numRows),
                                           numColumns (rhs.numColumns),
                                           rows(rhs.rows) {
  /*for (int i = 0; i < numRows; i++) {
    rows[i] = new std::vector<T> (numColumns);
    rows[i] = rhs.rows[i];
  }*/
}

/*template<typename T>
Matrix<T>::~Matrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}*/

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> & rhs) {
  if (this != &rhs) {
    std::vector <std::vector<T> >  temp (rhs.rows);
    /*for (int i = 0; i < rhs.numRows; i++) {
      //temp[i] = new std::vector (rhs.numColumns);
      temp[i] = rhs.rows[i];
    }*/
    //Delete memory
    /*for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;*/

    rows.clear();

    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = temp;
  }
  return *this;
}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert (index < numRows && index >= 0);
  return rows[index];
}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert (index < numRows && index >= 0);
  return rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  /*if (numRows == rhs.numRows && numColumns == rhs.numColumns) {
    for (int i = 0; i < numRows; i++) {
      if (rows[i] != rhs.rows[i]) {
        return false;
      }
    }
    return true;
  }
  return false;*/
  if (rows != rhs.rows) {
    return false;
  }
  return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert (numRows == rhs.numRows && numColumns == rhs.numColumns);

  Matrix<T> newMatrix (numRows, numColumns);
  for (int i = 0; i < numRows; i++) {
    //IntArray & l = *rows[i];
    //IntArray & r = *rhs.rows[i];
    //IntArray & newIntArray = *newMatrix.rows[i];
    for (int j = 0; j < numColumns; j++) {
      newMatrix[i][j] = (*this)[i][j] + rhs[i][j];
    }
  }
  return newMatrix;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  if (rhs.getRows() != 0) {
    for (int i = 0; i < rhs.getRows() - 1; i++) {
      s << rhs[i] << ",\n";
    }
    s << rhs[rhs.getRows() - 1];
  }
  s << " ]";
  return s;
}

#endif
