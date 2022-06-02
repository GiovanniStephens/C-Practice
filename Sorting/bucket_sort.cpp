/* Bucket sort.
 *
 * Author:  Giovanni Stephens
 * Date:    31/05/2022
 */

#include<iostream>
#include<vector>
#include<algorithm>

void bucket_sort(int arr[], int n) {
    // 1) Create n empty buckets
    std::vector<int> b[n];
 
    // 2) Put array elements
    // in different buckets
    for (int i = 0; i < n; i++) {
        int bi = arr[i]; // Index in bucket
        b[bi].push_back(arr[i]);
    }
 
    // 3) Sort individual buckets
    for (int i = 0; i < n; i++)
        sort(b[i].begin(), b[i].end());
 
    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
            arr[index++] = b[i][j];
}


int main() {
    int arr[] = { 2, 5, 3, 0, 2, 3, 0, 3 };
    int n = sizeof(arr) / sizeof(arr[0]);
    bucket_sort(arr, n);

    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";

    return 0;
}