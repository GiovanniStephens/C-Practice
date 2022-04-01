/* This is a basic practice program to learn how
 * to declare functions and work with strings.
 *
 * Author:  Giovanni Stephens
 * Date:    01/04/2022
 */ 

#include <iostream>
#include <vector>

// Prints a string to the console
void print_string(std::string s) {
    std::cout << s << std::endl;
}

// Converts int to string
std::string int_to_string(int i) {
    std::string s = std::to_string(i);
    return s;
}

// Split string at an index
std::string split_string(std::string s, int index) {
    return s.substr(index);
}

// Find a substring
int find_substring(std::string s, std::string sub) {
    return s.find(sub);
}

// Reverse a string
std::string reverse_string(std::string s) {
    std::string reversed = "";
    for (int i = s.length() - 1; i >= 0; i--) {
        reversed += s[i];
    }
    return reversed;
}

// To upper case
std::string to_upper_case(std::string s) {
    std::string upper_case = "";
    for (int i = 0; i < s.length(); i++) {
        upper_case += toupper(s[i]);
    }
    return upper_case;
}

// To lower case
std::string to_lower_case(std::string s) {
    std::string lower_case = "";
    for (int i = 0; i < s.length(); i++) {
        lower_case += tolower(s[i]);
    }
    return lower_case;
}

// Split string on spaces
std::vector<std::string> split_string_on_spaces(std::string s) {
    std::vector<std::string> split_string;
    std::string current_word = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            split_string.push_back(current_word);
            current_word = "";
        } else {
            current_word += s[i];
        }
    }
    split_string.push_back(current_word);
    return split_string;
}

int main() {
    std::string s = "Hello World!";
    print_string(s);
    print_string(split_string(s, 5));
    print_string(int_to_string(find_substring(s, "World")));
    print_string(reverse_string(s));
    print_string(to_upper_case(s));
    print_string(to_lower_case(s));
    std::vector<std::string> split_string = split_string_on_spaces(s);
    for (int i = 0; i < split_string.size(); i++) {
        print_string(split_string[i]);
    }
    return 0;
}
