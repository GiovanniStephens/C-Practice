/* This is a short program showing how disctionaries work in C++.
 * It is a practice program to get familiar with C++.
 *
 * Author: Giovanni Stephens
 * Date:   29/03/2022
 */
#include <iostream>
#include <map>
#include <string>

int main(){
    std::map<std::string, int> dictionary;
    dictionary["Hello"] = 1;
    dictionary["World"] = 2;
    std::cout << dictionary["Hello"] << std::endl; // 1
    std::cout << dictionary["World"] << std::endl; // 2
    return 0;
}