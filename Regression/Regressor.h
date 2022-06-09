#ifndef REGRESS_H_
#define REGRESS_H_

class Matrix {
public:
    Matrix(int rows, int cols);
    Matrix();
    ~Matrix();
    double& operator()(int i,int j);
    Matrix cofactor(unsigned int p, unsigned int q);
    double determinant();
    Matrix inverse();
    Matrix transpose();
    Matrix multiply(Matrix m);
    void print();
    unsigned int n;
private:
    std::vector<std::vector<double>> matrix;
};

class LinearRegressor {
    private:
        Matrix X;
        Matrix Y;
    public:
        std::vector<double> coefficients;
        LinearRegressor(std::vector<std::vector<double>> x, std::vector<double> y);
        ~LinearRegressor();
        void fit();
        double predict(std::vector<double> x);
};

#endif