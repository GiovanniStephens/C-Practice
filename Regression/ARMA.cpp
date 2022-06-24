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

std::vector<std::vector<float>> ARMA::lag_series(std::vector<float> series, int nlags) {
    std::vector<std::vector<float>> x_vec;
    for (int i = nlags; i < series.size(); i++) {
        std::vector<float> temp;
        for (int j = 1; j <= nlags; j++) {
            temp.push_back({series[i-j]});
        }
        x_vec.push_back(temp);
    }
    return x_vec;
}

LinearRegressor ARMA::AR(int nlags) {
    std::vector<float> y_vec;
    for (int i = nlags; i < this->data.size(); i++) {
        y_vec.push_back(this->data[i]);
    }
    std::vector<std::vector<float>> x_vec = this->lag_series(this->data, nlags);
    LinearRegressor lr(x_vec, y_vec);
    lr.fit();
    return lr;
}

void ARMA::fit() {
    // fit the AR model

    // Initial lags.
    int nlags = (int) std::min(10 * std::log10(this->data.size()), (double) this->data.size()/2 - 1);
    std::cout << "Initial lags: " << nlags << std::endl;
    nlags = 5;
    // Get initial AR model.
    LinearRegressor ar = AR(nlags);

    // Print ar coefficients.
    std::cout << "AR coefficients: " << std::endl;
    for (int i = 0; i < ar.coefficients.size(); i++) {
        std::cout << ar.coefficients[i] << " ";
    }

    // Get residuals.
    std::vector<float> residuals = ar.residuals;

    // Fit the ARMA model.
    std::vector<std::vector<float>> x_vec = this->lag_series(this->data, this->p);
    std::vector<std::vector<float>> resid_vec = this->lag_series(residuals, this->q);
    
    // Join the vectors.
    std::vector<std::vector<float>> x_resid_vec;
    // Get max of p and q.
    int data_length = std::min(x_vec.size(), resid_vec.size());
    for (int i = 0; i < data_length; i++) {
        std::vector<float> temp;
        for (int j = 0; j < this->p; j++) {
            temp.push_back(x_vec[i][j]);
        }
        for (int j = 0; j < this->q; j++) {
            temp.push_back(resid_vec[i][j]);
        }
        x_resid_vec.push_back(temp);
    }
    std::cout << "Length of this->data: " << this->data.size() << std::endl;
    std::cout << "Length of x_vec: " << x_vec.size() << std::endl;
    std::cout << "Length of resid_vec: " << resid_vec.size() << std::endl;
    std::cout << "Length of x_resid_vec: " << x_resid_vec.size() << std::endl;
    
    // y_vec
    std::vector<float> y_vec;
    for (int i = nlags + this->q; i < this->data.size(); i++) {
        y_vec.push_back(this->data[i]);
    }
    std::cout << "Length of y_vec: " << y_vec.size() << std::endl;

    // Fit the ARMA model.
    LinearRegressor arma(x_resid_vec, y_vec);
    arma.fit();

    // Get the coefficients.
    this->coefficients = arma.coefficients;
    this->residuals = arma.residuals;
}

ARMA::~ARMA() {
    this->data.clear();
    this->residuals.clear();
    this->coefficients.clear();
}


int main() {
    Data prices = Data();
    prices.read_csv("BTC-USD.csv");

    // calculate returns
    std::vector<float> returns = calculate_returns(prices.adj_close);

    // print length of returns
    std::cout << "Length of returns: " << returns.size() << std::endl;

    // Calculate the ARMA model
    ARMA arma(returns, 1, 0);

    arma.fit();

    // print the coefficients
    std::cout << "ARMA model coefficients:" << std::endl;
    for (int i = 0; i < arma.coefficients.size(); i++) {
        std::cout << arma.coefficients[i] << std::endl;
    }

    return 0;
}