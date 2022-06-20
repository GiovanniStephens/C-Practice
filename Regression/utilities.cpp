/* Contains functions that are useful for 
 * fitting an ARMA model.
 *
 * Author:  Giovanni Stephens
 * Date:    09/06/2022
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm> 
#include "utilities.h"
#include "Regressor.h"

std::vector<float> calculate_returns(std::vector<float> prices) {
    std::vector<float> returns;
    for (int i = 1; i < prices.size(); i++) {
        returns.push_back((prices[i] - prices[i-1]) / prices[i-1]);
    }
    return returns;
}

float mean(std::vector<float> x) {
    float sum = 0;
    for (int i = 0; i < x.size(); i++) {
        sum += x[i];
    }
    return sum / x.size();
}

/* Calculates the autocorrelation of a vector.
 *
 * @param x: The vector to calculate the autocorrelation of.
 * @param nlags: The number of lags to calculate the autocorrelation of.
 *               If nlags is -1, then the autocorrelation is calculated
 *               as min(10 * log_10(nobs), nobs - 1).
 * @return: The autocorrelation of the vector.
 */
std::vector<float> acf(std::vector<float> x, int nlags) {
    std::vector<float> acf;

    if (nlags == -1) {
        nlags = std::min(10 * std::log10(x.size()), (double) x.size() - 1);
    }
    float mean_x = mean(x);
    for (int i = 0; i <= nlags; i++) {
        float numerator = 0;
        float denominator = 0;
        for (int j = 0; j < x.size() - i; j++) {
            numerator += (x[j] - mean_x) * (x[j+i] - mean_x);
            denominator += std::pow(x[j] - mean_x, 2);
        }
        acf.push_back(numerator / denominator);
    }
    return acf;
}

std::vector<float> pacf(std::vector<float> x, int nlags) {
    std::vector<float> pacf;
    if (nlags == -1) {
        nlags = (int) std::min(10 * std::log10(x.size()), (double) x.size()/2 - 1);
    }

    for (int i = 1; i <= nlags; i++) {
        std::vector<float> y_vec;
        for (int j = i; j < x.size(); j++) {
            y_vec.push_back(x[j]);
        }
        std::vector<std::vector<float>> x_vec;
        for (int j = i; j < x.size(); j++) {
            std::vector<float> temp;
            for (int k = 1; k <= i; k++) {
                temp.push_back({x[j-k]});
            }
            x_vec.push_back(temp);
        }
        LinearRegressor lr(x_vec, y_vec);
        lr.fit();

        // print the coefficients
        std::cout << "Coefficients: ";
        for (int j = 0; j < lr.coefficients.size(); j++) {
            std::cout << lr.coefficients[j] << " ";
        }
        std::cout << std::endl;

        // push back last coefficient
        pacf.push_back(lr.coefficients[lr.coefficients.size()-1]);
    }
    
    return pacf;
}

void Timer::reset() {
    start_time = clock_type::now();
}

double Timer::elapsed_time() const {
    return std::chrono::duration_cast<second_clock_type>(clock_type::now() - start_time).count();
}

