/* Merge sort imlementation. 
 * This is for practicing c++.
 * 
 * Author:  Giovanni Stephens
 * Date:    30/05/2022
 */

#include <iostream>
#include "sorting.h"

void merge(int *arr, int left, int mid, int right) {
    int *temp = new int[right - left + 1];
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    for (int i = 0; i < k; i++) {
        arr[left + i] = temp[i];
    }
    delete[] temp;
}

void merge_sort(int *arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
