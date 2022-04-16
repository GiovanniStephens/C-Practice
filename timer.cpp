/** This is a basic class to time how long some code took.
 * It uses std::chronos to get the time.
 * 
 * Author:  Giovanni Stephens
 * Date:    16/04/2022
 */
#include <chrono>
#include <iostream>
#include <map>
#include <vector>

class Timer {
    using clock_type = std::chrono::steady_clock;
    using second_clock_type = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<clock_type> start_time{ clock_type::now() };

    public:
        void reset() {
            start_time = clock_type::now();
        }

        double elapsed_time() const {
            return std::chrono::duration_cast<second_clock_type>(clock_type::now() - start_time).count();
        }
};

int main() {
    Timer timer;
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
    std::cout << "Time taken: " << timer.elapsed_time() << " seconds" << std::endl;
    return 0;
}