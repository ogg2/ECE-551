#include <stdlib.h>
#include <stdio.h>

size_t maxSeq (int * array, size_t n) {
  if (array == NULL) {
    return 0;
  }

  int largestSeq = 1;
  int currentSeq = 1;
  for (int i = 1; i < n; i++) {
    if (array [i] > array[i - 1]) {
      currentSeq++;
      if (currentSeq > largestSeq) {
        largestSeq = currentSeq;
      }
    } else {
      currentSeq = 1;
    }
  }

  return largestSeq;
}
