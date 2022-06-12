/* This is a basic implementation of a k-means clustering algorithm.
 * The data are points in a 2D space. The goal is to find the best
 * centroids to cluster the data.
 * 
 * Author:   Giovanni Stephens
 * Date:     12/06/2022
 */

#include <vector>
#include <iostream>

float minimum(std::vector<std::vector<float>> *data) {
    float min = data->at(0).at(0);
    for (int i = 0; i < data->size(); i++) {
        for (int j = 0; j < data->at(i).size(); j++) {
            if (data->at(i).at(j) < min) {
                min = data->at(i).at(j);
            }
        }
    }
    return min;
}

float maximum(std::vector<std::vector<float>> *data) {
    float max = data->at(0).at(0);
    for (int i = 0; i < data->size(); i++) {
        for (int j = 0; j < data->at(i).size(); j++) {
            if (data->at(i).at(j) > max) {
                max = data->at(i).at(j);
            }
        }
    }
    return max;
}

std::vector<std::vector<float>> initialise_centroids(std::vector<std::vector<float>> *data, int k) {
    std::vector<std::vector<float>> centroids;
    float min = minimum(data);
    float max = maximum(data);

    for (int i = 0; i < k; i++) {
        std::vector<float> centroid;
        for (int j = 0; j < data->at(0).size(); j++) {
            centroid.push_back(min + (max - min) * (float)rand() / (float)RAND_MAX);
        }
        centroids.push_back(centroid);
    }

    return centroids;
}


int main() {
    // create a 2d vector of floats with two clusters
    std::vector<std::vector<float>> data = {
        {1.0, 1.0},
        {2.0, 2.0},
        {1.0, 2.0},
        {2.0, 1.0},
        {4.0, 4.0},
        {3.0, 4.0},
        {4.0, 3.0},
        {5.0, 5.0},
        {4.0, 5.0}
    };

    // Find the minimum value in the data
    float min = minimum(&data);

    // Print the minimum
    std::cout << "Minimum: " << min << std::endl;

    // Find the maximum value in the data
    float max = maximum(&data);

    // Print the maximum
    std::cout << "Maximum: " << max << std::endl;

    // Initialise the centroids
    std::vector<std::vector<float>> centroids = initialise_centroids(&data, 2);

    // Print the centroids
    std::cout << "Centroids: " << std::endl;
    for (int i = 0; i < centroids.size(); i++) {
        for (int j = 0; j < centroids.at(i).size(); j++) {
            std::cout << centroids.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
    

    return 0;
}