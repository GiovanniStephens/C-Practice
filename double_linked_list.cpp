/** This is a double linked list class.
 * It handles strings.
 *
 * Author:  Giovanni Stephens
 * Date:    09/05/2022
 */
#include <iostream>
#include <string>

class Node {
  public:
    Node *next;
    Node *prev;
    std::string data;

    Node(std::string data) {
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }
};

class DoubleLinkedList {
  public:
    Node *head;
    Node *tail;
    int size;

    DoubleLinkedList() {
        this->head = NULL;
        this->tail = NULL;
        this->size = 0;
    }

    void push_front(std::string data) {
        Node *new_node = new Node(data);
        if (this->head == NULL) {
            this->head = new_node;
            this->tail = new_node;
        } else {
            new_node->next = this->head;
            this->head->prev = new_node;
            this->head = new_node;
        }
        this->size++;
    }

    void push_back(std::string data) {
        Node *new_node = new Node(data);
        if (this->head == NULL) {
            this->head = new_node;
            this->tail = new_node;
        } else {
            new_node->prev = this->tail;
            this->tail->next = new_node;
            this->tail = new_node;
        }
        this->size++;
    }

    void pop_front() {
        if (this->head == NULL) {
            return;
        }
        Node *temp = this->head;
        this->head = this->head->next;
        this->head->prev = NULL;
        delete temp;
        this->size--;
    }

    void pop_back() {
        if (this->tail == NULL) {
            return;
        }
        Node *temp = this->tail;
        this->tail = this->tail->prev;
        this->tail->next = NULL;
        delete temp;
        this->size--;
    }

    void print() {
        Node *temp = this->head;
        while (temp != NULL) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void reverse() {
        Node *temp = this->head;
        Node *prev = NULL;
        Node *next = NULL;
        while (temp != NULL) {
            next = temp->next;
            temp->next = prev;
            temp->prev = next;
            prev = temp;
            temp = next;
        }
        this->tail = this->head;
        this->head = prev;
    }
};

int main() {
    DoubleLinkedList list;
    list.push_front("Hello");
    list.push_front("World");
    list.push_back("!");
    list.print();
    list.reverse();
    list.print();
    return 0;
}