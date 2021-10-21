#include "IntMatrix.h"
int main (void) {
  IntMatrix a(4,5);
  for (int i = 0; i < a.getRows(); i++) {
    for (int j = 0; j < a.getColumns(); j++) {
      a[i][j] = i+j;
    }
  }
  std::cout << "a is:\n" << a << std::endl;
  return EXIT_SUCCESS;
}
