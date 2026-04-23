/*
 https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
 */

#include "rbt.hpp"

using namespace rbt;

int main() {
  rbt::Node<int> *root = new rbt::Node<int>{10, BLACK, rbt::NIL<int>(),
                                            rbt::NIL<int>(), rbt::NIL<int>()};

  // Possibilidade 1:  nó com nenhum filho (ou dois filhos-folha vazios)
  /*
    insert(root, 5);
    insert(root, 15);

    remove(root, 5);
   */
  // Remover nó preto com filho vermelho
  /*
    insert(root, 10);
    insert(root, 5);
    insert(root, 15);
    insert(root, 1);

    remove(root, 5);
   */

  // Caso double black e irmão vermelho
  /*
    insert(root, 10);
    insert(root, 5);
    insert(root, 20);
    insert(root, 15);
    insert(root, 25);

    remove(root, 5);
   */

  // Irmão preto com filhos pretos
  /*
    insert(root,  10);
    insert(root,  5);
    insert(root,  20);
    insert(root,  15);
    insert(root,  25);

    remove(root, 15);
   */

  pretty_print(root);
  purge(root);
  return 0;
}
