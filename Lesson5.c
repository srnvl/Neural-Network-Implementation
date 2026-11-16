// Building a Neural Network - Layer Test

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {
    ReLU,
    Linear,
} ActivationType;

typedef struct {
    double* weights;
    int input_count;
    double bias;
    ActivationType activation;
} Neuron;

typedef struct {
    Neuron *neurons;
    int neuron_count;
    ActivationType activation;
} Layer;

// typedef struct {
//     Layer *layers;
//     int layer_count;
// } NeuralNetwork;

// Activation function implementation
double activate(double z, ActivationType type) {
    switch(type) {
        case ReLU:
            return z > 0.0f ? z : 0.0f;
        case Linear:
            return z;
        default:
            return z;
    }
}

// Initialize a single neuron
int neuron_init(Neuron *neuron, int input_count, ActivationType activation) {
    if (input_count <= 0) {
        return 0;
    }
    neuron->weights = malloc(input_count * sizeof(double));
    if (neuron->weights == NULL) {
        return 0;
    }
    neuron->input_count = input_count;
    neuron->activation = activation;
    neuron->bias = 0.0;

    return 1;
}

// Clean up single neuron memory
void neuron_destroy(Neuron *neuron) {
    if (neuron == NULL) return;
    free(neuron->weights);
    neuron->weights = NULL;
    neuron->input_count = 0;
}

// Initialize a layer of neurons
int layer_init(Layer *layer, int neuron_count, int input_count, ActivationType activation) {
    if (neuron_count <= 0 || input_count <= 0) {
        return 0;
    }

    layer->neurons = malloc(neuron_count * sizeof(Neuron));
    if (layer->neurons == NULL) {
        return 0; 
    }

    layer->neuron_count = neuron_count;
    layer->activation = activation;

    // Initialize every individual neuron inside the layer
    for (int i = 0; i < neuron_count; i++) {
        if (!neuron_init(&layer->neurons[i], input_count, activation)) {
            // Clean up already initialized neurons if one fails
            for (int j = 0; j < i; j++) {
                neuron_destroy(&layer->neurons[j]);
            }
            free(layer->neurons);
            layer->neurons = NULL;
            return 0;
        }
    }

    return 1;
}

// Safely set a weight on a specific neuron
int neuron_set_weight(Neuron *neuron, int index, double value) {
    if (neuron == NULL || neuron->weights == NULL)
        return 0;
    
    if (index < 0 || index >= neuron->input_count)
        return 0;

    neuron->weights[index] = value;  
    return 1;
}

// Compute forward pass for a single neuron
double neuron_forward(const Neuron* neuron, const double input[]) {
    double z = 0.0f;
    for (int i = 0; i < neuron->input_count; i++) {
        z = z + input[i] * neuron->weights[i];
    }
    z = z + neuron->bias;

    return activate(z, neuron->activation);
}

// Compute forward pass for an entire layer
void layer_forward(const Layer* layer, const double input[], double output[]) {
    for (int i = 0; i < layer->neuron_count; i++) {
        output[i] = neuron_forward(&layer->neurons[i], input);
    }
}

// Clean up entire layer memory
void layer_destroy(Layer *layer) {
    if (layer == NULL || layer->neurons == NULL)
        return;

    for (int i = 0; i < layer->neuron_count; i++) {
        neuron_destroy(&layer->neurons[i]);
    }

    free(layer->neurons);
    layer->neurons = NULL;
    layer->neuron_count = 0;
}

int main(void) {
    int input_count = 2;
    int neuron_count = 3;

    Layer layer;

    // 1. Initialize a Layer with 3 neurons, each taking 2 inputs, using ReLU activation
    if (!layer_init(&layer, neuron_count, input_count, ReLU)) {
        printf("Layer initialization failed.\n");
        return 1;
    }

    // 2. Define the input vector X = [2.0, 3.0]
    double inputs[2] = {2.0, 3.0};

    // 3. Configure weights and biases matching our structural example:
    // Neuron 1: weights = [0.5, 0.8], bias = 0.1
    neuron_set_weight(&layer.neurons[0], 0, 0.5);
    neuron_set_weight(&layer.neurons[0], 1, 0.8);
    layer.neurons[0].bias = 0.1;

    // Neuron 2: weights = [0.2, 0.4], bias = 0.2
    neuron_set_weight(&layer.neurons[1], 0, 0.2);
    neuron_set_weight(&layer.neurons[1], 1, 0.4);
    layer.neurons[1].bias = 0.2;

    // Neuron 3: weights = [-0.5, 0.3], bias = 0.5
    neuron_set_weight(&layer.neurons[2], 0, -0.5);
    neuron_set_weight(&layer.neurons[2], 1, 0.3);
    layer.neurons[2].bias = 0.5;

    // 4. Allocate output vector storage for the layer
    double *output = malloc(neuron_count * sizeof(double));
    if (output == NULL) {
        printf("Output allocation failed.\n");
        layer_destroy(&layer);
        return 1;
    }

    // 5. Perform Layer Forward Pass
    layer_forward(&layer, inputs, output);

    // 6. Print Results
    printf("--- Neural Network Layer Test ---\n");
    printf("Input Vector X: [%.1f, %.1f]\n", inputs[0], inputs[1]);
    printf("\nLayer Output Vector A:\n[");
    for (int i = 0; i < neuron_count; i++) {
        printf(" %.1f", output[i]);
        if (i < neuron_count - 1) printf(",");
    }
    printf(" ]\n");

    // 7. Clean up allocated memory
    free(output);
    layer_destroy(&layer);

    return 0;
}