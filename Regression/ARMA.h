#ifndef ARMA_H_
#define ARMA_H_

#include "Regressor.h"
#include "utilities.h"

class ARMA {
    private:
        int p;
        int q;
        std::vector<std::vector<float>> data;
    public:    
        std::vector<float> residuals;
        std::vector<float> coeffients;

        ARMA(std::vector<std::vector<float>> data, int p, int q);
        ~ARMA();
        void fit();
        void predict(int n);
};

#endif