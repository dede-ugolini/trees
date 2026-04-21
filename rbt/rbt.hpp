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
  insert_fixup(root, z);
  return root;
}

template <typename T> void right_rotate(Node<T> *&root, Node<T> *x) {
  // Define o node y
  Node<T> *y = x->left;
  // Subtree a esquerda de x vira a Subtree a direita de y
  x->left = y->right;
  if (y->right != NIL<T>()) {
    y->right->parent = x;
  }
  // Liga o pai de x a y
  y->parent = x->parent;

  // Pai de x é NIL então x era a própria raiz
  if (x->parent == NIL<T>()) {
    root = y;
  }

  else if (x == x->parent->right) {
    x->parent->right = y;
  }

  else {
    x->parent->left = y;
  }

  y->right = x;
  x->parent = y;
}

template <typename T> void left_rotate(Node<T> *&root, Node<T> *x) {
  Node<T> *y = x->right;
  x->right = y->left;

  if (y->left != NIL<T>()) {
    y->left->parent = x;
  }

  y->parent = x->parent;
  if (x->parent == NIL<T>()) {
    root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

template <typename T> void insert_fixup(Node<T> *&root, Node<T> *child) {
  while (child->parent->color == RED) {
    // Tio está do lado direito ou é NIL, pai está no lado esquerdo do avô
    if (child->parent == child->parent->parent->left) {
      Node<T> *uncle = child->parent->parent->right;
      // Tio vermelho
      if (uncle->color == RED) {
        // Colorir avô, tio e pai
        uncle->color = BLACK;               // Caso 1
        child->parent->color = BLACK;       // Caso 1
        child->parent->parent->color = RED; // Caso 1
        // Subir a verificação pra cima
        child = child->parent->parent; // Caso 1
      }
      // Tio preto ou NIL
      else {
        // Verificar se é LL (linha) ou LR (Triangulo)
        // Triangulo
        if (child == child->parent->right) { // Caso 2
          // No caso Triangulo deve se rotacionar o pai
          child = child->parent; // Caso 2
          // Rotacionar para a esquerda para a subtree ficar em linha
          left_rotate(root, child); // Caso 2
        }
        // Linha: pende a esquerda
        child->parent->color = BLACK;
        child->parent->parent->color = RED;
        right_rotate(root, child->parent->parent);
      }
    }
    // Tio está do lado esquerdo ou é NIL, pai está no lado direito do avô
    else {
      Node<T> *uncle = child->parent->parent->left;
      if (uncle->color == RED) {
        uncle->color = BLACK;
        child->parent->color = BLACK;
        child->parent->parent->color = RED;
        // Subir a verificação pra cima
        child = child->parent->parent;
      }
      // Tio preto ou NIL
      else {
        // Verificar se é LL (linha) ou LR (Triangulo)
        // Linha: pende a esquerda
        if (child == child->parent->left) {
          right_rotate(root, child->parent->parent);
        }
        // Triangulo
      }
    }
  }
  root->color = BLACK;
}

template <typename T>
void pretty_print(string prefix, Node<T> *&root, bool isLeft) {
  cout << prefix;
  cout << (isLeft ? "├──" : "└──");

  if (root == NIL<T>()) {
    cout << "NIL" << endl;
    return;
  }
  root->color == RED ? cout << COLOR_RED << root->data << COLOR_RESET << endl
                     : cout << root->data << endl;
  pretty_print(prefix + (isLeft ? "│  " : "  "), root->left, true);
  pretty_print(prefix + (isLeft ? "│  " : "  "), root->right, false);
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
