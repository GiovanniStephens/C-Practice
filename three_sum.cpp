/** This is a solution to the three sum problem using two
 * pointers. The time complexity is O(n^2) and the space
 * complexity is O(n).
 *
 * Problem on leetcode is here: https://leetcode.com/problems/3sum/
 * 
 * Author:  Giovanni Stephens
 * Date:    17/04/2022
 */
#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<std::vector<int>> v;
        int n = nums.size();
        std::sort(nums.begin(),nums.end());
        // Not enough numbers to get a triad.
        if (n < 3) {
            return {};
        }
        for (int i = 0; i < n; i++){
            if(nums[i] > 0) {
                break;
            }
            if (i > 0 && nums[i] == nums[i-1]) {
                continue;
            }
            int front = i+1;
            int back = n-1;
            int sum;
            while (front < back) {
                sum = nums[i] + nums[front] + nums[back];
                if (sum < 0) {
                    front++;
                } else if (sum > 0) {
                    back--;
                } else {
                    v.push_back({nums[i],nums[front],nums[back]});
                    int lastFront = nums[front];
                    int lastBack = nums[back];
                    while(front < back && nums[front] == lastFront) {
                        front++;
                    }
                    while(front < back && nums[back] == lastBack) {
                        back--;
                    }
                }    
            }
        }
        return v;
    }
};

int main() {
    Solution s;
    std::vector<int> nums = {-1, 0, 1, 2, -1, -4};
    std::vector<std::vector<int>> v = s.threeSum(nums);
    for (auto i : v) {
        for (auto j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}