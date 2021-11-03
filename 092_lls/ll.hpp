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
  LinkedList() : head (NULL), tail (NULL), size (0) {}
  LinkedList(const LinkedList<T> & rhs) : head (NULL), tail (NULL), size (0) {
    Node * curr = rhs.head;
    while (curr != NULL) {
      this->addBack (curr->data);
      curr = curr->next;
    }
  }

  LinkedList<T> & operator=(const LinkedList<T> & rhs) {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
      size--;
    }
    Node * it = rhs.head;
    while (it != NULL) {
      this->addBack (it->data);
      it = it->next;
    }
    return *this;
  }

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
    Node * curr = head;
    while (curr != NULL) {
      if (curr->data == item) {
        if (size == 1) {
          head = NULL;
          tail = NULL;
        } else if (curr->prev == NULL) {
          curr->next->prev = NULL;
          head = curr->next;
        } else if (curr->next == NULL) {
          curr->prev->next = NULL;
          tail = curr->prev;
        } else {
          Node * currNext = curr->next;
          curr->prev->next = currNext;
          currNext->prev = curr->prev;
        }
        delete curr;
        size--;
        return true;
      }
      curr = curr->next;
    }
    return false;
  }

  T & operator[](int index) {
    int i = 0;
    Node * curr = head;
    while (i < index) {
      curr = curr->next;
      i++;
    }
    return curr->data;
  }
  const T & operator[](int index) const {
    int i = 0;
    Node * curr = head;
    while (i < index) {
      curr = curr->next;
      i++;
    }
    return curr->data;
  }

  int find(const T & item) {
    int index = 0;
    Node * curr = head;
    while (index < size) {
      if (curr->data == item) {
        return index;
      }
      curr = curr->next;
      index++;
    }
    return -1;
  }

  int getSize() const {return size;}
  friend class Tester;
};

#endif
