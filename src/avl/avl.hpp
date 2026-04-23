#include <algorithm>
#include <iostream>
#include <queue>

namespace avl {

template <typename T> struct Node {
  T data;
  Node<T> *left;
  Node<T> *right;
  Node<T> *parent;
};

template <typename T> Node<T> *createNode(T data) {
  Node<T> *nn = new Node<T>();
  nn->data = data;
  nn->left = nullptr;
  nn->right = nullptr;
  nn->parent = nullptr;
  return nn;
}

template <typename T> static Node<T> *rightRotate(Node<T> *root) {
  Node<T> *t = root->left;
  Node<T> *u = t->right;
  t->right = root;
  root->left = u;
  return t;
}

template <typename T> static Node<T> *leftRotate(Node<T> *root) {
  Node<T> *t = root->right;
  Node<T> *u = t->left;
  t->left = root;
  root->right = u;
  return t;
}

template <typename T> static int height(Node<T> *root) {
  if (root == nullptr) {
    return 0;
  }
  return 1 + std::max(height(root->left), height(root->right));
}

template <typename T> int getBalance(Node<T> *root) {
  return height(root->left) - height(root->right);
}

template <typename T> Node<T> *minValue(Node<T> *root) {
  if (root->left == nullptr) {
    return root;
  }
  return minValue(root->left);
}

template <typename T> Node<T> *insert(Node<T> *&root, T item) {
  if (root == nullptr) {
    return createNode(item);
  }

  Node<T> *z = createNode(item);
  Node<T> *y = nullptr;
  Node<T> *x = root;

  while (x != nullptr) {
    y = x;
    if (z->data < x->data) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  z->parent = y;
  if (z->data < y->data) {
    y->left = z;
  } else {
    y->right = z;
  }

  int b = getBalance(root);
  if (b > 1) {
    if (getBalance(root->left) < 0) {
      root->left = leftRotate(root->left); // Left-Right Case
    }
    return rightRotate(root); // Left-Left Case
  } else if (b < -1) {
    if (getBalance(root->right) > 0) {
      root->right = rightRotate(root->right); // Right-Left Case
    }
    return leftRotate(root); // Right-Right Case
  }
  return root;
}

template <typename T> Node<T> *deleteNode(Node<T> *root, T element) {
  if (root == nullptr) {
    return root;
  }
  if (element < root->data) {
    root->left = deleteNode(root->left, element);
  } else if (element > root->data) {
    root->right = deleteNode(root->right, element);

  } else {
    // Node to be deleted is leaf node or have only one Child
    if (!root->right || !root->left) {
      Node<T> *temp = !root->right ? root->left : root->right;
      delete root;
      return temp;
    }
    // Node to be deleted have both left and right subtrees
    Node<T> *temp = minValue(root->right);
    root->data = temp->data;
    root->right = deleteNode(root->right, temp->data);
  }
  // Balancing Tree after deletion
  return root;
}

template <typename T> void deleteAllNodes(Node<T> *&root) {
  if (root) {
    deleteAllNodes(root->left);
    deleteAllNodes(root->right);
    delete root;
  }
  root = nullptr;
}

template <typename T> void levelOrder(Node<T> *root) {
  std::queue<Node<T> *> q;
  q.push(root);
  while (!q.empty()) {
    root = q.front();
    std::cout << root->data << " ";
    q.pop();
    if (root->left) {
      q.push(root->left);
    }
    if (root->right) {
      q.push(root->right);
    }
  }
}

} // namespace avl
