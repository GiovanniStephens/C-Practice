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
        for (int j = 0; j < coeffients.size(); j++) {
            y += coeffients[j] * x[j];
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
    int n = 10;
    x_bounds.push_back({0, 10});
    x_bounds.push_back({0, 10});
    // x_bounds.push_back({0, 10});
    coeffients.push_back(1);
    coeffients.push_back(1);
    coeffients.push_back(1);
    // coeffients.push_back(1);
    std::vector<std::vector<float>> data = generate_data(n, x_bounds, coeffients, noise_std);

    //print data
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
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
    
    // Print the first few rows of x
    std::cout << "x: " << std::endl;
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[i].size(); j++) {
            std::cout << x[i][j] << " ";
        }
        std::cout << std::endl;
    }

    //print the length of x and y
    std::cout << "x length: " << x.size() << std::endl;
    std::cout << "y length: " << y.size() << std::endl;
    

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