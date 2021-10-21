#include "IntMatrix.h"

//IntMatrix myMatrix (r, c) // returns actual object
//IntMatrix myMatrix = new IntMatrix (); //pointer to object?
//new always returns pointer

IntMatrix::IntMatrix() : numRows (0), numColumns (0),
                         rows (NULL) {
}

IntMatrix::IntMatrix(int r, int c) : numRows (r), numColumns (c),
                                     rows(new IntArray*[numRows]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs) : numRows (rhs.numRows), 
                                              numColumns (rhs.numColumns),
                                              rows (new IntArray*[numRows])  {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);    
    *rows[i] = *rhs.rows[i];
  }
}

IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}

IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray ** temp = new IntArray*[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      temp[i] = new IntArray(rhs.numColumns);
      *temp[i] = *rhs.rows[i];
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

int IntMatrix::getRows() const {
  return numRows;
}

int IntMatrix::getColumns() const {
  return numColumns;
}

const IntArray & IntMatrix::operator[](int index) const {
  assert (index < numRows && index >= 0);
  return *rows[index];
}

IntArray & IntMatrix::operator[](int index){
  assert (index < numRows && index >= 0);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
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

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert (numRows == rhs.numRows && numColumns == rhs.numColumns);

  IntMatrix newMatrix (numRows, numColumns);
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

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
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
