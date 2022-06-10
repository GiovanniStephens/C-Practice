/** This is a simple and multuple linear regression 
 * program matrix operations and the OLS method to solve for the 
 * coefficients.
 * 
 * Author:  Giovanni Stephens
 * Date:    29/04/2022
 */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <chrono>
#include "Regressor.h"

// Default constructor
Matrix::Matrix() {
}

Matrix::Matrix(int rows, int cols) {
    n = rows;
    matrix.resize(rows);
    for (int i = 0; i < rows; i++) {
        matrix[i].resize(cols);
    }
}

Matrix::~Matrix() {
    matrix.clear();
}

float& Matrix::operator()(int i,int j) {
    return matrix[i][j];
}

Matrix Matrix::cofactor(unsigned int p, unsigned int q) {
    Matrix cofactor(n-1, n-1);
    unsigned int i = 0;
    unsigned int j = 0;
    for (unsigned int row = 0; row < n; row++) {
        for (unsigned int col = 0; col < n; col++) {
            if (row != p && col != q) {
                cofactor.matrix[i][j] = matrix[row][col];
                j++;
                if (j == n-1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
    return cofactor;
}

float Matrix::determinant() {
    // calculate determinant recursively by computing the determinant of the cofactors.
    if(n == 1){
        return matrix[0][0];
    }

    float Det = 0;
    float s;
    Matrix Cof(n-1, n-1);

    for(unsigned int i = 0; i < n; i++){
        Cof = cofactor(0, i);
        s = pow(-1, i)*matrix[0][i]*Cof.determinant();
        Det += s;
    }
    return Det;
}

Matrix Matrix::inverse(){
    // get determinant of the matrix
    float Det = this->determinant();

    Matrix Cof(n-1, n-1);
    Matrix Inv(n, n);
    float s;

    // calculate inverse as the transpose of the adjugate matrix.
    for(size_t i = 0; i < n; i++){
        for(size_t j = 0; j < n; j++){

            Cof = cofactor(i,j);
            s = pow(-1, i + j);
            Inv(j, i) = s*Cof.determinant()/Det;

        }
    }
    return Inv;
}

Matrix Matrix::transpose() {
    Matrix transpose(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            transpose(j, i) = matrix[i][j];
        }
    }
    return transpose;
}

Matrix Matrix::multiply(Matrix m) {
    Matrix product(n, m.n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m.n; j++) {
            for (int k = 0; k < n; k++) {
                product(i, j) += matrix[i][k] * m(k, j);
            }
        }
    }
    return product;
}

void Matrix::print() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


LinearRegressor::LinearRegressor(std::vector<std::vector<float>> x, std::vector<float> y) {
    this->X = Matrix(x.size(), x[0].size() + 1);
    this->Y = Matrix(y.size(), 1);
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[0].size() + 1; j++) {
            if (j == 0) {
                this->X(i, j) = 1;
            } else {
                this->X(i, j) = x[i][j - 1];
            }
        }
    }
    for (int i = 0; i < y.size(); i++) {
        this->Y(i, 0) = y[i];
    }
}

LinearRegressor::~LinearRegressor() {
    coefficients.clear();
    X.~Matrix();
    Y.~Matrix();
}

void LinearRegressor::fit() {
    // create matrix of x values
    Matrix X_transpose = X.transpose();

    // X^T * X
    Matrix X_transpose_X = X_transpose.multiply(X);

    // X^T * Y
    Matrix X_transpose_Y = X_transpose.multiply(Y);

    // (X^T * X)^-1
    Matrix X_transpose_X_inverse = X_transpose_X.inverse();

    // (X^T * X)^-1 * X^T * Y
    Matrix X_transpose_X_inverse_X_transpose_Y = X_transpose_X_inverse.multiply(X_transpose_Y);

    // Update the coefficients, but first clear the coefficients vector
    coefficients.clear();
    for (int i = 0; i < X_transpose_X_inverse_X_transpose_Y.n; i++) {
        coefficients.push_back(X_transpose_X_inverse_X_transpose_Y(i, 0));
    }
}

float LinearRegressor::predict(std::vector<float> x) {
    float y_prediction;
    y_prediction = coefficients[0];
    for (int i = 1; i < coefficients.size(); i++) {
        y_prediction += coefficients[i] * x[i - 1];
    }
    return y_prediction;
}


/*
int main() {
    std::vector<std::vector<float>> x = {
        {1, 2, 3},
        {3, 2, 2},
        {3.5, 2.5, 1},
        {5, 2, 0}
    };

    std::vector<float> y = {
        1,
        2,
        3,
        4
    };

    LinearRegressor lr(x, y);
    // Timer to see how long it takes to fit the model
    Timer timer;
    lr.fit();
    std::cout << "Time to fit: " << timer.elapsed_time() << std::endl;
    std::cout << "Coefficients: ";
    for (int i = 0; i < lr.coefficients.size(); i++) {
        std::cout << lr.coefficients[i] << " ";
    }
    std::cout << std::endl;

    // Make a prediction
    std::vector<float> x_test = {
        4,
        2,
        3
    };
    // print input and prediction
    std::cout << "Input: ";
    for (int i = 0; i < x_test.size(); i++) {
        std::cout << x_test[i] << " ";
    }
    std::cout << "Prediction: " << lr.predict(x_test) << std::endl;
    return 0;
}
*/
