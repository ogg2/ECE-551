#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.hpp"
typedef LinkedList<int> IntList;

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
    std::cout << "Adding to front" << std::endl;
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
    std::cout << "Adding to Back" << std::endl;
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
    std::cout << "Copy Constructor" << std::endl;
    IntList il;

    il.addFront (4);
    il.addBack (5);
    il.addBack (6);
    IntList copy (il);
    std::cout << copy.getSize() << std::endl;
    assert (copy.getSize() == 3);
    assert (copy.head->data == 4);
    assert (copy.tail->data == 6);
    assert (copy.head->next->data == 5);
    assert (copy.tail->prev->data == 5);
    
    std::cout << "Assignment Operator" << std::endl;
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

    std::cout << "Indexing" << std::endl;
    il.addFront(4);
    il.addFront(5);

    il[0] = 7;
    il[1] = il.head->data;
    assert (il.head->data == 7);
    assert (il.tail->data == 7);
  }

  void testAllocation () {
    IntList il;
    std::cout << "Allocating" << std::endl;
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
    std::cout << "Destroying" << std::endl;
    il.addFront (4);
    il.addBack (5);
    il.addBack (6);
  }

  void testFind () {
    IntList il;
    std::cout << "Finding" << std::endl;
    il.addFront (4);
    il.addBack (5);
    il.addBack (6);
    il.addFront(3);

    assert (il.find (4) == 1);
    assert (il.find (3) == 0);
    assert (il.find (5) == 2);
    assert (il.find (6) == 3);
    assert (il.find (8) == -1);
  }

  void testRemove () {
    IntList il;
    std::cout << "Removing" << std::endl;
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
  t.testFind();
  t.testRemove();
  return EXIT_SUCCESS;
}
