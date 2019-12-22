#include <iostream>

template<class Value>
class AVL
{
	class Node {
	public:
		Node(Value data) : data(data), left(0), right(0), height(1), number(1) {}
		Value data;
		Node *left, *right;
		int height;
		int number;
	};
public:

	AVL() {
		root = NULL;
	};

	int kstat(int k)
	{
		Node* current = root;
		int t = 0;

		while (current)
		{
			t = current->left ? current->left->number : 0;

			if (t == k)
			{
				return current->data;
			}

			if (t > k)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
				k = k - 1 - t;
			}
		}
		return -1;

	};

	void insertAVL(int data) {
		root = insert(root, data);
	}

	void removeAVL(int data) {
		root = remove(root, data);
	}

private:
	int get_height(Node* node)
	{
		return node ? node->height : 0;
	};

	int get_balance_factor(Node* node)
	{
		return get_height(node->right) - get_height(node->left);
	};

	void renum(Node* node)
	{
		int h_left = get_height(node->left);
		int h_right = get_height(node->right);

		h_left > h_right ? node->height = h_left + 1 : node->height = h_right + 1;

		int n_left = node->left ? node->left->number : 0;
		int n_right = node->right ? node->right->number : 0;
		node->number = n_left + n_right + 1;

	};

	Node* small_right(Node* node)
	{
		Node* tmp = node->left;
		node->left = tmp->right;
		tmp->right = node;

		renum(node);
		renum(tmp);

		return tmp;
	};

	Node* small_left(Node* node)
	{
		Node* tmp = node->right;
		node->right = tmp->left;
		tmp->left = node;

		renum(node);
		renum(tmp);

		return tmp;
	};


	Node* check_balance(Node* node)
	{
		renum(node);

		int factor = get_balance_factor(node);

		if (factor == 2)
		{
			if (get_balance_factor(node->right) < 0)
			{
				node->right = small_right(node->right);
			}
			return small_left(node);
		}

		if (factor == -2)
		{
			if (get_balance_factor(node->left) > 0)
			{
				node->left = small_left(node->left);
			}
			return small_right(node);
		}
		return node;
	};

	Node* insert(Node* node, int data)
	{
		if (!node)
			return new Node(data);

		if (data < node->data)
			node->left = insert(node->left, data);
		else
			node->right = insert(node->right, data);

		node = check_balance(node);

		return node;
	};

	Node* find_min(Node* node)
	{
		return node->right ? find_min(node->right) : node;
	};

	Node* remove_min(Node* node)
	{
		if (!node->right)
			return node->left;

		node->right = remove_min(node->right);

		return check_balance(node);
	};

	Node* maxNode(Node* node){
		Node* current = node;
		while (current->right) {
			current = current->right;
		}

		return current;
	};



	Node* remove(Node* node, int data)
	{
		if (!node)
			return node;

		if (node->data > data)
		{
			node->left = remove(node->left, data);
		}

		if (node->data < data)
		{
			node->right = remove(node->right, data);
		}

		if (node->data == data)
		{
			if (!(node->left) || !(node->right)){
			Node* check = node->left? node->left : node->right;
			if(check){
				*node = *check;
			}else{
				check = node;
				node = nullptr;
			}
			delete check;}

			else{
				Node* check = maxNode(node->left);
				node->data = check->data;
				node->left = remove(node->left, check->data);
			}
		}

		if (!node) {
			return node;
		}
		return check_balance(node);
	};

	Node* root;
};

int main() {

	AVL<int> tree;

	int N;
	std::cin >> N;

	int value = 0;
	int k = 0;

	for (int i = 0; i < N; i++)
	{
		std::cin >> value >> k;
		if (value < 0)
		{
			tree.removeAVL(std::abs(value));
		}
		else
		{
			tree.insertAVL(value);
		}
		std::cout << tree.kstat(k) << " ";
	}

	return 0;
}
