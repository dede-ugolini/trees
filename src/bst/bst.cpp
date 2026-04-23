#include "bst.hpp"

int main() {
  bst::Node<int> *root = nullptr;
  root = bst::insert(root, 22);
  root = bst::insert(root, 25);
  root = bst::insert(root, 9);
  root = bst::insert(root, 11);
  bst::pretty_print(root);
  bst::clean(root);
  return 0;
}
