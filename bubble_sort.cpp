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
    int i, j, temp;

    print_array(array, 5);

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 4; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    print_array(array, 5);

    return 0;
}