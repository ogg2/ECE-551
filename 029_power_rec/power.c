#include <stdlib.h>
#include <stdio.h>

unsigned power_helper (unsigned x, unsigned y, unsigned ans) {
  if (y == 0) {
    return ans * 1;
  }

  return power_helper(x, y - 1, ans * x);
}

unsigned power(unsigned x, unsigned y) {
  return power_helper(x, y, 1);
}
