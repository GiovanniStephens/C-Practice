/** This is a simple linear regression program
 * that uses the OLS method to solve for the 
 * coefficients.
 * 
 * Author:  Giovanni Stephens
 * Date:    12/04/2022
 */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

class Matrix {
public:
    Matrix(int rows, int cols);
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

Matrix::Matrix(int rows, int cols) {
    n = rows;
    matrix.resize(rows);
    for (int i = 0; i < rows; i++) {
        matrix[i].resize(cols);
    }
}

double& Matrix::operator()(int i,int j) {
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

double Matrix::determinant() {
    // calculate determinant recursively by computing the determinant of the cofactors.
    if(n == 1){
        return matrix[0][0];
    }

    double Det = 0;
    double s;
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
    double Det = this->determinant();

    Matrix Cof(n-1, n-1);
    Matrix Inv(n, n);
    double s;

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


class LinearRegressor {
    private:
        std::vector<std::vector<double>> x;
        std::vector<double> y;
    public:
        std::vector<double> coefficients;
        LinearRegressor(std::vector<std::vector<double>> x, std::vector<double> y);
        ~LinearRegressor();
        void fit();
};

LinearRegressor::LinearRegressor(std::vector<std::vector<double>> x, std::vector<double> y) {
    this->x = x;
    this->y = y;
}

LinearRegressor::~LinearRegressor() {
    x.clear();
    y.clear();
    coefficients.clear();
}

void LinearRegressor::fit() {
    // create matrix of x values with a column of 1's at the first column
    Matrix X(x.size(), x[0].size() + 1);
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[0].size() + 1; j++) {
            if (j == 0) {
                X(i, j) = 1;
            } else {
                X(i, j) = x[i][j-1];
            }
        }
    }
    X.print();
    std::cout << std::endl;

    // create matrix of y values
    Matrix Y(y.size(), 1);
    for (int i = 0; i < y.size(); i++) {
        Y(i, 0) = y[i];
    }
    Y.print();
    std::cout << std::endl;

    // create matrix of x values
    Matrix X_transpose = X.transpose();
    X_transpose.print();
    std::cout << std::endl;

    // X^T * X
    Matrix X_transpose_X = X_transpose.multiply(X);
    X_transpose_X.print();
    std::cout << std::endl;

    // X^T * Y
    Matrix X_transpose_Y = X_transpose.multiply(Y);
    X_transpose_Y.print();
    std::cout << std::endl;

    // (X^T * X)^-1
    Matrix X_transpose_X_inverse = X_transpose_X.inverse();
    X_transpose_X_inverse.print();
    std::cout << std::endl;

    // (X^T * X)^-1 * X^T * Y
    Matrix X_transpose_X_inverse_X_transpose_Y = X_transpose_X_inverse.multiply(X_transpose_Y);
    X_transpose_X_inverse_X_transpose_Y.print();
    std::cout << std::endl;

    // Update the coefficients
    for (int i = 0; i < X_transpose_X_inverse_X_transpose_Y.n; i++) {
        coefficients.push_back(X_transpose_X_inverse_X_transpose_Y(i, 0));
    }
}

int main() {
    std::vector<std::vector<double>> x = {
        {1, 2, 3},
        {3, 2, 2},
        {3.5, 2.5, 1},
        {5, 2, 0}
    };

    std::vector<double> y = {
        1,
        2,
        3,
        4
    };

    LinearRegressor lr(x, y);
    lr.fit();
    std::cout << "Coefficients: ";
    for (int i = 0; i < lr.coefficients.size(); i++) {
        std::cout << lr.coefficients[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
