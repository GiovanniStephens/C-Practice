/* This is a first hack at estimating an ARMA model.
 * The estimation procedure is to fit a high-order
 * AR model to the data, then fit an ARMA model to the
 * residuals of the AR model.
 * 
 * The AR model is fit using the OLS method.
 * The ARMA model is fit using the OLS too.
 * 
 * Author:  Giovanni Stephens
 * Date:    05/06/2022
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include "ARMA.h"

class Data {
    private:
        bool file_exists(std::string filename){ 
            std::ifstream infile(filename);
            return infile.good();
        }

    public:
        std::vector<std::string> dates;
        std::vector<float> open;
        std::vector<float> high;
        std::vector<float> low;
        std::vector<float> close;
        std::vector<float> volume;
        std::vector<float> adj_close;

        Data() {}

        ~Data() {
            this->dates.clear();
            this->open.clear();
            this->high.clear();
            this->low.clear();
            this->close.clear();
            this->volume.clear();
            this->adj_close.clear();
        }

        void read_csv(std::string filename) {
            if (file_exists(filename)) {
                std::ifstream file(filename);
                std::string line;
                while (std::getline(file, line)) {
                    // skip the first line
                    if (line.find("Date") != std::string::npos) {
                        continue;
                    }
                    std::stringstream line_stream(line);
                    std::string cell;
                    std::vector<std::string> row;
                    while (std::getline(line_stream, cell, ',')) {
                        row.push_back(cell);
                    }
                    this->dates.push_back(row[0]);
                    this->open.push_back(std::stof(row[1]));
                    this->high.push_back(std::stof(row[2]));
                    this->low.push_back(std::stof(row[3]));
                    this->close.push_back(std::stof(row[4]));
                    this->adj_close.push_back(std::stof(row[5]));
                    this->volume.push_back(std::stof(row[6]));
                }
            } else {
                std::cout << "File: " << filename << " not found" << std::endl;
            }
        }
};

ARMA::ARMA(std::vector<float> x, int p, int q) {
    this->data = x;
    this->p = p;
    this->q = q;
}

LinearRegressor ARMA::AR(int nlags) {
    std::vector<float> y_vec;
    std::vector<std::vector<float>> x_vec;
    for (int i = nlags; i < this->data.size(); i++) {
        y_vec.push_back(this->data[i]);
        std::vector<float> temp;
        for (int j = 1; j <= nlags; j++) {
            temp.push_back({this->data[j-i]});
        }
        x_vec.push_back(temp);
    }
    LinearRegressor lr(x_vec, y_vec);
    lr.fit();
    return lr;
}

void ARMA::fit() {
    // fit the AR model

    // Initial lags.
    int nlags = (int) std::min(10 * std::log10(this->data.size()), (double) this->data.size()/2 - 1);

    // Get initial AR model.
    LinearRegressor ar = AR(nlags);

    // Get residuals.
    std::vector<float> residuals = ar.residuals;

    // Fit the ARMA model.
    

    // Gone to create a functiion that returns residuals in the OLS class.
}


int main() {
    Data prices = Data();
    prices.read_csv("BTC-USD.csv");

    // calculate returns
    std::vector<float> returns = calculate_returns(prices.adj_close);

    int pacf_order = 5;

    // Calculate the pacf values
    std::vector<float> pacf_values = pacf(returns, pacf_order);

    // Print first 5 rows of PACF values
    for (int i = 0; i < pacf_order; i++) {
        std::cout << pacf_values[i] << std::endl;
    }
    
    return 0;
}