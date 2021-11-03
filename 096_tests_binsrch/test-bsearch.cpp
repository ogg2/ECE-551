#include "function.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <assert.h>

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n),
                                                                    f(fn),
								                                                    mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class SinFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return 10000000 * (sin(arg/100000.0) - 0.5);
  }
};

class LinearFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return arg;
  }
};


class MyFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return arg + 10;
  }
};

void check(Function<int,int> * f, int low, int high, int expected_ans,
           const char * mesg) {
  int max = std::log2(high-low) + 1;
  CountedIntFn * counted = new CountedIntFn(max, f, mesg);
  int ans = binarySearchForZero (counted, low, high);

  assert (ans == expected_ans);
}

int main (void) {
  SinFunction * sin = new SinFunction();
  check (sin,  0, 150000, 52359, "Sin Function");

  LinearFunction * lin = new LinearFunction();
  check (lin, -20, 10, 0, "Neg Linear Function");
  check (lin, 1, 10, 1, "Pos Linear Function");
  check (lin, 0, 1, 0, "Pos Linear Function");
  check (lin, -100, 1, 0, "Pos Linear Function");
  
  MyFunction * myFn = new MyFunction();
  check (myFn, -200000000, -1000000, -1000001, "Random Function");
  check (myFn, -20, 10, -10, "Randot Function");

  return EXIT_SUCCESS;
}
