#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

class Tester;

//YOUR CODE GOES HERE
template <typename T>
class LinkedList{
 public:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL){};
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head (NULL), tail (NULL), size (0) {};
  LinkedList(const LinkedList<T> & rhs) {
    head = rhs.head;
    tail = rhs.tail;
    Node * it = rhs.head;
    while (it != NULL) {
      this->addBack (it->data);
      it = it->next;
    }
    size = rhs.getSize();
  };
  LinkedList<T> & operator=(const LinkedList<T> & rhs);

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }

  void addFront(const T & item) {
    head = new Node (item, head, NULL);
    if (tail == NULL) {
      tail = head;
    } else {
      head->next->prev = head;
    }
    size++;
  }

  void addBack(const T & item) {
    tail = new Node (item, NULL, tail);
    if (head == NULL) {
      head = tail;
    } else {
      tail->prev->next = tail;
    }
    size++;
  }

  bool remove(const T & item) {
    return false;
  }

  T & operator[](int index) {
    return head->data;
  }
  const T & operator[](int index) const {
    return head->data;
  }

  int find(const T & item) {
    return -1;
  }
  int getSize() const {return size;}
  friend Tester;
};

#endif
