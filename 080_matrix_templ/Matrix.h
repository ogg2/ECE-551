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
    std::vector<T> ** rows;
  public:
    Matrix() : numRows (0), numColumns (0), rows (NULL) {}

    Matrix(int r, int c) : numRows (r), numColumns (c),
                           rows(new std::vector<T> * [numRows])  {
      for (int i = 0; i < numRows; i++) {
        rows[i] = new std::vector<T> (numColumns);
      }
    }

    Matrix(const Matrix & rhs) : numRows (rhs.numRows),
                                 numColumns (rhs.numColumns),
                                 rows(new std::vector<T> * [numRows]) {
      for (int i = 0; i < numRows; i++) {
        rows[i] = new std::vector<T> (rhs[i]);
        //rows[i] = rhs.rows[i];
      }
    }

    ~Matrix() {
      for (int i = 0; i < numRows; i++) {
        delete rows[i];
      }
      delete[] rows;
    }

    Matrix & operator=(const Matrix & rhs) {
      if (this != &rhs) {
        std::vector<T> ** temp = new std::vector<T> * [rhs.numRows];
        for (int i = 0; i < rhs.numRows; i++) {
          temp[i] = new std::vector<T> (rhs[i]);
          //temp[i] = rhs.rows[i];
        }
        //Delete memory
        for (int i = 0; i < numRows; i++) {
          delete rows[i];
        }
        delete[] rows;

        numRows = rhs.numRows;
        numColumns = rhs.numColumns;
        rows = temp;
      }
      return *this;
    }

    int getRows() const {return numRows;}
    int getColumns() const {return numColumns;}

    const std::vector<T> & operator[](int index) const {
      assert (index < numRows && index >= 0);
      return *rows[index];
    }
    std::vector<T> & operator[](int index) {
      assert (index < numRows && index >= 0);
      return *rows[index];
    }

    bool operator==(const Matrix & rhs) const {
      if (numRows == rhs.numRows && numColumns == rhs.numColumns) {
        for (int i = 0; i < numRows; i++) {
          if (*rows[i] != *rhs.rows[i]) {
            return false;
          }
        }
        return true;
      }
      return false;
    }
    Matrix operator+(const Matrix & rhs) const {
      assert (numRows == rhs.numRows && numColumns == rhs.numColumns);

      Matrix newMatrix (numRows, numColumns);
      for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
          newMatrix[i][j] = (*this)[i][j] + rhs[i][j];
        }
      }
      return newMatrix;
    }
    //template<typename T>
    //friend std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs);
};

/*template<typename T>
Matrix::Matrix(int r, int c) : numRows (r), numColumns (c),
                               rows(new std::vector<T> * [numRows])  {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new std::vector<T> (numColumns);
  }
}

template<typename T>
Matrix::Matrix(const Matrix & rhs) : numRows (rhs.numRows),
                                     numColumns (rhs.numColumns),
                                     rows(new std::vector<T> * [numRows]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new std::vector<T> (rhs[i]);
    //rows[i] = rhs.rows[i];
  }
}

template<typename T>
Matrix::~Matrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}

template<typename T>
Matrix & Matrix::operator=(const Matrix & rhs) {
  if (this != &rhs) {
    std::vector<T> ** temp = new std::vector<T> * [rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      temp[i] = new std::vector (rhs[i]);
      //temp[i] = rhs.rows[i];
    }
    //Delete memory
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;

    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = temp;
  }
  return *this;
}

template<typename T>
const std::vector<T> & Matrix::operator[](int index) const {
  assert (index < numRows && index >= 0);
  return *rows[index];
}

template<typename T>
std::vector<T> & Matrix::operator[](int index) {
  assert (index < numRows && index >= 0);
  return *rows[index];
}

template<typename T>
bool Matrix::operator==(const Matrix & rhs) const {
  if (numRows == rhs.numRows && numColumns == rhs.numColumns) {
    for (int i = 0; i < numRows; i++) {
      if (*rows[i] != *rhs.rows[i]) {
        return false;
      }
    }
    return true;
  }
  return false;
}

template<typename T>
Matrix Matrix::operator+(const Matrix & rhs) const {
  assert (numRows == rhs.numRows && numColumns == rhs.numColumns);

  Matrix newMatrix (numRows, numColumns);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      newMatrix[i][j] = (*this)[i][j] + rhs[i][j];
    }
  }
  return newMatrix;
}*/

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

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  s << "{";
  if (rhs.size() != 0) {
    for (size_t i = 0; i < rhs.size() - 1; i++) {
      s << rhs[i] << ", ";
    }
    s << rhs[rhs.size() - 1];
  }
  s << "}";
  return s;
}

#endif
