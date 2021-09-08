#include <stdlib.h>
#include <stdio.h>

unsigned power (unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_ans);

void run_check (unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans != expected_ans) {
    printf("Expected Ans: %u, Ans: %u\n", expected_ans, ans);
    exit(EXIT_FAILURE);
  }
}

int main (void) {

  run_check(0,8,0);
  run_check(2,0,1);
  run_check(0,0,1);
  
  run_check(2,4,16);

  run_check(10,10,1410065408);
  
  return EXIT_SUCCESS;
}
