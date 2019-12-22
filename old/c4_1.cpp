#include <iostream>


#define MAX_FRUIT 50000

class BinaryHeap{

public:
	BinaryHeap();
	~BinaryHeap();
	
	int Peek();
	void InsertHeap(int data); //добавляем в кучу
	void PrintHeap();

	int* array;//array
	size_t arr_size; //текущий размер массива
	
	void BuildHeap(); //строим кучу 
	int ExtractMax();
	
	void ShiftUp(int index); //значение уменьшилось
		
private:
		
	void ShiftDown(int index); //значение увеличилось
	
};

int BinaryHeap::ExtractMax(){
	
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
	
}

int BinaryHeap::Peek(){
	if (arr_size == 0)
	{
		return -1;
	}
	return array[0];
}

void BinaryHeap::PrintHeap() {
	
	for( int i = 0; i < arr_size; ++i ) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
};

void BinaryHeap::InsertHeap(int data){
	
	arr_size++;
	
	array[arr_size - 1] = data;
	ShiftUp(arr_size - 1);
	
};

void BinaryHeap::BuildHeap(){
	
	for (int i = arr_size / 2 - 1; i >= 0; --i)
	{
		ShiftDown(i);
	}
	
};

void BinaryHeap::ShiftDown(int index){
	int left = 2*index + 1;
	int right = 2*index + 2;
	
	int largest = index;
	
	if (left < arr_size && array[left] > array[largest])
	{
		largest = left;
	}
	
	if (right < arr_size && array[right] > array[largest])
	{
		largest = right;
	}
	
	if (largest != index)
	{
		std::swap(array[index], array[largest]);
		ShiftDown(largest);
	}
	
};

void BinaryHeap::ShiftUp(int index){
	
	while(index > 0)
	{
		int parent = (index - 1) / 2; 
		
		if (array[index] <= array[parent] )
			return;
		
		std::swap( array[index], array[parent] );
		index = parent;
	}
	
};

BinaryHeap::BinaryHeap(){
	
	array = new int[MAX_FRUIT];
	arr_size = 0;	
};

BinaryHeap::~BinaryHeap(){
	delete[] array;
};



int main(int argc, const char * argv[]) {
	
	BinaryHeap heap;
	
	int n = 0;
	int value = 0;
	
	std::cin >> n;
	
	for (int i = 0; i < n; ++i){
		
		std::cin >> heap.array[i];
		
	}
	
	heap.arr_size = n;
	heap.BuildHeap();
	
	int K = 0;
	std::cin >> K;
	
	int count = 0;
	
	int* eaten = new int[MAX_FRUIT];
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
