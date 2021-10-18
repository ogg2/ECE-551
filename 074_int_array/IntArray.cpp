#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {

}
IntArray::IntArray(int n) : data(int[n]), numElements(n) {

}

IntArray::IntArray(const IntArray & rhs)  {
  int newData [numElements];
  for (int i = 0; i < numElements; i++) {
    newData[i] = data[i];
  }
  rhs.data = newData;
  rhs.numElements = newElements;
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
 // IntArray (rhs);
}
const int & IntArray::operator[](int index) const {
  assert (index < numElements);
  return &data[index];
}
int & IntArray::operator[](int index) {
  assert (index < numElements);
  return &data[index];
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
  return !(this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  char printing[16];
  snprintf (printing, 16, %d, rhs.numElements);
  stream.write (printing, strlen(printing));
  return s;
}
