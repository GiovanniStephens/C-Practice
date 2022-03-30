#include <iostream>
#include <string>

int main() {
    std::string s = "Hello World!";
    std::cout << s << std::endl;

    // Reverse string
    int len = s.length();
    char reversed[len] = {};
    for (int i = 0; i < len; i++) {
        reversed[i] = s[len - i - 1];
    }
    std::cout << reversed << std::endl;
    return 0;
}