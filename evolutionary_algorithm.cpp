/* This is my attempt at creating an EA.
 *
 * Date:    31/08/2022
 * Author:  Giovanni Stephens
 */

#include <iostream>
#include <vector>

class EA {
    int population_size;
    int generations;
    float crossover_probability;
    float mutation_probability;
    bool elitism;

    public:
        EA(int population_size,
           int generations,
           float crossover_probability,
           float mutation_probability,
           bool elitism) {
            this->population_size = population_size;
            this->generations = generations;
            this->crossover_probability = crossover_probability;
            this->mutation_probability = mutation_probability;
            this->elitism = elitism;
           }
};


int main() {

    return 1;
}