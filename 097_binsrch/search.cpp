#include <cstdlib>
#include <cstdio>
#include "function.h"
#include <cmath>
#include <iostream>

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while (low < high) {
    int middle = (low + high) / 2;
    int ans = f->invoke (middle);
    if (ans == 0) {
      return middle;
    } else if (ans < 0) {
      low = middle + 1;
    } else {
      high = middle;
    }
  }
  return low;
}
  /*if (f->invoke(middle) == 0 || low < high) {
    return middle;
  } else if (f->invoke(middle) < 0) {
    middle = binarySearchForZero(f, middle + 1, high);
  } else {
    middle = binarySearchForZero(f, low, middle);
  }*/
