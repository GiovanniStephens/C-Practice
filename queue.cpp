/* This is a basic implementation of
 * a queue using an array. 
 * It only handles integers.
 * 
 * Author: Giovanni Stephens
 * Date:   02/04/2022
 */

#include <iostream>

#define MAX_SIZE 100

// Class declaration
class Queue {
    int front, rear;
    int *arr;
    int capacity;
    int count;

public:
    Queue(int size = MAX_SIZE);
    ~Queue();

    void enqueue(int data);
    int dequeue();
    int peek();
    bool isEmpty();
    bool isFull();
    int size();
};

// Constructor
Queue::Queue(int size) {
    front = rear = -1;
    capacity = size;
    count = 0;
    arr = new int[capacity];
}

// Destructor
Queue::~Queue() {
    delete[] arr;
}

// Enqueue function
void Queue::enqueue(int data) {
    if (isFull()) {
        std::cout << "Queue is full" << std::endl;
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear = (rear + 1) % capacity;
    arr[rear] = data;
    count++;
}

// Dequeue function
int Queue::dequeue() {
    if (isEmpty()) {
        std::cout << "Queue is empty" << std::endl;
        return -1;
    }
    int data = arr[front];
    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % capacity;
    }
    count--;
    return data;
}

// Peek function (looks at the front element)
int Queue::peek() {
    if (isEmpty()) {
        std::cout << "Queue is empty" << std::endl;
        return -1;
    }
    return arr[front];
}

// IsEmpty function. (Checks if the queue is empty)
bool Queue::isEmpty() {
    return count == 0;
}

// IsFull function. (Checks if the queue is full)
bool Queue::isFull() {
    return count == capacity;
}

// Size function. (Returns the size of the queue)
int Queue::size() {
    return count;
}

int main() {
    Queue q(3);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4); // Queue is full
    std::cout << q.dequeue() << std::endl;
    std::cout << q.dequeue() << std::endl;
    std::cout << q.dequeue() << std::endl;
    std::cout << q.dequeue() << std::endl; // Queue is empty
    return 0;
}