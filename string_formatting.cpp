/* This is a basic practice program to learn how
 * to use string formatting.
 *
 * Author:  Giovanni Stephens
 * Date:    01/04/2022
 */

#include <iostream>

int main() {
    int some_int = 42;
    double some_double = 3.14159;
    std::string some_string = "Hello World!";

    // Using printf
    std::cout << "Using printf" << std::endl;
    printf("Some int is: %d\n", some_int);
    printf("some_double is: %f\n", some_double);
    printf("Some string is: %s\n", some_string.c_str());    
    return 0;
}