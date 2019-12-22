/*
2_1. Обход дерева в порядке in-order
*/

#include <iostream>
#include <vector>
#include <stack>
#include <string>

class Tree {
public:
    Tree(int data) : data(data), left_tree(nullptr),
        right_tree(nullptr) {}
	 ~Tree() {};

    void add(int data);
    void show();

private:
    Tree *left_tree;
    Tree *right_tree;
    int data;
};

void Tree::add(int data) {

    Tree *tree = this;
    bool flag = false;


    while (!flag)
	{
        if (tree->data <= data)
		{
            if (tree->left_tree == nullptr)
			{
                flag = true;
                tree->left_tree = new Tree(data);
            }
			else
			{
                tree = tree->left_tree;
            }
        }
		else
		{
            if (tree->right_tree == nullptr)
			{
                flag = true;
                tree->right_tree = new Tree(data);
            }
			else
			{
                tree = tree->right_tree;
            }
        }
    }

}

void Tree::show() {

std::stack<Tree*> leftStack;
std::stack<Tree*> rightStack;

Tree* currentTree = this;
while( !leftStack.empty() || currentTree != NULL )
{
    if( currentTree )
    {
        leftStack.push( currentTree );
        currentTree = currentTree->left_tree;
    }
    else
    {
        currentTree = leftStack.top();
        leftStack.pop();

        rightStack.push( currentTree );
        currentTree = currentTree->right_tree;
    }
}

while( !rightStack.empty() )
{
    currentTree = rightStack.top();
    rightStack.pop();

    std::cout << currentTree->data;
    std::cout << " ";
}

}

int main()
{
    int n = 0;
    std::cin >> n;

    int key;
    std::cin >> key;
    Tree tree(key);


    for(int i = 0; i < n-1; i++) {
		std::cin >> key;
        tree.add(key);
    }

    tree.show();


    return 0;
}
