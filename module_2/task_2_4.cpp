/*
2_4. Обход дерева в порядке level-order
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

	if(!this)
		return;

	std::deque<Tree*> in;
	std::deque<int> out;

	in.push_back(this);

	while(!in.empty())
	{
		Tree* current = in[0];
		in.pop_front();

		out.push_back(current->data);


		if(current->right_tree)
			in.push_back(current->right_tree);

		if(current->left_tree)
			in.push_back(current->left_tree);

	}

	for(int i = 0; i < out.size(); i++)
	{
		std::cout << out[i] << " ";
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
