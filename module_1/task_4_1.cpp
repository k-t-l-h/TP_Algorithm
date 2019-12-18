/*
4_1. Жадина.
Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы.
 Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм.
  За раз он выбирает несколько самых тяжелых фруктов, которые может поднять
   одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину.
    Если фрукт весит нечетное число грамм, он откусывает большую половину.
     Фрукт массы 1гр он съедает полностью.
*/
#include <iostream>

#define START_SIZE 16

struct Less
{
	bool operator ()(const int& l, const int& r)  {return l < r;}
};


template <class Compare>
class BinaryHeap{

public:

	BinaryHeap(Compare cmpf = Compare())
	{
		array = new int[START_SIZE];
		arr_size = 0;
		max_size = START_SIZE;
		cmp = cmpf;
	};

	~BinaryHeap() {
		delete[] array;
	};

	int Peek()	{
		if (arr_size == 0)
		{
			return -1;
		}
		return array[0];
	};

	void InsertHeap(int data){

		if (arr_size == max_size )
		{
			resize();
		}

		arr_size++;

		array[arr_size - 1] = data;
		ShiftUp(arr_size - 1);

	}; //добавляем в кучу

	void PrintHeap(){

		for( int i = 0; i < arr_size; ++i ) {
			std::cout << array[i] << " ";
		}
		std::cout << std::endl;
	};

	size_t arr_size; //текущий размер массива
	size_t max_size; //максимальный размер массива

	int ExtractMax() {

		if (arr_size > 0)
		{
			int tmp = 0;
			tmp = array[0];

			array[0] = array[arr_size-1];

			arr_size--;

			if(arr_size != 0)
			{
				ShiftDown(0);
			}

			return tmp;
		}

		return -1;

	};

	void ShiftUp(int index) {

		while(index > 0)
		{
			int parent = (index - 1) / 2;

			if (array[index] <= array[parent] )
				return;

			std::swap( array[index], array[parent] );
			index = parent;
		}

	}; //значение уменьшилось

private:

	Compare cmp;
	int* array;//array

	void BuildHeap() {

		for (int i = arr_size / 2 - 1; i >= 0; --i)
		{
			ShiftDown(i);
		}

	}; //строим кучу
	void ShiftDown(int index){
		int left = 2*index + 1;
		int right = 2*index + 2;

		int largest = index;

		if (cmp(left, arr_size) && array[left] > array[largest])
		{
			largest = left;
		}

		if (cmp(right, arr_size) && array[right] > array[largest])
		{
			largest = right;
		}

		if (largest != index)
		{
			std::swap(array[index], array[largest]);
			ShiftDown(largest);
		}

	}; //значение увеличилось


	void resize(){
		int* tmp = new int[max_size*2];
		std::copy(array, array + arr_size, tmp);
		delete[] array;
		array = tmp;
    	max_size *= 2;
	}

};

int main(int argc, const char * argv[]) {

	int n = 0;
	int value = 0;

	std::cin >> n;

	BinaryHeap<Less> heap;

	for (int i = 0; i < n; ++i){

		std::cin >> value;
		heap.InsertHeap(value);
	}
	//


	int K = 0;
	std::cin >> K;

	int count = 0;

	int* eaten = new int[K];
	size_t eaten_s = 0;
	int eaten_summ = 0;

	//пока есть хоть что-то
	while(heap.Peek() != -1 && heap.Peek() != 1)
	{
		count++;

		eaten_s = 0;
		eaten_summ = 0;

		//есть фрукты и фрукт можно поднять
		while(heap.arr_size != 0 && (heap.Peek() + eaten_summ <= K) )
		{
			eaten_s++;
			eaten_summ += heap.Peek();

			eaten[eaten_s-1] = heap.ExtractMax();

		}

		while(eaten_s)
		{
			int t = eaten[eaten_s-1];

			if (t > 1)
			{
				heap.InsertHeap((int)(t / 2));
			}
			eaten_s--;
		}
	}

	count += (heap.arr_size / K);
	if (heap.arr_size % K)
		count++;

	std::cout << count;

	delete[] eaten;

	return 0;

}
