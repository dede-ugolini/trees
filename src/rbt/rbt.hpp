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
        // Triangulo
        if (child == child->parent->left) {
          child = child->parent; // Caso 2
          right_rotate(root, child->parent->parent);
        }
        // Linha: pende a direita
        child->parent->color = BLACK;
        child->parent->parent->color = RED;
        left_rotate(root, child->parent->parent);
      }
    }
  }
  root->color = BLACK;
}

template <typename T> Node<T> *search(Node<T> *&root, T data) {
  Node<T> *x = root;
  while (x != NIL<T>()) {
    if (data < x->data) {
      x = x->left;
    } else if (data > x->data) {
      x = x->right;
    } else {
      return x;
    }
  }
  return NIL<T>();
}

template <typename T> Node<T> *min(Node<T> *&root) {
  Node<T> *x = root;
  while (x->left != NIL<T>()) {
    x = x->left;
  }
  return x;
}

template <typename T> void transplant(Node<T> *&root, Node<T> *u, Node<T> *v) {
  if (u->parent == NIL<T>()) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

template <typename T> void remove(Node<T> *&root, T data) {
  Node<T> *target = search(root, data);
  if (target == NIL<T>()) {
    return;
  }
  Node<T> *x = NIL<T>();
  Node<T> *y = target;
  Color y_original_color = y->color;
  if (target->left == NIL<T>()) {
    x = target->right;
    transplant(root, target, target->right);
  } else if (target->right == NIL<T>()) {
    x = target->left;
    transplant(root, target, target->left);
  } else {
    y = min(target->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == target) {
      x->parent = y;
    } else {
      transplant(root, y, y->right);
      y->right = target->right;
      y->right->parent = y;
    }
    y->left = target->left;
    y->left->parent = y;
    y->color = target->color;
    transplant(root, target, y);
  }
  if (y_original_color == BLACK) {
    remove_fixup(root, y);
  }
  delete target;
}

template <typename T> void remove_fixup(Node<T> *&root, Node<T> *child) {
  while (child != root && child->color == BLACK) {
    // Child está do lado esquerdo e irmão do lado direito
    if (child == child->parent->left) {
      Node<T> *w = child->parent->right;
      if (w->color == RED) {
        w->color = BLACK;
        w->parent->color = RED;
        left_rotate(root, child->parent);
        w = child->parent->right;
      }
      if (w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        child = child->parent;
      } else if (w->right->color == BLACK) {
        w->left->color = BLACK;
        w->color = RED;
        right_rotate(root, w);
        w = w->parent->right;
      }
    }
    // Child está do lado direito e irmão do lado esquerdo
    else {
      Node<T> *w = child->parent->left;
      if (w->color == RED) {
        w->color = BLACK;
        w->parent->color = RED;
        right_rotate(root, child->parent);
        w = child->parent->left;
      }
      if (w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        child = child->parent;
      } else if (w->left->color == BLACK) {
        w->right->color = BLACK;
        w->color = RED;
        left_rotate(root, w);
        w = w->parent->left;
      }
    }
  }
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

template <typename T> void in_order_walk(Node<T> *&root) {
  if (root == NIL<T>()) {
    return;
  }
  in_order_walk(root->left);
  root->color == RED
      ? std::cout << COLOR_RED << root->data << COLOR_RESET << std::endl
      : std::cout << root->data << std::endl;
  in_order_walk(root->right);
}

template <typename T> void pre_order_walk(Node<T> *&root) {
  if (root == NIL<T>()) {
    return;
  }
  root->color == RED
      ? std::cout << COLOR_RED << root->data << COLOR_RESET << std::endl
      : std::cout << root->data << std::endl;
  in_order_walk(root->left);
  in_order_walk(root->right);
}

template <typename T> void post_order_walk(Node<T> *&root) {
  if (root == NIL<T>()) {
    return;
  }
  in_order_walk(root->left);
  in_order_walk(root->right);
  root->color == RED
      ? std::cout << COLOR_RED << root->data << COLOR_RESET << std::endl
      : std::cout << root->data << std::endl;
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
