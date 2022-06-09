/* Contains functions that are useful for 
 * fitting an ARMA model.
 *
 * Author:  Giovanni Stephens
 * Date:    09/06/2022
 */

#include <iostream>
#include <vector>
#include "utilities.h"
#include "Regressor.h"

std::vector<float> calculate_returns(std::vector<float> prices) {
    std::vector<float> returns;
    for (int i = 1; i < prices.size(); i++) {
        returns.push_back((prices[i] - prices[i-1]) / prices[i-1]);
    }
    return returns;
}

void Timer::reset() {
    start_time = clock_type::now();
}

double Timer::elapsed_time() const {
    return std::chrono::duration_cast<second_clock_type>(clock_type::now() - start_time).count();
}




