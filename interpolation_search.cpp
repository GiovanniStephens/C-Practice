/* Interpolation search. 
 * It basically picks a point in a sorted 
 * vay and checks if the value is in the
 * range of the point.
 * 
 * It is much like a binary search, but it
 * picks the point using a proportional 
 * split in the data. This is quite a good search
 * if you know that the data are uniform and
 * evenly distributed (as well as sorted, of course).
 * 
 * Author: Giovanni Stephens
 * Date:   16/07/2022
 */

#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int target = 5;
    int low = 0;
    int high = v.size() - 1;
    int mid;

    while ((v[high] != v[low]) && (target >= v[low]) && (target <= v[high])) {
        mid = low + ((target - v[low]) * (high - low) / (v[high] - v[low]));

        if (v[mid] < target)
            low = mid + 1;
        else if (target < v[mid])
            high = mid - 1;
        else
            std::cout << "Found " << target << " at index " << mid << std::endl;
            return 0;
    }

    if (target == v[low])
        std::cout << "Found " << target << " at index " << low << std::endl;
    else
        std::cout << "Not found" << std::endl;

    return 0;
}