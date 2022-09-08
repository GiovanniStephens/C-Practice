/* This is my attempt at creating an EA.
 *
 * Date:    31/08/2022
 * Author:  Giovanni Stephens
 */

#include <iostream>
#include <vector>
using namespace std;

class EA {
    int population_size;
    int generations;
    float crossover_probability;
    float mutation_probability;
    bool elitism;
    vector<vector<int>> population;

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

        void create_individual(int len){
            /* Creates a random binary vector 
             * to represent a random gene. 
             *
             * Todo: Paralellize this.
             */
            vector<int> individual;
            for (int i = 0; i < len; i++){
                individual.push_back(rand() % 2);
            }
            population.push_back(individual);
        }
};


int main() {

    return 1;
}