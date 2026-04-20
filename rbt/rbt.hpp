#include <iostream>
#include <string>

using namespace std;

namespace rbt {

inline constexpr const char *COLOR_RED = "\x1b[31m";
inline constexpr const char *COLOR_RESET = "\x1b[0m";

enum Color { BLACK, RED };

template <typename T> struct Node {
  T data;
  Color color;
  Node<T> *left;
  Node<T> *right;
  Node<T> *parent;
};

template <typename T> Node<T> *NIL() {
  static Node<T> nil{T{}, BLACK, nullptr, nullptr, nullptr};
  nil.left = nil.right = nil.parent = &nil;
  return &nil;
}

template <typename T> Node<T> *insert(Node<T> *&root, T data) {
  Node<T> *z = new Node<T>{data, RED, NIL<T>(), NIL<T>(), NIL<T>()};
  Node<T> *y = NIL<T>();
  Node<T> *x = root;

  while (x != NIL<T>()) {
    y = x;
    if (z->data < x->data) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  // y é o ultimo node antes de x ser NIL
  z->parent = y;
  if (z->data < y->data) {
    y->left = z;
  } else {
    y->right = z;
  }
  // TODO: Fixup
  return root;
}

template <typename T>
void pretty_print(string prefix, Node<T> *&root, bool isLeft) {
  if (root != NIL<T>()) {
    cout << prefix;
    cout << (isLeft && root->left != NIL<T>() ? "├──" : "└──");
    root->color == RED ? cout << COLOR_RED << root->data << COLOR_RESET << endl
                       : cout << root->data << endl;
    pretty_print(prefix + (isLeft ? "│  " : "  "), root->left, true);
    pretty_print(prefix + (isLeft ? "│  " : "  "), root->right, false);
  }
}

template <typename T> void pretty_print(Node<T> *&root) {
  pretty_print("", root, false);
}

template <typename T> void purge(Node<T> *&root) {
  if (root != NIL<T>()) {
    purge(root->left);
    purge(root->right);
    delete root;
    root = nullptr;
  }
}
} // namespace rbt
