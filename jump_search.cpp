/* Ths s a jump search implementation. 
 * This was implemented to practice more C++.
 *
 * Author:  Giovanni Stephens
 * Date:    16/07/2022
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int jump_size = 3;
    int target = 5;
    int size = v.size() - 1; 
    int prev = 0;
    while(v[std::min(prev+jump_size, size)] < target) {
        prev += jump_size;

        if (prev >= v.size()) {
            std::cout << "Target not found" << std::endl;
            return 0;
        }
    }

    while(v[prev] < target) {
        prev++;
        if (prev >= v.size()) {
            std::cout << "Target not found" << std::endl;
            return 0;
        }
    }

    std::cout << "Found " << target << " at index " << prev << std::endl;

    return 0;   
}