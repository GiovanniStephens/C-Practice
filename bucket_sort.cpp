/* Bucket sort.
 *
 * Author:  Giovanni Stephens
 * Date:    31/05/2022
 */

#include<iostream>
#include<vector>
#include<algorithm>

void bucket_sort(std::vector<int> &arr) {
    int n = arr.size();
    int max = *std::max_element(arr.begin(), arr.end());
    int min = *std::min_element(arr.begin(), arr.end());
    std::vector<int> bucket(max - min + 1, 0);
    std::vector<int> sorted(n, 0);

    for (int i = 0; i < n; ++i)
        ++bucket[arr[i] - min];

    for (int i = 1; i < bucket.size(); ++i)
        bucket[i] += bucket[i - 1];

    for (int i = n - 1; i >= 0; --i) {
        sorted[--bucket[arr[i] - min]] = arr[i];
    }

    arr = sorted;
}


int main() {
    std::vector<int> arr = { 12, 11, 13, 5, 6, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);

    bucket_sort(arr);

    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";

    return 0;
}