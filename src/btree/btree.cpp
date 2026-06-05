#include <iostream>
#include <vector>

class Btree {
public:
  class Node {
  public:
    bool leaf;
    std::vector<int> k;
    std::vector<Node *> c;

    Node(bool _leaf) : leaf(_leaf) {}
  };

  int t; // Grau minimo
  Node *root;

  void split_child(Node *x, int i) {
    Node *y = x->c[i];
    Node *z = new Node(y->leaf);

    // Pega a chave do meio
    int middle = y->k[t - 1];

    for (int j = t; j < (2 * t - 1); j++) {
      z->k.push_back(y->k[j]);
    }

    if (!y->leaf) {
      for (int j = t; j < (2 * t); j++) {
        z->c.push_back(y->c[j]);
      }
    }

    // Reduz y
    y->k.resize(t - 1);

    if (!y->leaf) {
      y->c.resize(t);
    }

    x->c.insert(x->c.begin() + 1 + i, z);

    x->k.insert(x->k.begin() + i, middle);
  }

  void insert_non_full(Node *x, int k) {
    if (x == nullptr) {
      return;
    }
    size_t i = x->k.size() - 1;
    if (x->leaf) {
      x->k.push_back(0);
      while (i >= 0 && k < x->k[i]) {
        x->k[i + 1] = x->k[i];
        i--;
      }
      x->k[i + 1] = k;
    } else {
      while (i >= 0 && k < x->k[i]) {
        i--;
      }
      i++;

      // Filho cheio de chaves?
      if (x->c[i]->k.size() == 2 * t - 1) {
        split_child(x, i);
        if (k > x->k[i]) {
          i++;
        }
      }
      // Desce para o filho
      insert_non_full(x->c[i], k);
    }
  }

  void tranverse(Node *x) {
    if (x == nullptr) {
      return;
    }
    size_t i;
    for (i = 0; i < x->k.size(); i++) {
      if (!x->leaf) {
        tranverse(x->c[i]);
      }
      std::cout << x->k[i] << " ";
    }
    if (!x->leaf) {
      tranverse(x->c[i]);
    }
  }

  void destructor(Node *x) {
    if (x == nullptr) {
      return;
    }

    if (!x->leaf) {
      for (size_t i = 0; i < x->c.size(); i++) {
        destructor(x->c[i]);
      }
    }
    delete x;
  }

  Btree(int _t) {
    if (_t < 2) {
      throw std::invalid_argument("t must be >= 2");
    }
    t = _t;
    root = nullptr;
  }

  ~Btree() { destructor(root); }

  void insert(int k) {
    if (root == nullptr) {
      root = new Node(true);
      root->k.push_back(k);
      return;
    }

    if (root->k.size() == 2 * t - 1) {
      Node *s = new Node(false);
      s->c.push_back(root);
      split_child(s, 0);
      insert_non_full(s->c[0], k);
      root = s;
    } else {
      insert_non_full(root, k);
    }
  }

  void tranverse() { tranverse(root); }
};

int main() {
  Btree btree(2);
  btree.insert(10);
  btree.insert(12);
  btree.insert(15);
  btree.insert(13);
  btree.insert(30);
  btree.tranverse();
  return 0;
}
