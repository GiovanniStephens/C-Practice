/** This is a basic matrix multiplication program.
 * 
 * Author:  Giovanni Stephens
 * Date:    26/04/2022
 */
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::vector<int>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    std::vector<std::vector<int>> matrix2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    std::vector<std::vector<int>> result;

    for (int i = 0; i < matrix1.size(); i++) {
        std::vector<int> row;
        for (int j = 0; j < matrix2[0].size(); j++) {
            int sum = 0;
            for (int k = 0; k < matrix1[0].size(); k++) {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            row.push_back(sum);
        }
        result.push_back(row);
    }

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[0].size(); j++) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
}