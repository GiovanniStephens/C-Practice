/** This program shows how to invert a matrix
 * using loops.
 * 
 * Author:  Giovanni Stephens
 * Date:    26/04/2022
 */
#include <iostream>
#include <vector>
#include <string>

class Matrix {
public:
    Matrix(std::vector<std::vector<double>> matrix);
    Matrix cofactor(size_t p, size_t q);
    double determinant();
    Matrix inverse();
    void print();
private:
    size_t n;
    std::vector<std::vector<double>> matrix;
};

Matrix::Matrix(std::vector<std::vector<double>> matrix) {
    this->matrix = matrix;
    this->n = matrix.size();
}




int main() {
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    std::vector<std::vector<int>> result;

    // Todo - implement matrix inversion

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[0].size(); j++) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
}