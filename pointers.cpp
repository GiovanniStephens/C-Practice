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
    std::cout << "The address of the name variable is: " << &name << std::endl;
    std::string *name_pointer = &name;
    std::cout << "The address of the name_pointer pointer is: " << &name_pointer << std::endl;
    std::cout << "The address of the name_pointer variable is: " << name_pointer << std::endl;
    std::cout << "The value that the name_pointer points to is: " << *name_pointer << std::endl;

    std::string *name_pointer2 = name_pointer;
    std::cout << "The address of the name_pointer2 pointer is: " << &name_pointer2 << std::endl;
    std::cout << "The address of the name_pointer2 variable is: " << name_pointer2 << std::endl;
    std::cout << "The value that the name_pointer2 points to is: " << *name_pointer2 << std::endl;
}