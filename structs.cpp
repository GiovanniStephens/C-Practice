/** This is a basic program to learn how to use structs.
 *
 * Author:  Giovanni Stephens
 * Date:    10/04/2022
 */
#include <iostream>

struct house {
    // Public members by default
    int bedrooms;
    int bathrooms;
    int square_feet;
    int year_built;
};

int main() {
    // Create a struct
    house my_house;

    // Assign values to the struct
    my_house.bedrooms = 3;
    my_house.bathrooms = 2;
    my_house.square_feet = 1000;
    my_house.year_built = 2020;

    // Print the values
    std::cout << "My house has " << my_house.bedrooms << " bedrooms, "
              << my_house.bathrooms << " bathrooms, "
              << my_house.square_feet << " square feet, and was built in "
              << my_house.year_built << std::endl;

    return 0;
}
