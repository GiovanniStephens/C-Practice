/* This is a basic implementation of a k-means clustering algorithm.
 * The data are points in a 2D space. The goal is to find the best
 * centroids to cluster the data.
 * 
 * Author:   Giovanni Stephens
 * Date:     12/06/2022
 */

#include <vector>
#include <iostream>
#include <cmath>
#include <string>

class k_means {
    private:
        std::vector<std::vector<float>> data;
        int n_initialisations;
        int max_iterations;
        float tolerance;
        int n_features_in;
        std::string init_method;
        int n_clusters;
        
        std::vector<float> minimum(std::vector<std::vector<float>> *data);
        std::vector<float> maximum(std::vector<std::vector<float>> *data);
        std::vector<std::vector<float>> initialise_centroids(std::vector<std::vector<float>> *data, int k);
        std::vector<std::vector<float>> initialise_centroids_random(std::vector<std::vector<float>> *data, int k);
        std::vector<std::vector<float>> initialise_centroids_kmeanspp(std::vector<std::vector<float>> *data, int k);
        float euclidian_distance(std::vector<float> *x, std::vector<float> *y);
        void update_centroid(std::vector<std::vector<float>> *data, std::vector<std::vector<float>> *centroids, std::vector<int> *clusters);
        int classify(std::vector<std::vector<float>> *data, std::vector<std::vector<float>> *centroids, int item);
        float calculate_inertia(std::vector<std::vector<float>> *data, std::vector<std::vector<float>> *centroids, std::vector<int> *clusters);
    public:
        std::vector<std::vector<float>> centroids;
        std::vector<int> labels;
        float inertia;
        k_means(std::vector<std::vector<float>> *data,
                std::string init_method = "k-means++",
                int n_initialisations = 1, 
                int n_clusters = 2,
                int max_iterations = 100, 
                float tolerance = 0.001); 
        void fit_predict();
        std::vector<int> predict(std::vector<std::vector<float>> *data);
};
        
        

std::vector<float> k_means::minimum(std::vector<std::vector<float>> *data) {
    std::vector<float> min;
    for (int i = 0; i < data->at(0).size(); i++) {
        float min_i = data->at(0).at(i);
        for (int j = 0; j < data->size(); j++) {
            if (data->at(j).at(i) < min_i) {
                min_i = data->at(j).at(i);
            }
        }
        min.push_back(min_i);
    }
    return min;
}

std::vector<float> k_means::maximum(std::vector<std::vector<float>> *data) {
    std::vector<float> max;
    for (int i = 0; i < data->at(0).size(); i++) {
        float max_i = data->at(0).at(i);
        for (int j = 0; j < data->size(); j++) {
            if (data->at(j).at(i) > max_i) {
                max_i = data->at(j).at(i);
            }
        }
        max.push_back(max_i);
    }
    return max;
}

std::vector<std::vector<float>> k_means::initialise_centroids(std::vector<std::vector<float>> *data, int k) {
    std::vector<std::vector<float>> centroids;

    if (k > data->size()) {
        std::cout << "Error: k is greater than the number of data points" << std::endl;
        return centroids;
    }

    if (k == data->size()) {
        for (int i = 0; i < data->size(); i++) {
            centroids.push_back(data->at(i));
        }
        return centroids;
    }

    if (init_method == "random") {
        centroids = initialise_centroids_random(data, k);
    } else if (init_method == "k-means++") {
        centroids = initialise_centroids_kmeanspp(data, k);
    } else {
        std::cout << "Error: invalid init_method" << std::endl;
    }

    return centroids;
}

std::vector<std::vector<float>> k_means::initialise_centroids_random(std::vector<std::vector<float>> *data, int k) {
    std::vector<std::vector<float>> centroids;
    std::vector<int> indices;
    for (int i = 0; i < data->size(); i++) {
        indices.push_back(i);
    }
    for (int i = 0; i < k; i++) {
        int index = rand() % indices.size();
        centroids.push_back(data->at(indices.at(index)));
        indices.erase(indices.begin() + index);
    }
    return centroids;
}

std::vector<std::vector<float>> k_means::initialise_centroids_kmeanspp(std::vector<std::vector<float>> *data, int k) {
    std::vector<std::vector<float>> centroids;
    
    // Initialise the first centroid randomly
    std::vector<int> indices;
    for (int i = 0; i < data->size(); i++) {
        indices.push_back(i);
    }
    int index = rand() % indices.size();
    centroids.push_back(data->at(indices.at(index)));
    indices.erase(indices.begin() + index);

    // Initialise the rest of the centroids using k-means++
    for (int i = 1; i < k; i++) {
        std::vector<float> distances;
        float sum = 0;
        for (int j = 0; j < indices.size(); j++) {
            float distance = euclidian_distance(&centroids.at(i - 1), &data->at(indices.at(j)));
            distances.push_back(distance);
            sum += distance;
        }
        float r = (float)rand() / (float)RAND_MAX * sum;
        float sum_i = 0;
        for (int j = 0; j < distances.size(); j++) {
            sum_i += distances.at(j);
            if (sum_i >= r) {
                centroids.push_back(data->at(indices.at(j)));
                indices.erase(indices.begin() + j);
                break;
            }
        }
    }
    return centroids;
}


float k_means::euclidian_distance(std::vector<float> *x, std::vector<float> *y) {
    float distance = 0;
    for (int i = 0; i < x->size(); i++) {
        distance += pow(x->at(i) - y->at(i), 2);
    }
    return sqrt(distance);
}

void k_means::update_centroid(std::vector<std::vector<float>> *data, std::vector<std::vector<float>> *centroids, std::vector<int> *clusters) {
    for (int i = 0; i < centroids->size(); i++) {
        std::vector<float> centroid;
        for (int j = 0; j < centroids->at(0).size(); j++) {
            centroid.push_back(0);
        }
        int count = 0;
        for (int j = 0; j < clusters->size(); j++) {
            if (clusters->at(j) == i) {
                for (int k = 0; k < data->at(j).size(); k++) {
                    centroid.at(k) += data->at(j).at(k);
                }
                count++;
            }
        }
        for (int j = 0; j < centroid.size(); j++) {
            centroid.at(j) /= count;
        }
        centroids->at(i) = centroid;
    }
}

int k_means::classify(std::vector<std::vector<float>> *data, std::vector<std::vector<float>> *centroids, int item) {
    int index = -1;
    float min = 1000000;
    for (int i = 0; i < centroids->size(); i++) {
        float distance = euclidian_distance(&data->at(item), &centroids->at(i));
        if (distance < min) {
            min = distance;
            index = i;
        }
    }
    return index;
}

k_means::k_means(std::vector<std::vector<float>> *data,
                 std::string init_method,
                 int n_initialisations,
                 int n_clusters,
                 int max_iterations,
                 float tolerance) {
    this->data = *data;
    this->init_method = init_method;
    this->n_initialisations = n_initialisations;
    this->n_clusters = n_clusters;
    this->max_iterations = max_iterations;
    this->tolerance = tolerance;
    this->n_features_in = data->at(0).size();
}

float k_means::calculate_inertia(std::vector<std::vector<float>> *data, std::vector<std::vector<float>> *centroids, std::vector<int> *clusters) {
    float inertia = 0;
    for (int i = 0; i < data->size(); i++) {
        inertia += pow(euclidian_distance(&data->at(i), &centroids->at(clusters->at(i))), 2);
    }
    return inertia;
}

void k_means::fit_predict() {
    float best_inertia = 1000000;
    for (int i = 0; i < n_initialisations; i++) {
        std::vector<std::vector<float>> centroids = initialise_centroids(&data, n_clusters);
        std::vector<int> labels;
        for (int j = 0; j < data.size(); j++) {
            labels.push_back(0);
        }
        int iterations = 0;
        while (iterations < max_iterations) {
            std::vector<int> new_labels;
            for (int j = 0; j < data.size(); j++) {
                int label = classify(&data, &centroids, j);
                new_labels.push_back(label);
            }

            if (new_labels == labels) {
                break;
            }
            labels = new_labels;
            update_centroid(&data, &centroids, &labels);
            iterations++;
        }
        inertia = calculate_inertia(&data, &centroids, &labels);
        if (inertia < best_inertia) {
            best_inertia = inertia;
            this->inertia = inertia;
            this->centroids = centroids;
            this->labels = labels;
        }
    }
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

    // Run the k-means algorithm with k = 2
    k_means kmeans(&data, "random", 2, 2, 100, 0.001);
    kmeans.fit_predict();

    // Print the results
    std::cout << "Inertia: " << kmeans.inertia << std::endl;
    std::cout << "Centroids: " << std::endl;
    for (int i = 0; i < kmeans.centroids.size(); i++) {
        std::cout << "Cluster " << i << ": ";
        for (int j = 0; j < kmeans.centroids.at(0).size(); j++) {
            std::cout << kmeans.centroids.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }

    // Print the labels
    std::cout << "Labels: " << std::endl;
    for (int i = 0; i < kmeans.labels.size(); i++) {
        std::cout << kmeans.labels.at(i) << " ";
    }

    return 0;
}