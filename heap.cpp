/* This is a heap implementation in C++.
 * It is a bit of practice for me. 
 *
 * Author:  Giovanni Stephens
 * Date:    26/06/2022
 */

#include <iostream>

class Heap {
    private:
        int *heap;
        int size;
        int capacity;
        int last;
        void swap(int i, int j);
        void bubble_up(int i);
        void bubble_down(int i);
        void resize();
    public:
        Heap();
        Heap(int capacity);
        ~Heap();
        void insert(int value);
        int remove();
        int peek();
        int get_size();
        int get_capacity();
        void print();
};

Heap::Heap() {}   

Heap::Heap(int capacity) {
    this->capacity = capacity;
}

Heap::~Heap() {
}

void Heap::insert(int value) {

}
