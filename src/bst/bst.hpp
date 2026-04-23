#include <iostream>
#include <queue>

namespace bst {

template <typename T> struct Node {
  T data;
  int height;
  Node<T> *left;
  Node<T> *right;
  Node<T> *parent;
};

template <typename T> void in_order_walk(Node<T> *root) {

  if (root == nullptr) {
    return;
  }
  in_order_walk(root->left);
  std::cout << root->data << std::endl;
  in_order_walk(root->right);
}

template <typename T> void pre_order_walk(Node<T> *root) {
  if (root == nullptr) {
    return;
  }
  std::cout << root->data << std::endl;
  pre_order_walk(root->left);
  pre_order_walk(root->right);
}

template <typename T> void post_order_walk(Node<T> *root) {
  if (root == nullptr) {
    return;
  }
  pre_order_walk(root->left);
  pre_order_walk(root->right);
  std::cout << root->data << std::endl;
}

template <typename T> Node<T> *min(Node<T> *root) {
  if (root->left == nullptr) {
    return root;
  }
  return min(root->left);
}

template <typename T> Node<T> *max(Node<T> *root) {
  if (root->right == nullptr) {
    return root;
  }
  return max(root->right);
}

// Maior elemento da sub tree a direita
template <typename T> Node<T> *successor(Node<T> *target) {
  if (target->right != nullptr) {
    return min(target->right);
  }
  Node<T> *successor = target->right;
  while (successor != nullptr && target == successor->right) {
    target = successor;
    successor = successor->parent;
  }
  return successor;
}

// Maior elemento da sub tree a esquerda
template <typename T> Node<T> *predecessor(Node<T> *target) {
  if (target->left != nullptr) {
    return max(target->left);
  }
  Node<T> *predecessor = target->parent;
  while (predecessor != nullptr && target == predecessor->right) {
    target = predecessor;
    predecessor = predecessor->parent;
  }
  return predecessor;
}

template <typename T> Node<T> *delNode(Node<T> *root, T data) {
  if (root == nullptr)
    return root;

  if (root->data > data)
    root->left = delNode(root->left, data);
  else if (root->data < data)
    root->right = delNode(root->right, data);
  else {
    // Node with 0 or 1 child
    if (root->left == nullptr) {
      Node<T> *temp = root->right;
      delete root;
      return temp;
    }
    if (root->right == nullptr) {
      Node<T> *temp = root->left;
      delete root;
      return temp;
    }

    // Node with 2 children
    Node<T> *succ = successor(root);
    root->data = succ->data;
    root->right = delNode(root->right, succ->data);
  }
  return root;
}

template <typename T> bool is_leaf(Node<T> *target) {
  if (target->left == nullptr && target->right == nullptr) {
    return true;
  }
  return false;
}

template <typename T> int balance(Node<T> *root) {
  return height(root->left) - height(root->right);
}

template <typename T> Node<T> *clean(Node<T> *root) {
  if (root != nullptr) {
    clean(root->left);
    clean(root->right);
    delete root;
    root = nullptr;
  }
  return root;
}

template <typename T> static int height(Node<T> *root) {
  if (root == nullptr) {
    return -1;
  }
  int left = height(root->left);
  int right = height(root->right);
  return 1 + std::max(left, right);
}

template <typename T> Node<T> *createNode(T data) {
  Node<T> *new_node = new Node<T>();
  new_node->data = data;
  new_node->height = 0;
  new_node->left = nullptr;
  new_node->right = nullptr;
  new_node->parent = nullptr;
  return new_node;
}

template <typename T> Node<T> *insert(Node<T> *&root, T data) {

  if (root == nullptr) {
    return createNode(data);
  }
  Node<T> *z = createNode(data);
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
  return root;
}

template <typename T> Node<T> *search(Node<T> *root, T target) {
  if (root == nullptr) {
    return nullptr;
  }
  if (target == root->data) {
    return root;
  }
  if (target < root->data) {
    return search(root->left, target);
  } else {
    return search(root->right, target);
  }
}

template <typename T> void level_order_walk(Node<T> *root) {

  if (root == nullptr)
    return;
  std::queue<Node<T> *> tree_queue;
  tree_queue.push(root);
  while (!tree_queue.empty()) {
    int level_size = tree_queue.size();

    for (int i = 0; i < level_size; i++) {
      Node<T> *current = tree_queue.front();
      tree_queue.pop();

      std::cout << current->data << " ";

      if (current->left)
        tree_queue.push(current->left);
      if (current->right)
        tree_queue.push(current->right);
    }

    std::cout << std::endl;
  }
}

template <typename T>
void pretty_print(std::string prefix, Node<T> *&root, bool isLeft) {
  if (root == nullptr) {
    return;
  }
  std::cout << prefix;
  std::cout << (isLeft ? "├──" : "└──");

  std::cout << root->data << std::endl;
  pretty_print(prefix + (isLeft ? "│  " : "  "), root->left, true);
  pretty_print(prefix + (isLeft ? "│  " : "  "), root->right, false);
}

template <typename T> void pretty_print(Node<T> *&root) {
  pretty_print("", root, false);
}
} // namespace bst
