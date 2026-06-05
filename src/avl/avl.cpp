#include "avl.hpp"

int main() {
  avl::Node<int> *root = avl::createNode(10);
  root = avl::insert(root, 12);
  avl::pretty_print(root);
  avl::purge(root);
  return 0;
}
