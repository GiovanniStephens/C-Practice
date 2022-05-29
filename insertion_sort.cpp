/* Insertion sort programmed in C++
 * as practice.
 *
 * Author:  Giovanni Stephens
 * Date:    29/05/2022
 */
#include <iostream>

void insertion_sort(int *array, int size) {
    int i, j, temp;
    for (i = 1; i < size; i++) {
        temp = array[i];
        for (j = i - 1; j >= 0 && array[j] > temp; j--) {
            array[j + 1] = array[j];
        }
        array[j + 1] = temp;
    }
}

int main() {
    int array[10] = {5, 2, 4, 6, 1, 3, 9, 7, 8, 0};
    int size = 10;
    insertion_sort(array, size);
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}