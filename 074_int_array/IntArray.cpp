#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}

IntArray::IntArray(int n) : data(new int[n]), numElements(n) {
}

//Copy Constructor
IntArray::IntArray(const IntArray & rhs) : data(new int[rhs.numElements]),
                                           numElements (rhs.numElements) {
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}

//Destructor
IntArray::~IntArray() {
  delete[] data;
}

//= operator
IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != & rhs) {
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      temp[i] = rhs.data[i];
    }
    delete[] data;
    numElements = rhs.numElements;
    data = temp;
  }
  return *this;
}
//[] operator
const int & IntArray::operator[](int index) const {
  assert (index < numElements && index >= 0);
  return data[index];
}

//[] operator
int & IntArray::operator[](int index) {
  assert (index < numElements && index >= 0);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements == rhs.numElements) {
    for (int i = 0; i < numElements; i++) {
      if (data[i] != rhs.data[i]) {
        return false;
      }
    }
    return true;
  }
  return false;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  if (rhs.size() != 0) {
    for (int i = 0; i < rhs.size() - 1; i++) {
      s << rhs[i] << ", ";
    }
    s << rhs[rhs.size() - 1];
  }
  s << "}";
  return s;
}
