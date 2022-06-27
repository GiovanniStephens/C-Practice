/* This is a heap implementation in C++.
 * It is a bit of practice for me.
 *
 * Author:  Giovanni Stephens
 * Date:    26/06/2022
 */

#include <iostream>
#include <vector>

class Heap {
  private:
    std::vector<int> v;
    bool min_heap; // Default to min-heap.

    bool compare(int a, int b) {
        if (min_heap) {
            return a < b;
        } else {
            return a > b;
        }
    }

    void heapify(int index) {
        int min_index = index;
        int left = 2 * index;
        int right = left + 1;
        int last = v.size() - 1;

        // both the children should have the value between
        // 1 <= child <= last
        if (left <= last && compare(v[left], v[index])) {
            min_index = left;
        }
        if (right <= last && compare(v[right], v[index])) {
            min_index = right;
        }
        if (min_index != index) {
            std::swap(v[index], v[min_index]);
            heapify(min_index);
        }
    }

  public:
    Heap(int default_size = 10, bool type = true) {
        v.reserve(default_size);
        v.push_back(-1);
        min_heap = type;
    }
    ~Heap() {
        v.clear();
    }

    void insert(int value) {
        v.push_back(value);
        int index = v.size() - 1;
        int parent = index / 2;

        while (index > 1 && compare(v[index], v[parent])) {
            std::swap(v[index], v[parent]);
            index = parent;
            parent = index / 2;
        }
    }

    int remove() {
        int last = v.size() - 1;
        std::swap(v[1], v[last]);
        v.pop_back();
        heapify(1);

        return v[1];
    }

    int peek() {
        return v[1];
    }

    int get_size() {
        return v.size() - 1;
    }

    int get_capacity() {
        return v.capacity();
    }

    void print(){
        for (int i = 1; i < v.size(); i++) {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Heap h;
    h.insert(1);
    h.insert(2);
    h.insert(3);
    h.insert(4);

    h.print();
    h.remove();

    h.print();

    return 0;
}