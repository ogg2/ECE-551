#include <cstdlib>
#include "function.h"
#include <cmath>
#include <iostream>

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while (low < high) {
    int middle = (low + high) / 2;
    if (f->invoke (middle) == 0) {
      return middle;
    } else if (f->invoke (middle) < 0) {
      low = middle + 1;
    } else {
      high = middle;
    }

  }
  /*if (f->invoke(middle) == 0 || low < high) {
    return middle;
  } else if (f->invoke(middle) < 0) {
    middle = binarySearchForZero(f, middle + 1, high);
  } else {
    middle = binarySearchForZero(f, low, middle);
  }*/
  
  return low;
}
