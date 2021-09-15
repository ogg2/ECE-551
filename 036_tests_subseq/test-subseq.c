#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void testing (int array[], size_t size, size_t expectedSize) {
  size_t returnedSize = maxSeq (array, size);
  if (expectedSize != returnedSize) {
    printf("Failed test - Expected: %ld, Size: %ld\n", expectedSize, returnedSize);
    exit(EXIT_FAILURE);
  }
}

int main (void) {
  
  int testArray0[] = {0};
  printf ("Test0\n");
  testing (testArray0, 1, 1);

  int testArray1[] = {0, 1, 1};
  printf ("Test1\n");
  testing (testArray1, 3, 2);
  
  testing (NULL, 0, 0);
  printf ("Test2\n");

  int testArray3[] = {1, 3, 5, 7, 3, 9, 10, 11};
  printf ("Test3\n");
  testing (testArray3, 8, 4);

  int testArray4[] = {1, 2, 1, 2, 4, 5};
  printf ("Test4\n");
  testing (testArray4, 4, 2);

  int testArray5[] = {-4, -4, -3, -1};
  printf ("Test5\n");
  testing (testArray5, 4, 3);

  int testArray6[] = {-4, 0, 1, 2};
  printf ("Test6\n");
  testing (testArray6, 4, 4);

  return EXIT_SUCCESS;
}
