#include <iostream>
#include <stack>

template <class Value>
class AVL {
  class Node {
  public:
    Node(Value data) : data(data), left(0), right(0),
                       height(1), lnumber(0), rnumber(0){};
    ~Node() =default;
    Value data;
    Node *left, *right;
    int height;
    int lnumber;
    int rnumber;
  };

public:
  AVL() : root(nullptr){};
  ~AVL(){
    free_node(root);
  };
  void insertAVL(int data, int& index) {
    root = insert(root, data, index);
  }
  void removeAVL(int index) {
    root = remove(root, index);
  }

private:
  Node* root;

  void free_node(Node* node) {
    if (node == nullptr) {
      return;
    }
    free_node(node->left);
    free_node(node->right);
    free(node);
  }

  int get_height(Node* node) { return node ? node->height : 0; };

  int get_balance_factor(Node* node) {
    return get_height(node->right) - get_height(node->left);
  };

  void renum(Node* node) {
    node->lnumber = node->left == nullptr ? 0 : node->left->lnumber + node->left->rnumber + 1;
    node->rnumber = node->right == nullptr ? 0 : node->right->lnumber + node->right->rnumber + 1;
  };

  void rehight(Node* node) {
    node->height = get_height(node->left) > get_height(node->right) ?
    get_height(node->left) : get_height(node->right);
    node->height = node->height+1;
  }

  Node* small_right(Node* node) {
    Node* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    renum(node);
    rehight(node);
    renum(tmp);
    rehight(tmp);

    return tmp;
  };

  Node* small_left(Node* node) {
    Node* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    renum(node);
    rehight(node);
    renum(tmp);
    rehight(tmp);

    return tmp;
  };

  Node* check_balance(Node* node) {
    renum(node);
    rehight(node);

    int factor = get_balance_factor(node);

    if (factor == 2) {
      if (get_balance_factor(node->right) < 0) {
        node->right = small_right(node->right);
      }
      return small_left(node);
    }

    if (factor == -2) {
      if (get_balance_factor(node->left) > 0) {
        node->left = small_left(node->left);
      }
      return small_right(node);
    }
    return node;
  };

  Node* insert(Node* node, int data, int& index) {
    if (node == nullptr) {
      return new Node(data);
    }

    if (data <= node->data) {
      index += node->rnumber +1;
      node->left = insert(node->left, data, index);
    } else {
      node->right = insert(node->right, data, index);
    }

    node = check_balance(node);
    return node;
  };

  Node* find_min(Node* node) {
    return node->left ? find_min(node->left) : node;
  };

  Node* remove_min(Node* node) {
    if (!node->left) return node->right;

    node->left = remove_min(node->left);

    return check_balance(node);
  };

  Node* remove(Node* node, int position) {
    if (node == nullptr) {
      return nullptr;
    }

    if (position > node->rnumber) {
      node->left = remove(node->left, position - node->rnumber - 1);
    } else if (position < node->rnumber) {
      node->right = remove(node->right, position);
    } else {
      //иначе удаляем
      Node* tmpleft = node->left;
      Node* tmpright = node->right;
      delete node;
      if (tmpright == nullptr) {
        return  tmpleft;
      }

      Node* tmpmin = find_min(tmpright);
      tmpmin->right = remove_min(tmpright);
      tmpmin->left = tmpleft;

      tmpmin = check_balance(tmpmin);

      return tmpmin;
    }
    node = check_balance(node);

    return node;
  }
};

int main() {
  AVL<int> tree;

  int N;
  std::cin >> N;

  int value = 0;
  int op = 0;

  for (int i = 0; i < N; i++) {
    std::cin >> op >> value;

    int pos = 0;
    switch (op) {
    case 1:
      pos = 0;
      tree.insertAVL(value, pos);
      std::cout << pos << std::endl;
      break;
    case 2:
      tree.removeAVL(value);
      break;
    }
  }

  return 0;
}
