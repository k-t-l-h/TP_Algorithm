/*
3_1. Вычислить разницу глубин наивного дерева поиска
 и декартового дерева. Разница может быть отрицательна.
*/

#include <iostream>
#include <vector>
#include <queue>


class NaiveTree {

  class T_node {
  public:
    T_node(int data) : data(data), left_tree(nullptr), right_tree(nullptr){};

    int data;
    T_node *left_tree, *right_tree;
  };
public:
  NaiveTree() : root(nullptr){};
  ~NaiveTree() { free_tree(root); };

  void free_tree(T_node* current) {
    if (current) {
      if (current->left_tree) free_tree(current->left_tree);
      if (current->right_tree) free_tree(current->right_tree);
      delete current;
    }
  }

  void add(int data);
  int width();
  int depth();

private:
  T_node* root;
};

void NaiveTree::add(int data) {
  if (!root) {
    root = new T_node(data);
    return;
  }

  T_node* current = root;

  while (current) {
    if (current->data <= data) {
      if (current->left_tree) {
        current = current->left_tree;
      } else {
        current->left_tree = new T_node(data);
        return;
      }
    } else {
      if (current->right_tree) {
        current = current->right_tree;
      } else {
        current->right_tree = new T_node(data);
        return;
      }
    }
  }
  return;
};

int NaiveTree::depth() {
  struct QueNode{
    NaiveTree::T_node* node;
    int depth;
  };

  int depth = 0;

  if (root == nullptr) {
    return depth;
  }

  QueNode qn ={root, 0};
  std::queue<QueNode> queue;
  queue.push(qn);

  while (!queue.empty()) {
    auto element = queue.front();
    queue.pop();

    if (element.depth > depth) {
      depth = element.depth;
    }

    if (element.node->left_tree) {
      QueNode qnl ={element.node->left_tree, element.depth+1};
      queue.push(qnl);
    }

    if (element.node->right_tree) {
      QueNode qnr ={element.node->right_tree, element.depth+1};
      queue.push(qnr);
    }
  }

  return depth;
};

class Tree {
  class T_node {
  public:
    T_node(int data, int priority)
        : data(data),
          priority(priority),
          left_tree(nullptr),
          right_tree(nullptr){};
    int data;
    int priority;
    T_node *left_tree, *right_tree;
  };

public:
  Tree() : root(nullptr){};
  Tree(T_node* tree) : root(tree){};
  ~Tree() { free_tree(root); }

  void free_tree(T_node* current) {
    if (current) {
      if (current->left_tree) free_tree(current->left_tree);
      if (current->right_tree) free_tree(current->right_tree);

      delete current;
    }
  }

  void add(int data, int priority);
  void split(T_node* root, int data, T_node*& left, T_node*& right);
  int width();
  int depth();

private:
  T_node* root;
};

void Tree::split(T_node* root, int data, T_node*& left, T_node*& right) {
  if (!root) {
    left = nullptr;
    right = nullptr;
    return;
  }

  if (root->data <= data) {
    split(root->right_tree, data, root->right_tree, right);
    left = root;
  } else {
    split(root->left_tree, data, left, root->left_tree);
    right = root;
  }
};

void Tree::add(int data, int priority) {
  if (!root) {
    root = new T_node(data, priority);
    return;
  }

  T_node* current = root;
  T_node* parent = nullptr;

  int flag = 1;

  while (current != nullptr && current->priority >= priority) {
    parent = current;
    if (current->data > data) {
      flag = 1;
      current = current->left_tree;
    } else {
      flag = 0;
      current = current->right_tree;
    }
  }

  T_node* T1 = nullptr;
  T_node* T2 = nullptr;

  split(current, data, T1, T2);

  current = new T_node(data, priority);
  current->left_tree = T1;
  current->right_tree = T2;

  if (!parent) {
    root = current;
    return;
  }

  if (flag) {
    parent->left_tree = current;
  } else {
    parent->right_tree = current;
  }
};

int Tree::depth() {
  struct QueNode{
    Tree::T_node* node;
    int depth;
  };

  int depth = 0;

  if (root == nullptr) {
    return depth;
  }

  QueNode qn ={root, 0};
  std::queue<QueNode> queue;
  queue.push(qn);

  while (!queue.empty()) {
    auto element = queue.front();
    queue.pop();

    if (element.depth > depth) {
      depth = element.depth;
    }

    if (element.node->left_tree) {
      QueNode qnl ={element.node->left_tree, element.depth+1};
      queue.push(qnl);
    }

    if (element.node->right_tree) {
      QueNode qnr ={element.node->right_tree, element.depth+1};
      queue.push(qnr);
    }
  }

  return depth;
};

int main() {
  int size = 0;
  std::cin >> size;

  if (size == 0) {
    std::cout << "0";
    return 0;
  }

  int value = 0;
  int priority = 0;

  Tree* tree = new Tree();
  NaiveTree* ntree = new NaiveTree();

  for (int i = 0; i < size && std::cin >> value >> priority; i++) {
    tree->add(value, priority);
    ntree->add(value);
  }

  std::cout << abs(tree->depth() - ntree->depth());
  return 0;
}
