#include <iostream>
#include <algorithm>
#include <memory>

using namespace std;

template <typename K, typename V>
class btree_node {
  using node_ptr = unique_ptr<btree_node<K, V>>;

  node_ptr l;
  K k1;
  node_ptr m;
  K k2;
  node_ptr r;
};

template <typename K, typename V>
class btree {
  unique_ptr<btree_node<K, V>> root;

  bool insert(K, V);
  bool remove(K, V);
  V* lookup(K) const;
};

int main() {
  cout << "hello" << endl;
}
