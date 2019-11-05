/*
Порядковые статистики. Дано число N и N строк. Каждая строка содержит
команду добавления или удаления натуральных чисел, а также запрос на
получение k-ой порядковой статистики. Команда добавления числа A
задается положительным числом A, команда удаления числа A задается
отрицательным числом “-A”. Запрос на получение k-ой порядковой
статистики задается числом k.
*/


#include <iostream>

class AVL
{
	public:

	AVL(): data(0), height(1), number(1), left(nullptr), right(nullptr) {};
	AVL(int data): data(data), height(1), number(1), left(nullptr), right(nullptr) {};

	int data;
	int height;
	int number;

	AVL* left;
	AVL* right;

};

int get_height(AVL* tree)
{
	return tree? tree->height : 0;
};


int get_balance_factor(AVL* tree)
{
	return get_height(tree->right) - get_height(tree->left);
};

void renum(AVL* tree)
{
	int h_left = get_height(tree->left);
	int h_right = get_height(tree->right);

	h_left > h_right ? tree->height = h_left + 1 : tree->height = h_right + 1;

	int n_left = tree->left ? tree->left->number: 0;
	int n_right = tree->right ? tree->right->number: 0;
	tree->number = n_left + n_right + 1;

};

AVL* small_right(AVL* tree)
{
	AVL* tmp = tree->left;
	tree->left = tmp->right;
	tmp->right = tree;

	renum(tree);
	renum(tmp);

	return tmp;
};

AVL* small_left(AVL* tree)
{
	AVL* tmp = tree->right;
	tree->right = tmp->left;
	tmp->left = tree;

	renum(tree);
	renum(tmp);

	return tmp;
};


AVL* check_balance(AVL* tree)
{
	renum(tree);

	int factor = get_balance_factor(tree);

	if (factor == 2)
	{
		if(get_balance_factor(tree->right) < 0)
		{
			tree->right = small_right(tree->right);
		}
		return small_left(tree);
	}

	if (factor == -2)
	{
		if(get_balance_factor(tree->left) > 0)
		{
			tree->left = small_left(tree->left);
		}
		return small_right(tree);
	}
	return tree;
};

AVL* insert(AVL* tree, int data)
{
	if(!tree)
		return new AVL(data);

	if( data < tree->data)
		tree->left = insert(tree->left, data);
	else
		tree->right = insert(tree->right, data);

    tree = check_balance(tree);

	return tree;
};

AVL* find_min(AVL* tree)
{
	return tree->right ? find_min(tree->right) : tree;
};

AVL* remove_min(AVL* tree)
{
	if(!tree->right)
		return tree->left;

	tree->right = remove_min(tree->right);

	return check_balance(tree);
};

AVL* remove(AVL* tree, int data)
{
	if (!tree)
		return tree;

	if( tree->data > data)
	{
		tree->left = remove(tree->left, data);
	}

	if( tree->data < data)
	{
		tree->right = remove(tree->right, data);
	}

	if(tree->data == data)
	{
		AVL* l = tree->left;
		AVL* r = tree->right;
		delete tree;

		if (!l)
			return r;

		AVL* tmp = find_min(l);
		tmp->left = remove_min(l);
		tmp->right = r;

		return check_balance(tmp);
	}

	return check_balance(tree);
};


int kstat(AVL* tree, int k)
{
	AVL* current = tree;
	int t = 0;

	while(current)
	{
		t = current->left ? current->left->number : 0;

		if (t == k)
		{
			return current->data;
		}

		if( t > k )
		{
			current = current->left;
		}
		else
		{
			current = current->right;
			k = k - 1 - t;
		}
	}
	return - 1;

};


int main() {

    AVL *tree = nullptr;

    int N;
    std::cin >> N;

	int value = 0;
	int k = 0;

    for (int i = 0; i < N; i++)
	{
		std::cin >> value >> k;
		if (value < 0)
		{
			tree = remove(tree, std::abs(value));
		}
		else
		{
			tree = insert(tree, value);
		}
		std::cout << kstat(tree, k) << " ";
    }

    return 0;
}
