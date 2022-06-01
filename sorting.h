#ifndef SORTING_H
#define SORTING_H

#include<vector>

void bubble_sort(int *arr, int n);
void insertion_sort(int *arr, int n);
void selection_sort(int *arr, int n);
void merge_sort(int *arr, int left, int mid, int right);
void quick_sort(int arr[], int low, int high);
void heap_sort(int *arr, int n, int i);
void counting_sort(std::vector<int> &arr);
void bucket_sort(int arr[], int n);

#endif
