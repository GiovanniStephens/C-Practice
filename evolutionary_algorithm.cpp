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

    void crossover(vector<int> *parent_1, vector<int> *parent_2,
                   vector<int> *child) {
        /* Does a random split between two individials.*/

        // Pick a random splitting point
        // Update the child with values from parent_1
        // on the left of the splitting point,
        // and parent_2 on the right.
    }

    void random_crossover(vector<int> *parent_1, vector<int> *parent_2,
                          vector<int> *child) {
        /* Does a random crossover between two individials.*/

        // for each element in the child, randomly pick
        // from either of the parents.
    }

  public:
    EA(int population_size, int generations, float crossover_probability,
       float mutation_probability, bool elitism) {
        this->population_size = population_size;
        this->generations = generations;
        this->crossover_probability = crossover_probability;
        this->mutation_probability = mutation_probability;
        this->elitism = elitism;
    }

    void create_individual(int len) {
        /* Creates a random binary vector
         * to represent a random gene.
         *
         * Todo: Paralellize this.
         */
        vector<int> individual;
        for (int i = 0; i < len; i++) {
            individual.push_back(rand() % 2);
        }
        population.push_back(individual);
    }
};

int main() { return 1; }