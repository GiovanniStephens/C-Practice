/* Basic example of bubble sort.
 * 
 * Author:  Giovanni Stephens
 * Date:    28/05/2022
 */
#include <iostream>

void print_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int array[5] = {5, 4, 3, 2, 1};
    int i, j, temp, swapped;

    print_array(array, 5);

    for (i = 0; i < 5; ++i) {
        swapped = 0;
        for (j = 0; j < 5 - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
    }

    print_array(array, 5);

    return 0;
}