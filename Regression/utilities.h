#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <chrono>

std::vector<float> calculate_returns(std::vector<float> prices);

// Timer to determine how long things are taking.
class Timer {
    using clock_type = std::chrono::steady_clock;
    using second_clock_type = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<clock_type> start_time{ clock_type::now() };
public:
    void reset();
    double elapsed_time() const;
};

#endif