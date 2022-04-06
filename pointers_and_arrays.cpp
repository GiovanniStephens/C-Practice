/** This is an example of using pointers and arrays in C++.
 * This is for my learning purposes.
 * 
 * Reference: https://www.cplusplus.com/doc/tutorial/pointers/
 * 
 * Modified by: Giovanni Stephens
 * Date: 06/04/2022
 */

#include <iostream>
using namespace std;

int main () {
    int numbers[5];
    int * p;

    p = numbers;        // p points to the first element of numbers
    *p = 10;            // numbers[0] = 10
    p++;                // p points to numbers[1]
    *p = 20;            // numbers[1] = 20
    p = &numbers[2];    // p points to numbers[2]
    *p = 30;            // numbers[2] = 30
    p = numbers + 3;    // p points to numbers[3]
    *p = 40;            // numbers[3] = 40
    p = numbers;        // p points to numbers[0]
    *(p+4) = 50;        // numbers[4] = 50
    for (int n=0; n<5; n++)
        cout << numbers[n] << ", ";
    // Output: 10, 20, 30, 40, 50,
    return 0;
}