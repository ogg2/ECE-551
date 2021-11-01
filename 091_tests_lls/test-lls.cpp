#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront (4);
    assert (il.head->data == 4);
    assert (il.tail->data == 4);
    assert (il.getSize() == 1);
    assert (il.tail->prev == NULL);

    il.addFront (5);
    assert (il.head->data == 5);
    assert (il.tail->data == 4);
    assert (il.tail->prev->data == 5);
    assert (il.getSize() == 2);
    assert (il.head->next->data == 4);
  }

  void testAddBack () {
    IntList il;
    il.addBack (4);
    assert (il.head->data == 4);
    assert (il.tail->data == 4);
    assert (il.getSize() == 1);
    assert (il.tail->prev == NULL);

    il.addBack (5);
    assert (il.head->data == 4);
    assert (il.tail->data == 5);
    assert (il.tail->prev->data == 4);
    assert (il.getSize() == 2);
    assert (il.head->next->data == 5);
  }
  // many more tester methods

  void testCopyConstructor () {
    IntList il;

    il.addFront (4);
    il.addBack (5);
    il.addBack (6);
    IntList copy (il);
    assert (copy.getSize() == 3);
    assert (copy.head->data == 4);
    assert (copy.tail->data == 6);
    assert (copy.head->next->data == 5);
    assert (copy.tail->prev->data == 5);

    IntList equals;
    equals.addFront (4);
    equals = copy;
    assert (equals.getSize() == 3);
    assert (equals.head->data == copy.head->data);
    assert (equals.tail->data == copy.tail->data);
    assert (equals.head->next->data == copy.head->next->data);
    assert (equals.tail->prev->data == copy.tail->prev->data);
    assert (copy.getSize() == equals.getSize());
  }

  void testIndexing () {
    IntList il;

    il.addFront(4);
    il.addFront(5);

    il[0] = 7;
    il[1] = il.head->data;
    assert (il.head->data == 7);
    assert (il.tail->data == 7);
  }

  void testAllocation () {
    IntList il;
    try {
      il.addFront(4);
    } catch (std::bad_alloc & e) {
      std::cerr << e.what();
    }
    try {
      il.addBack (5);
    } catch (...) {
      std::cerr << "Threw error";
    }
  }

  void testDestructor () {
    IntList il;
    il.addFront (4);
    il.addBack (5);
    il.addBack (6);
  }

  void testRemove () {
    IntList il;
    assert (il.remove(1) == false);
    il.addFront (4);
    assert (il.remove (4) == true);
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
    il.addBack (5);
    il.addBack (4);
    il.addBack (6);
    assert (il.remove (7) == false);
    assert (il.remove (6) == true);
    assert (il.tail->next == NULL);
    assert (il.tail->data == 4);
    assert (il.tail->prev->data == 5);
    assert (il.head->data == 5);
    il.addFront (3);
    il.addFront (2);
    assert (il.remove (3) == true);
    assert (il.head->next->data == 5);
    assert (il.head->next->prev->data == 2);
    assert (il.remove (4) == true);
    assert (il.getSize() == 2);
    il.addFront (8);
    il.addFront (9);
    assert (il.remove (9) == true);
    assert (il.head->prev == NULL);
    assert (il.head->data == 8);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopyConstructor();
  t.testIndexing();
  t.testAllocation();
  t.testDestructor();
  t.testRemove();
  return EXIT_SUCCESS;
}
