/* Binary search implementation
 * to practice more C++.
 *
 * Author:  Giovanni Stephens
 * Date:    16/07/2022
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int>::iterator it;
    int target = 5;

    int low = 0;
    int high = v.size() - 1;
    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (v[mid] == target) {
            std::cout << "Found " << target << " at index " << mid << std::endl;
            break;
        } else if (v[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (low > high) {
        std::cout << "Target not found" << std::endl;
    }

    return 0;
}