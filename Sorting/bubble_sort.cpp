/* Basic example of bubble sort.
 * 
 * Author:  Giovanni Stephens
 * Date:    28/05/2022
 */
#include <iostream>
#include "sorting.h"

void bubble_sort(int *arr, int n) {
    int swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = 0;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}
