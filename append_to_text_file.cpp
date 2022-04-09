/** This is a basic program to practice using C++.
 * It reads a .txt file and then appends some text to
 * the end of the file.
 * 
 * Author: Giovanni Stephens
 * Date:   09/04/2022
 */
#include <iostream>
#include <fstream>

int main() {
    // Same as writing a file.
    std::ofstream outfile;
    outfile.open("write_text_file.txt", std::ios_base::app);
    outfile << "This is a new line of text." << std::endl;
    outfile.close();
    return 0;
}