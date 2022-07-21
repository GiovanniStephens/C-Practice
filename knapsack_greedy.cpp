/* Greedy algorithm to solve the 
 * knapsack problem.
 * 
 * Author:  Giovanni Stephens
 * Date:    21/07/2022
 */

#include <iostream>
#include <vector>

std::vector<std::vector<int>> sort_items(std::vector<std::vector<int>> items) {
    /* Sorts the items based on their value per unit of weight using 
     * selection sort.
     */
    std::vector<float> value_per_weight;
    for (int i = 0; i < items.size(); i++) {
        value_per_weight.push_back((float)items[i][1] / (float)items[i][0]);
    }
    for (int i = 0; i < items.size(); i++) {
        int index = i;
        for (int j = i; j < value_per_weight.size(); j++) {
            if (value_per_weight[j] > value_per_weight[index]) {
                index = j;
            }
        }
        // swap the elements
        std::vector<int> temp = items[i];
        items[i] = items[index];
        items[index] = temp;
        float val_per_weight_temp = value_per_weight[i];
        value_per_weight[i] = value_per_weight[index];
        value_per_weight[index] = val_per_weight_temp;
    }
    return items;
}

std::vector<std::vector<int>> knapsack_greedy(std::vector<std::vector<int>> items, int capacity) {
    std::vector<std::vector<int>> knapsack;
    int current_weight = 0;
    int current_value = 0;
    std::vector<std::vector<int>> sorted_items = sort_items(items);
    for (auto item : sorted_items) {
        if (current_weight + item[0] <= capacity) {
            knapsack.push_back(item);
            current_weight += item[0];
            current_value += item[1];
        } else {
            continue;
        }
    }
    return knapsack;
}

int main() {
    // Weight, value
    std::vector<std::vector<int>> items = {{10,2}, {20,3}, {30,4}, {40,20}, {50,5}};
    int capacity = 60;

    std::vector<std::vector<int>> knapsack = knapsack_greedy(items, capacity);

    for (auto item : knapsack) {
        std::cout << item[0] << " " << item[1] << std::endl;
    }

    return 0;
}