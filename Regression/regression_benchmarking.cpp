// #include "Regressor.h"
// #include "utilities.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Regressor.h"
#include "utilities.h"

float random_normal(float mu, float sigma) {
    float z = (float) rand() / (float) RAND_MAX;
    float x = sqrt(-2.0 * log(z)) * cos(2.0 * M_PI * (float) rand() / (float) RAND_MAX);
    return mu + sigma * x;
}

std::vector<std::vector<float>> generate_data(int n,
                                 std::vector<std::vector<float>> x_bounds,
                                 std::vector<float> coeffients,
                                 float noise_std) {
    std::vector<std::vector<float>> data;
    for (int i = 0; i < n; i++) {
        std::vector<float> x;
        // x.push_back(coeffients[0]);
        for (int j = 0; j < x_bounds.size(); j++) {
            x.push_back(x_bounds[j][0] + (x_bounds[j][1] - x_bounds[j][0]) * rand() / (float) RAND_MAX);
        }
        float y = 0;
        for (int j = 1; j < coeffients.size(); j++) {
            y += coeffients[j] * x[j-1];
        }
        y += coeffients[0];
        y += random_normal(0, noise_std);
        data.push_back(x);
        data.back().push_back(y);
    }
    return data;
}

int main() { 
    std::vector<std::vector<float>> x_bounds;
    std::vector<float> coeffients;
    float noise_std = 0.1;
    int n = 10000;
    x_bounds.push_back({0, 10});
    x_bounds.push_back({0, 10});
    // x_bounds.push_back({0, 10});
    coeffients.push_back(1);
    coeffients.push_back(1.5);
    coeffients.push_back(1);
    // coeffients.push_back(1);
    std::vector<std::vector<float>> data = generate_data(n, x_bounds, coeffients, noise_std);

    // first columns are x, last is y
    std::vector<std::vector<float>> x;
    std::vector<float> y;
    for (int i = 0; i < data.size(); i++) {
        std::vector<float> row;
        for (int j = 0; j < data[i].size() - 1; j++) {
            row.push_back(data[i][j]);
        }
        x.push_back(row);
        y.push_back(data[i].back());
    }

    Timer timer;

    LinearRegressor regressor = LinearRegressor(x, y);
    regressor.fit();

    std::cout << "Time to fit: " << timer.elapsed_time() << "s" << std::endl;

    std::cout << "Coefficients: " << std::endl;
    for (int i = 0; i < regressor.coefficients.size(); i++) {
        std::cout << regressor.coefficients[i] << std::endl;
    }
    return 0; 
}