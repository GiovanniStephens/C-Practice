#ifndef ARMA_H_
#define ARMA_H_

#include "Regressor.h"
#include "utilities.h"

class ARMA {
    private:
        int p;
        int q;
        std::vector<float> data;

        std::vector<std::vector<float>> lag_series(std::vector<float> series, int nlags);
    public:
        std::vector<float> residuals;
        std::vector<float> coefficients;

        ARMA(std::vector<float> data, int p, int q);
        LinearRegressor AR(int nlags);
        ~ARMA();
        
        void fit();
        void predict(int n);
};

#endif