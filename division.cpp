/** This program is to see how division works in C++.
 *
 * Author:  Giovanni Stephens
 * Date:    16/04/2022
 */
#include <iostream>

int main() {
    int a = 5;
    int b = 2;
    int c = a / b;
    float d = a / b;
    float e = 5.0;
    std::cout << "a / b (int division) = " << c << std::endl;
    std::cout << "Float of a / b (d is a float) = " << d << std::endl;
    std::cout << "Float of b / e (mixed division) = " << b / e << std::endl;
    return 0;
}