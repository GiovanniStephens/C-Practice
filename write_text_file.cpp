/** This program writes a text file.
 * It is purely for learning purposes.
 *
 * Author: Giovanni Stephens
 * Date:   07/04/2022
 */

#include <iostream>
#include <fstream>

int main() {
    std::ofstream outfile;
    outfile.open("write_text_file.txt");
    outfile << "This is a text file." << std::endl;
    outfile.close();
    return 0;
}