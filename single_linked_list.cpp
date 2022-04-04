/** This is a basic implementation of an
 * integer singly linked list. 
 * It is is for practice using C++.
 * 
 * Author: Giovanni Stephens
 * Date:   04/04/2022
 */
#include <iostream>

class Node {
    int data;
    Node *next;
public:
    Node(int data);
    ~Node();
    int getData();
    Node *getNext();
    void setData(int data);
    void setNext(Node *next);
};

class linked_list {
    Node *head;
    Node *tail;
    int count;
public:
    linked_list();
    ~linked_list();
    void add(int data);
    void remove(int data);
    void print();
    int size();
};

Node::Node(int data) {
    this->data = data;
    this->next = NULL;
}

Node::~Node() {
    delete this->next;
}

int Node::getData() {
    return this->data;
}

Node *Node::getNext() {
    return this->next;
}

void Node::setData(int data) {
    this->data = data;
}

void Node::setNext(Node *next) {
    this->next = next;
}

linked_list::linked_list() {
    this->head = NULL;
    this->tail = NULL;
    this->count = 0;
}

linked_list::~linked_list() {
    delete this->head;
}

void linked_list::add(int data) {
    Node *newNode = new Node(data);
    if (this->head == NULL) {
        this->head = newNode;
        this->tail = newNode;
    } else {
        this->tail->setNext(newNode);
        this->tail = newNode;
    }
    this->count++;
}

void linked_list::remove(int data) {
    Node *current = this->head;
    Node *previous = NULL;
    while (current != NULL) {
        if (current->getData() == data) {
            if (previous == NULL) {
                this->head = current->getNext();
            } else {
                previous->setNext(current->getNext());
            }
            this->count--;
            delete current;
            break;
        }
        previous = current;
        current = current->getNext();
    }
}

void linked_list::print() {
    Node *current = this->head;
    while (current != NULL) {
        std::cout << current->getData() << " ";
        current = current->getNext();
    }
    std::cout << std::endl;
}

int linked_list::size() {
    return this->count;
}

int main() {
    linked_list *list = new linked_list();
    list->add(1);
    list->add(2);
    list->add(3);
    list->add(4);
    list->add(5);
    list->print();
    //list->remove(3); // Screws up the tail. (Need to fix)
    list->print();
    std::cout << "Size: " << list->size() << std::endl;
    delete list;
    return 0;
}