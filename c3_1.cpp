#include <iostream>

class CQueue {
	
	//левый и правый списки
    struct LeftNode { //хранит введенные данные
        int data;
        Node* next;
        explicit Node(int data) : data(data), next(0) {}
    };
	
	struct RightNode { //служит для обработки данных
        int data;
        Node* next;
        explicit Node(int data) : data(data), next(0) {}
    };

	
public:
    Queue();
    Queue(const Queue&) = delete;
    Queue(Queue&&) = delete;
    Queue& operator = (const Queue&) = delete;
    Queue& operator = (Queue&&) = delete;
    ~Queue();
    
    void enqueue(int data)
	{
		/*
		 1) While stack1 is not empty, push everything from stack1 to stack2.
  2) Push x to stack1 (assuming size of stacks is unlimited).
  3) Push everything back to stack1.
  */
	};
		
	int deque()
	{
		/*
		 1) If stack1 is empty then error
		2) Pop an item from stack1 and return it
		*/
	}
	
    bool isEmpty()
	{
		
	};
	
private:
    Node* left_head;
    Node* right_head;
	Node* left_tail;
    Node* right_tail;
};

