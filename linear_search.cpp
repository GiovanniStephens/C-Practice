/* Basic linear search implementation
 * to practice more C++.
 *
 * Linear search simply loops over the array
 * and checks if the key is in the array.
 * 
 * Author:  Giovanni Stephens
 * Date:    16/07/2022
 */

#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int>::iterator it;
    int target = 5;

    for (it = v.begin(); it != v.end(); it++) {
        if (*it == target) {
            std::cout << "Found " << target << " at index " << std::distance(v.begin(), it) << std::endl;
            break;
        }
    }

    if (it == v.end()) {
        std::cout << "Target not found" << std::endl;
    }

    return 0;
}