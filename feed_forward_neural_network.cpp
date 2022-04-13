/** This is an basic implementaion of a 
 * feed forward neural network (perceptron).
 * This is practice program.
 * 
 * Author:  Giovanni Stephens
 * Date:    13/04/2022
 */
#include <stdlib>

// Number of inputs
#define INPUTS 3
// Number of outputs
#define OUTPUTS 1
// Number of hidden layers
#define HIDDEN_LAYERS 2
// Number of neurons per hidden layer
#define HIDDEN_NEURONS 2
// Number of weights per neuron
#define WEIGHTS_PER_NEURON 2
// Number of weights per hidden layer
#define WEIGHTS_PER_HIDDEN_LAYER (HIDDEN_NEURONS * WEIGHTS_PER_NEURON)
// Number of weights per output layer
#define WEIGHTS_PER_OUTPUT_LAYER (OUTPUTS * WEIGHTS_PER_NEURON)
// Number of weights per layer
#define WEIGHTS_PER_LAYER (WEIGHTS_PER_HIDDEN_LAYER + WEIGHTS_PER_OUTPUT_LAYER)
// Number of weights
#define WEIGHTS (HIDDEN_LAYERS * WEIGHTS_PER_LAYER)
// Number of biases
#define BIASES (HIDDEN_LAYERS + OUTPUTS)
// Number of layers
#define LAYERS (INPUTS + HIDDEN_LAYERS + OUTPUTS)

// Neuron class
class Neuron {
    public:
        // Constructor
        Neuron();
        // Destructor
        ~Neuron();
        // Set the weights
        void setWeights(double *weights);
        // Set the bias
        void setBias(double bias);
        // Get the weights
        double *getWeights();
        // Get the bias
        double getBias();
        // Calculate the output
        double calculateOutput(double *inputs);
    private:
        // Weights
        double *weights;
        // Bias
        double bias;
        // Initialize the weights
        void initializeWeights();
};

Neuron::Neuron() {
    // Allocate memory for weights
    weights = new double[WEIGHTS_PER_NEURON];
    // Initialize weights
    for (int i = 0; i < WEIGHTS_PER_NEURON; i++) {
        weights[i] = 0.0;
    }
    // Initialize bias
    bias = 0.0;
}

Neuron::~Neuron() {
    // Delete weights
    delete[] weights;
}

void Neuron::setWeights(double *weights) {
    // Set the weights
    for (int i = 0; i < WEIGHTS_PER_NEURON; i++) {
        this->weights[i] = weights[i];
    }
}

void Neuron::initializeWeights() {
    // Initialize weights
    for (int i = 0; i < WEIGHTS_PER_NEURON; i++) {
        weights[i] = rand();
    }
}

