/* Contains functions that are useful for 
 * fitting an ARMA model.
 *
 * Author:  Giovanni Stephens
 * Date:    09/06/2022
 */

#include <iostream>
#include <vector>
#include "utilities.h"

std::vector<float> calculate_returns(std::vector<float> prices) {
    std::vector<float> returns;
    for (int i = 1; i < prices.size(); i++) {
        returns.push_back((prices[i] - prices[i-1]) / prices[i-1]);
    }
    return returns;
}

