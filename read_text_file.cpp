/** This program reads a text file.
 * It is purely for learning purposes.
 *
 * Author: Giovanni Stephens
 * Date:   07/04/2022
 */
#include <iostream>
#include <fstream>

int main() {
    std::ifstream infile;
    infile.open("write_text_file.txt");
    std::string line;
    while (std::getline(infile, line)) {
        std::cout << line << std::endl;
    }
    infile.close();
    return 0;
}