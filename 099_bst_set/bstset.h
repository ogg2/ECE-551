#ifndef __BSTSET_H__
#define __BSTSET_H__
#include <stdexcept>
#include "set.h"

template<typename T>
class BstSet : public Set<T> {
private:
  class Node {
    public:
      T key;
      Node * left;
      Node * right;
      Node (T k) : key (k), left (NULL), right (NULL) {}
    };
  Node * root;
public:
  BstSet () : root (NULL) {}
  BstSet (const BstSet<T> & rhs) : root (NULL) {
    copier (rhs.root);
  }
  BstSet<T> & operator=(const BstSet<T> & rhs) {
    if (this != &rhs) {
      destruct (root);
      root = NULL;
      copier (rhs.root);
    }
    return *this;
  }
  void copier (Node * curr) {
    if (curr != NULL) {
      add (curr->key);
      copier (curr->left);
      copier (curr->right);
    }
  }
  
  ~BstSet<T> () {
    destruct (root);
    root = NULL;
  }
  void destruct (Node * curr) {
    if (curr != NULL) {
      destruct (curr->left);
      destruct (curr->right);
      delete curr;
    }
  }

  virtual void add(const T & key) {
    root = add (root, key);
  }
  virtual Node * add (Node * curr, const T & key) {
    if (curr == NULL) {
      Node * newNode = new Node (key);
      return newNode;
    } else {
      if (key == curr->key) {
        ;
      } else if (key < curr->key) {
        Node * newLeft = add (curr->left, key);
        curr->left = newLeft;
      } else {
        Node * newRight = add (curr->right, key);
        curr->right = newRight;
      }
    }
    return curr;
  }

  virtual bool contains(const T& key) const {
    Node * curr = root;
    while (curr != NULL) {
      if (curr->key == key) {
        return true;
      } else if (key < curr->key) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    return false;
  }

  virtual void remove(const T& key) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key == (*curr)->key) {
        if ((*curr)->left == NULL) {
          Node * right = (*curr)->right;
          delete *curr;
          *curr = right;
        } else if ((*curr)->right == NULL) {
          Node * left = (*curr)->left;
          delete *curr;
          *curr = left;
        } else { //2 CHILDREN
          Node ** toReplace = &(*curr)->left;
          while ((*toReplace)->right != NULL) {
            toReplace = &(*toReplace)->right;
          }
          (*curr)->key = (*toReplace)->key;
          Node * temp = (*toReplace)->left;
          delete *toReplace;
          *toReplace = temp;
        }
      } else if (key < (*curr)->key) {
        curr = &(*curr)->left;
      } else {
        curr = &(*curr)->right;
      }
    }
  }
};
#endif
