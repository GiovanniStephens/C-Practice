/** This is a practice program. The problem
 * came from LeetCode.com.
 * 
 * https://leetcode.com/problems/roman-to-integer/
 * 
 * Author:  Giovanni Stephens
 * Date:    14/04/2022
 */

#include <iostream>
#include <string>

class Solution {
public:
    int romanToInt(std::string s);
    int charToInt(char c);
};

int Solution::charToInt(char c) {
    switch(c) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default :
            return 0;
    }
}

int Solution::romanToInt(std::string s) {
    int total = 0;
    for (int i=0; i<s.length(); i++) {
        int current_value = charToInt(s[i]);
        if (i+1 < s.length()) {
            int next_value = charToInt(s[i+1]);
            if (next_value > current_value) {
                total+=next_value-current_value;
                i++;
            } else {
                total+=current_value;
            }
        } else {
            total+=current_value;
        }
    }
    return total;
}

int main() {
    Solution s;
    std::cout << "Int for III: " << s.romanToInt("III") << std::endl;
    std::cout << "Int for IV: " << s.romanToInt("IV") << std::endl;
    std::cout << "Int for IX: " << s.romanToInt("IX") << std::endl;
    std::cout << "Int for LVIII: " << s.romanToInt("LVIII") << std::endl;
    return 0;
}