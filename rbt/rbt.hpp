namespace rbt {

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
} // namespace rbt
