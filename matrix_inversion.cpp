/** This program shows how to invert a matrix
 * using loops.
 * 
 * Author:  Giovanni Stephens
 * Date:    26/04/2022
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
    void print();
private:
    unsigned int n;
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

void Matrix::print() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {10, 3, 4},
        {7, 8, 9}
    };

    Matrix m(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m(i, j) = matrix[i][j];
        }
    }

    std::cout << "Matrix:" << std::endl;
    m.print();
    std::cout << "Determinant: " << m.determinant() << std::endl;
    std::cout << "Inverse:" << std::endl;
    m.inverse().print();
    return 0;
}