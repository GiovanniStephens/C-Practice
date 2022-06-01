/** This is a leetcode solution to the string to int converter.
 * 
 * Problem on leetcode is here: https://leetcode.com/problems/string-to-integer-atoi/
 *
 * Author:  Giovanni Stephens
 * Date:    17/04/2022
 */
#include <iostream>
#include <string>
#include <climits>

class Solution {
public:
    int myAtoi(std::string s) {
        long res = 0;
        int sign = 1;
        int MAX = INT_MAX;
        int MIN = INT_MIN;
        
        if (s.length() == 0) {
            return res;
        }
        // Get the starting position of the number
        int i = 0;
        while (s[i] == ' ') {
            i++;
        }
        // Check for the sign
        if (s[i] == '-') {
            sign = -1;
            i++;
        } else if (s[i] == '+') {
            i++;
        }
        while (isdigit(s[i])) {
            res = res * 10 + (s[i] - '0');
            if (sign*res < 0 && sign*res < MIN) {
                return MIN;
            }
            if (sign*res > 0 && sign*res > MAX) {
                return MAX;
            }
            i++;
        }
        return sign*res;
    }
};

int main() {
    Solution s;
    std::string str = "   -42";
    std::cout << s.myAtoi(str) << std::endl;
    return 0;
}