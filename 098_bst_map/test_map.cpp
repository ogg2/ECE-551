#include <iostream>
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include "bstmap.h"
#include <string>

int main (void) {
  BSTMap<int, std::string> map;

  assert (map.root == NULL);
  map.add (5, "five");
  assert (map.root->key == 5);
  assert (map.root->value == "five");
  map.add (3, "three");
  map.add (9, "nine");
  assert (map.root->left->key == 3);
  assert (map.root->right->key == 9);
  map.add (4, "four");
  assert (map.root->left->right->key == 4);
  map.lookup(2); 
  map.lookup(10); 
  map.lookup(8); 
  map.add (3, "thirty");
  assert (map.lookup(3) == "thirty");
  assert (map.lookup(4) == "four");
  assert (map.lookup(5) == "five");
  assert (map.lookup(9) == "nine");

  map.remove(9);
  assert (map.root->right == NULL);
  map.add (9, "nine");
  assert (map.root->right->key == 9);
  map.remove(4);
  assert (map.root->left->right == NULL);
  map.add (4, "four");
  assert (map.lookup(4) == "four");

  map.remove(8);
  assert (map.root->left->key == 3);
  map.remove(3);
  assert (map.root->left->key == 4);
  assert (map.root->left->left == NULL);
  assert (map.root->left->right == NULL);

  map.remove (4);
  map.add (3, "three");
  map.add (4, "four");
  map.add (0, "zero");
  map.add (2, "two");
  map.add (-1, "-one");
  map.remove (3);
  assert (map.root->left->key == 2);

  return EXIT_SUCCESS;
}
