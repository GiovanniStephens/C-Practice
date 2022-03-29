/* This is a program that demonstrates the use of arrays.
 * It is basically a practice program to get familiar with arrays.
 *
 * Author: Giovanni Stephens
 * Date:   29/03/2022
 */
#include <iostream>

int main() {
    int num_items = 10;
    // Instantiate an array of size 10.
    int array[num_items];
    // Initialize the array.
    for (int i = 0; i < num_items; i++) {
        array[i] = i;
    }
    // Print the array.
    for (int i = 0; i < num_items; i++) {
        std::cout << array[i] << std::endl;
    }
    return 0;
}