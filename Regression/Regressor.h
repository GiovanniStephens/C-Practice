#ifndef REGRESS_H_
#define REGRESS_H_

class Matrix {
public:
    Matrix(int rows, int cols);
    Matrix();
    ~Matrix();
    float& operator()(int i,int j);
    Matrix cofactor(unsigned int p, unsigned int q);
    float determinant();
    Matrix inverse();
    Matrix transpose();
    Matrix multiply(Matrix m);
    void print();
    unsigned int n;
private:
    std::vector<std::vector<float>> matrix;
};

class LinearRegressor {
    private:
        Matrix X;
        Matrix Y;
    public:
        std::vector<float> coefficients;
        LinearRegressor(std::vector<std::vector<float>> x, std::vector<float> y);
        ~LinearRegressor();
        void fit();
        float predict(std::vector<float> x);
};

#endif