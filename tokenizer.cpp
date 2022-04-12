/** This program is to split a string 
 * into tokens for further processing.
 * This step is a prerequisite for the
 * training of a word2vec model.
 * 
 * Author:  Giovanni Stephens
 * Date:    12/04/2022
 */

#include <iostream>
#include <vector>
#include <string>

int main(){
    std::string str = "This is a test string";
    std::vector<std::string> tokens;
    std::string token;
    std::string delimiter = " ";
    size_t pos = 0;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    tokens.push_back(str);
    for (auto &t : tokens) {
        std::cout << t << std::endl;
    }
    return 0;
}