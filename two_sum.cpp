/** Leetcode problem to find two numbers in 
 * an array that sum to a given value.
 *
 * https://leetcode.com/problems/two-sum/
 * 
 * Author:  Giovanni Stephens
 * Date:    14/04/2022
 */
#include <iostream>
#include <vector>
#include <map>

int main() {
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    int n = nums.size();
    std::map<int,int> mp;
    for(int i=0; i<n; i++){
        //if complement is found return indices
        if(mp.find(target-nums[i]) != mp.end()){
            std::cout << mp[target-nums[i]] << ", " << i << std::endl;
        }
        mp[nums[i]] = i;
    }
    return 0;
}