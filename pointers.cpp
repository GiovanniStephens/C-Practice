/** This is a basic demo showing how pointers
 * can be used in C++. This is for my practice in
 * this language.
 * 
 * Author: Giovanni Stephens
 * Date:   06/04/2022
 */

#include <iostream>
#include <string>

int main() {
    std::string name = "Giovanni";
    // Print the address to the name variable
    std::cout << "The address of the name variable is: " << &name << std::endl;
    // Make a pointer to the name variable
    std::string *name_pointer = &name;
    // Print the address of the name_pointer variable
    std::cout << "The address of the name_pointer pointer is: " << &name_pointer << std::endl;
    // Print the address of the name_pointer variable
    std::cout << "The address of the name_pointer variable is: " << name_pointer << std::endl;
}