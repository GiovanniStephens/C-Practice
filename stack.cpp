/** THis ia a basic implementation of a stack in 
 * C++. This program is to practice the use of
 * classes and objects as well as remember stacks.
 * 
 * Author:  Giovanni Stephens
 * Date:    03/04/2022
 */
#include <iostream>

#define MAX_SIZE 100

class Stack {
    int *arr;
    int capacity;
    int top;

public:
    Stack(int size = MAX_SIZE);
    ~Stack();

    void push(int data);
    int pop();
    int peek();
    bool isEmpty();
    bool isFull();
    int size();
};

// Constructor
Stack::Stack(int size) {
    capacity = size;
    top = -1;
    arr = new int[capacity];
}

// Deconstructor 
Stack::~Stack() {
    delete[] arr;
}

// Push integer onto the stack
void Stack::push(int data) {
    if (isFull()) {
        std::cout << "Stack is full" << std::endl;
        return;
    }
    top = (top + 1) % capacity;
    arr[top] = data;
}

// Pop the top value off the stack
int Stack::pop() {
    if (isEmpty()) {
        std::cout << "Stack is empty" << std::endl;
        return -1;
    }
    int data = arr[top];
    top = (top - 1 + capacity) % capacity;
    return data;
}

// Peek at the top value of the stack
int Stack::peek() {
    if (isEmpty()) {
        std::cout << "Stack is empty" << std::endl;
        return -1;
    }
    return arr[top];
}

// Is the stack empty?
bool Stack::isEmpty() {
    return top == -1;
}

// Is the stack full?
bool Stack::isFull() {
    return top == capacity - 1;
}

// Return the size of the stack
int Stack::size() {
    return top + 1;
}

int main() {
    // Create a stack  
    Stack stack(3);

    // Push some values onto the stack
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4); // Stack is full

    // Pop the values off the stack
    std::cout << "Pop: " << stack.pop() << std::endl; // 3

    stack.push(5);
    std::cout << "Pop: " << stack.pop() << std::endl; // 5

    // Print the size of the stack
    std::cout << "Size: " << stack.size() << std::endl; // 2

    // Peek at the top value
    std::cout << "Peek: " << stack.peek() << std::endl; // 2

    // Is the stack empty?
    std::cout << "IsEmpty: " << stack.isEmpty() << std::endl; // false

    // Is the stack full?
    std::cout << "IsFull: " << stack.isFull() << std::endl; // false

    return 0;
}