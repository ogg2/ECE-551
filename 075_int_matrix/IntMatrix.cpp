#include "IntMatrix.h"

//IntMatrix myMatrix (r, c) // returns actual object
//IntMatrix myMatrix = new IntMatrix (); //pointer to object
//new always returns pointer

IntMatrix::IntMatrix() : numRows (0), numColumns (0),
                         rows (NULL) {
}

IntMatrix::IntMatrix(int r, int c) : numRows (r), numColumns (c),
                                     rows(new IntArray*[r]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(c);
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs) : numRows (rhs.numRows), 
                                              numColumns (rhs.numColumns),
                                              rows (new IntArray (numColumns)[numRows])  {
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      (*rows[i])[j] = (*rhs.rows[i])[j];
    }
  }
}

IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete[] rows[i];
  }
  delete[] rows;
}

IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray ** temp = new IntArray (rhs.numRows)[rhs.numColumns]; 
    for (int i = 0; i < rhs.numRows; i++) {
      for (int j = 0; j < rhs.numColumns; j++) {
        temp[i][j] = rhs.rows[i][j];
      }
      delete[] rows[i];
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

/*const IntArray & IntMatrix::operator[](int index) const {
  assert (index < numRows && index >= 0);
  return 
}

IntArray & IntMatrix::operator[](int index){

}

bool IntMatrix::operator==(const IntMatrix & rhs) const {

}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {

}*/

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  return s;
}
