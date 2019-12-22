#include <iostream>
#include <cstring>

#define START_SIZE 1000000

class stack {

public:
    stack();
    ~stack() {};

	void resize()
	{
		max_size *= 2;
		int* new_buffer = new int[max_size];
		memcpy(new_buffer, buffer, real_size);
		delete[] buffer;
		
		
	};
	
    void push(int data)
	{
		if (real_size == max_size - 1) {
			
			resize();
		}
			
		buffer[real_size] = data;
		real_size++;
	};
	
    int pop() 
	{
		if (real_size == 0) {
			return -1;
		}
		return buffer[--real_size];
	};
	
    bool is_empty() const {
		return real_size == 0;
	};
	

private:
    int *buffer;
    size_t real_size;
    size_t max_size;
	
};

stack::stack()
{
	real_size = 0;
    max_size = START_SIZE;
	
	buffer = new int[max_size];
	
}



class Queue {

public:
	//правило пяти
    Queue();
    Queue(const Queue&) = delete;
    Queue(Queue&&) = delete;
    Queue& operator = (const Queue&) = delete;
    Queue& operator = (Queue&&) = delete;
	~Queue();

	void enqueue(int data);
		
	int dequeue();
	
	
private:
    stack *input;
    stack *output;
};

Queue::Queue() {
    input = new stack();
    output = new stack();
}

Queue::~Queue() {
        delete input;
        delete output;
    }
	
void Queue::enqueue(int data) {
    input->push(data);
}

int Queue::dequeue() {
	
    if (output->is_empty())
	{
        while (!input->is_empty()) 
		{
            output->push(input->pop());
        }
	}
    return output->pop();
}


int main(int argc, const char * argv[]) {

	Queue queue;
	
    int n = 0;
    std::cin >> n;
    
    for (int i = 0; i < n; i++) {
        int operation = 0;
        int value = -1;
		
        std::cin >> operation >> value;
		
        switch (operation) {
            case 2: 
			{
                int queue_value = -1;
				queue_value = queue.dequeue();
				
                if (queue_value != value) 
				{
                    std::cout << "NO" << std::endl;
                    return 0;
                }
                break;
            }
            case 3:
                queue.enqueue(value);
                break;
				
            default:
                std::cout << "NO" << std::endl;
                return 0;
        }
    }
    std::cout << "YES" << std::endl;
    
    return 0;
}


