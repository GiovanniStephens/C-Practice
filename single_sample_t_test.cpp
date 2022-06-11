/* This is a basic implementation of a one-sample Student t-test.
 * 
 * Assupmtion: 
 *  The data is normally distributed,
 *  The data are assumed to be independent,
 *  The data are assumed to be uncorrelated.
 * 
 * Author:  Giovanni Stephens
 * Date:    11/06/2022
 */

#include <iostream>
#include <vector>
#include <cmath>

/* Calculates the mean (or average) of a vector.
 * 
 * @param x: The vector to calculate the mean of.
 * @return: The mean of the vector.
 */
float mean(std::vector<float> x) {
    float sum = 0;
    for (int i = 0; i < x.size(); i++) {
        sum += x[i];
    }
    return sum / x.size();
}

/* Calculates the standard deviation of a vector.
 * 
 * @param x: The vector to calculate the standard deviation of.
 * @return: The standard deviation of the vector.
 */
float std_dev(std::vector<float> x) {
    float sum = 0;
    float mean_x = mean(x);
    for (int i = 0; i < x.size(); i++) {
        sum += std::pow(x[i] - mean_x, 2);
    }
    return std::sqrt(sum / x.size());
}

int main() {
    std::vector<float> x = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "Mean: " << mean(x) << std::endl;
    std::cout << "Std Dev: " << std_dev(x) << std::endl;

    // Calculate the t statistic for the mean being equal to 0.
    float t_statistic = (mean(x) - 0) / (std_dev(x) / std::sqrt(x.size()));
    std::cout << "t statistic: " << t_statistic << std::endl;

    return 0;
}