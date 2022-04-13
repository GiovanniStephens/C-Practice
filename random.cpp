/** This is to understand the std library random
 * functions.
 * 
 * Author:  Giovanni Stephens
 * Date:    13/04/2022
 */
#include <stdlib.h>
#include <iostream>

int main() {
    // Set the seed
    srand(time(NULL));
    
    std::cout << "Testing the rand() function" << std::endl;
    std::cout << "The random number is: " << rand() << std::endl;
    std::cout << "Another random number is: " << rand() << std::endl;
    std::cout << "Another random number is: " << rand() << std::endl;

    std::cout << "Trying to get a random number between 0 and 1" << std::endl;
    std::cout << "The random number is: " << (double)rand() / (double)RAND_MAX << std::endl;

    std::cout << "Trying to get a random number between 0 and 10" << std::endl;
    std::cout << "The random number is: " << (double)rand() / (double)RAND_MAX * 10 << std::endl;
    return 0;
}