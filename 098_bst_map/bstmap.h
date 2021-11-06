#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <stdexcept>
#include "map.h"

template<typename K, typename V>
class BSTMap : public Map<K,V> {
  public:
    class Node {
      public:
        K key;
        V value;
        Node * left;
        Node * right;
        Node(K k, V v) : key(k), value(v), left(NULL), right(NULL){};
    };
    Node * root;

public:
  BSTMap () : root(NULL) {}

  virtual void add(const K & key, const V & value) {
    root = add (root, key, value);
  }

  virtual Node * add (Node * curr, const K & key, const V & value) {
    if (curr == NULL) {
      Node * newNode = new Node (key, value);
      return newNode;
    } else {
      if (key == curr->key) {
        curr->value = value;
      } else if (key < curr->key) {
        Node * newLeft = add (curr->left, key, value);
        curr->left = newLeft;
      } else {
        Node * newRight = add (curr->right, key, value);
        curr->right = newRight;
      }
    }
    return curr;
  }

  virtual const V & lookup(const K& key) const throw (std::invalid_argument) {
    Node * curr = root;
    while (curr != NULL) {
      if (curr->key == key) {
        return curr->value;
      } else if (key < curr->key) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    try {
      return curr->value;
    } catch (std::invalid_argument & e) {
      std::cerr << e.what();
    }
  }
/*  virtual Node * remove (Node * curr, const K& key) {
    if (curr == NULL) {
      return curr;
    }
    if (curr->key == key) {
      ; //IS THIS RIGHT
    } else {
      if (key < curr->key) {
        Node * parentL = remove (curr->left, key);
        curr->left = parentL;
      } else {
        Node * parentR = remove (curr->right, key);
        curr->right = parentR;
      }
      return curr;
    }

    if (curr->left == NULL) {
      Node * temp = curr->right;
      delete curr;
      return temp;
    } else if (curr->right == NULL) {
      Node * temp = curr->left;
      delete curr;
      return temp;
    } else {
      //NOT REMOVING NODE WITH 2 CHILDREN CORRECTLY
      //NEED TO UPDATE REPLACEMENT NODE'S ORIGINAL PARENT TO POINT TO NULL
      Node * temp = curr;
      curr = curr->left;
      while (curr != NULL) {
        curr = curr->right;
      }
      curr->left = temp->left;
      curr->right = temp->right;
      //NEED TO RETURN EVERYTIME WE CALL A NEW NODE
      //MAY NEED TO UPDATE CODE ABOVE
      return temp;
    }
  }
  virtual Node * closest (Node * curr) {
    if (curr == NULL) {
      return curr;
    }
    return closest (curr->right);
  }
  virtual void remove(const K& key) {
    Node * curr = root;
    while (curr != NULL) {
      if (curr->key == key) {
        Node * ans = remove (curr, key);
      }
    }
    root = remove (root, key);
  }*/

  virtual void remove (const K& key) {
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
        } else {
          //2 CHILDREN
          Node ** toReplace = &(*curr)->left;
          while ((*toReplace)->right != NULL) {
            toReplace = &(*toReplace)->right;
          }
          (*toReplace)->left = (*curr)->left;
          (*toReplace)->right = (*curr)->right;
          delete *curr;
          *curr = *toReplace;
          *toReplace = NULL;
        }

      } else if (key < (*curr)->key) {
        curr = &(*curr)->left;
      } else {
        curr = &(*curr)->right;
      }
    }
  }
  virtual ~BSTMap<K,V>() {
    destroy (root);
  }

  void destroy (Node * curr) {
    if (curr != NULL) {
      destroy (curr->left);
      destroy (curr->right);
      delete curr;
    }
  }
};
#endif
