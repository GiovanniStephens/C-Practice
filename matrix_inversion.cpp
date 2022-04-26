/** This program shows how to invert a matrix
 * using loops.
 * 
 * Author:  Giovanni Stephens
 * Date:    26/04/2022
 */
#include <iostream>
#include <vector>
#include <string>

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