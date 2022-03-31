/* This is a basic program to test the declaration of variables.
 * 
 * Author: Giovanni Stephens
 * Date: 31/03/2022
 */

#include <iostream>

int main() {
    int var1;
    int var2;
    int var3;
    var1 = var2 = var3 = 5; // Each variable is assigned a value of 5.
    var1 = 3; // Should not change the others.
    std::cout << "var1: " +  std::to_string(var1) << std::endl;
    std::cout << "var2: " +  std::to_string(var2) << std::endl;
    std::cout << "var3: " +  std::to_string(var3) << std::endl;
    return 0;
}