/* This is a basic selection sort implementation.
 * This was completed as a practice programe to improve
 * my C++ skills.
 * 
 * Author:  Giovanni Stephens
 * Date:    30/05/2022
 */

#include<iostream>

void selection_sort(int *arr, int size) {
    int min_index;
    int temp;
    for(int i = 0; i < size; i++) {
        min_index = i;
        for(int j = i + 1; j < size; j++) {
            if(arr[j] < arr[min_index]){
                min_index = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}

int main() {
    int arr[] = {5, 4, 3, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    selection_sort(arr, size);
    for(int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}