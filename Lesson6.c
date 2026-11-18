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

typedef struct {
    Layer *layers;
    int layer_count;
} NeuralNetwork;


// Activation function implementation
double activate(double z, ActivationType type) {
    switch(type) {
        case ReLU:
            return z > 0.0 ? z : 0.0;

        case Linear:
            return z;

        default:
            return z;
    }
}


// Initialize a single neuron
int neuron_init(Neuron *neuron, int input_count, ActivationType activation) {

    if (neuron == NULL || input_count <= 0)
        return 0;

    neuron->weights = NULL;
    neuron->input_count = 0;
    neuron->bias = 0.0;
    neuron->activation = activation;

    neuron->weights = calloc(input_count, sizeof(double));

    if (neuron->weights == NULL)
        return 0;

    neuron->input_count = input_count;
    neuron->activation = activation;
    neuron->bias = 0.0;

    return 1;
}


// Clean up single neuron memory
void neuron_destroy(Neuron *neuron) {

    if (neuron == NULL)
        return;

    free(neuron->weights);

    neuron->weights = NULL;
    neuron->input_count = 0;
}


// Initialize a layer of neurons
int layer_init(Layer *layer, int neuron_count,
               int input_count, ActivationType activation) {

    if (layer == NULL || neuron_count <= 0 || input_count <= 0)
        return 0;

    layer->neurons = NULL;
    layer->neuron_count = 0;
    layer->activation = activation;

    layer->neurons = calloc(neuron_count, sizeof(Neuron));

    if (layer->neurons == NULL)
        return 0;

    layer->neuron_count = neuron_count;
    layer->activation = activation;

    for (int i = 0; i < neuron_count; i++) {

        if (!neuron_init(&layer->neurons[i],
                         input_count,
                         activation)) {

            for (int j = 0; j < i; j++) {
                neuron_destroy(&layer->neurons[j]);
            }

            free(layer->neurons);

            layer->neurons = NULL;
            layer->neuron_count = 0;

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


// Safely set a neuron's bias
int neuron_set_bias(Neuron *neuron, double value) {

    if (neuron == NULL)
        return 0;

    neuron->bias = value;

    return 1;
}


// Compute forward pass for a single neuron
double neuron_forward(const Neuron* neuron, const double input[]) {

    double z = 0.0;

    for (int i = 0; i < neuron->input_count; i++) {
        z += input[i] * neuron->weights[i];
    }

    z += neuron->bias;

    return activate(z, neuron->activation);
}


// Compute forward pass for an entire layer
void layer_forward(const Layer* layer,
                   const double input[],
                   double output[]) {

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


// Initialize an entire neural network
int network_init(NeuralNetwork* neuralnetwork,
                 const int architecture[],
                 int layer_count,
                 ActivationType activation) {

    if (neuralnetwork == NULL ||
        architecture == NULL ||
        layer_count <= 0)
        return 0;

    neuralnetwork->layers = NULL;
    neuralnetwork->layer_count = 0;

    // Validate architecture
    for (int i = 0; i <= layer_count; i++) {

        if (architecture[i] <= 0)
            return 0;
    }

    // Allocate memory for layers
    neuralnetwork->layers = calloc(layer_count, sizeof(Layer));

    if (neuralnetwork->layers == NULL)
        return 0;

    neuralnetwork->layer_count = layer_count;

    // Initialize each layer
    for (int i = 0; i < layer_count; i++) {

        if (!layer_init(&neuralnetwork->layers[i],
                        architecture[i + 1],
                        architecture[i],
                        activation)) {

            for (int j = 0; j < i; j++) {
                layer_destroy(&neuralnetwork->layers[j]);
            }

            free(neuralnetwork->layers);

            neuralnetwork->layers = NULL;
            neuralnetwork->layer_count = 0;

            return 0;
        }
    }

    return 1;
}


// Perform forward propagation across the entire network
int network_forward(const NeuralNetwork* neuralnetwork,
                    const double input[],
                    double output[]) {

    if (neuralnetwork == NULL ||
        neuralnetwork->layers == NULL ||
        input == NULL ||
        output == NULL)
        return 0;

    const double *current_input = input;

    double *buffer1 = NULL;
    double *buffer2 = NULL;

    // Find the largest layer size for temporary storage
    int max_neurons = 0;

    for (int i = 0; i < neuralnetwork->layer_count; i++) {

        if (neuralnetwork->layers[i].neuron_count > max_neurons)
            max_neurons = neuralnetwork->layers[i].neuron_count;
    }

    buffer1 = malloc(max_neurons * sizeof(double));
    buffer2 = malloc(max_neurons * sizeof(double));

    if (buffer1 == NULL || buffer2 == NULL) {

        free(buffer1);
        free(buffer2);

        return 0;
    }

    double *current_output = buffer1;
    double *next_output = buffer2;

    // Process every layer sequentially
    for (int i = 0; i < neuralnetwork->layer_count; i++) {

        Layer *layer = &neuralnetwork->layers[i];

        // The final layer writes directly into the output array
        if (i == neuralnetwork->layer_count - 1) {

            layer_forward(layer, current_input, output);
        }
        else {

            layer_forward(layer, current_input, current_output);

            current_input = current_output;

            // Swap temporary buffers
            double *temp = current_output;
            current_output = next_output;
            next_output = temp;
        }
    }

    free(buffer1);
    free(buffer2);

    return 1;
}


// Destroy entire neural network
void network_destroy(NeuralNetwork* neuralnetwork) {

    if (neuralnetwork == NULL)
        return;

    if (neuralnetwork->layers != NULL) {

        for (int i = 0; i < neuralnetwork->layer_count; i++) {
            layer_destroy(&neuralnetwork->layers[i]);
        }

        free(neuralnetwork->layers);
    }

    neuralnetwork->layers = NULL;
    neuralnetwork->layer_count = 0;
}


// Main
int main(void) {

    // Architecture: 2 inputs -> 3 neurons -> 4 neurons -> 1 output
    int architecture[] = {2, 3, 4, 1};

    int layer_count = 3;

    NeuralNetwork network;

    // Initialize network
    if (!network_init(&network,
                      architecture,
                      layer_count,
                      ReLU)) {

        printf("Network initialization failed.\n");
        return 1;
    }

    // Define input vector
    double inputs[] = {2.0, 3.0};

    // Configure weights and biases for the first layer

    neuron_set_weight(&network.layers[0].neurons[0], 0, 0.5);
    neuron_set_weight(&network.layers[0].neurons[0], 1, 0.8);
    neuron_set_bias(&network.layers[0].neurons[0], 0.1);

    neuron_set_weight(&network.layers[0].neurons[1], 0, 0.2);
    neuron_set_weight(&network.layers[0].neurons[1], 1, 0.4);
    neuron_set_bias(&network.layers[0].neurons[1], 0.2);

    neuron_set_weight(&network.layers[0].neurons[2], 0, -0.5);
    neuron_set_weight(&network.layers[0].neurons[2], 1, 0.3);
    neuron_set_bias(&network.layers[0].neurons[2], 0.5);

    // Configure remaining weights and biases
    // Zero-initialized weights and biases are retained
    // for the other layers in this demonstration.

    // Allocate final output
    double output[1];

    // Perform network forward propagation
    if (!network_forward(&network, inputs, output)) {

        printf("Forward propagation failed.\n");

        network_destroy(&network);
        return 1;
    }

    // Print results
    printf("--- Neural Network Test ---\n");

    printf("Input Vector: [%.1f, %.1f]\n",
           inputs[0], inputs[1]);

    printf("Network Output:\n");

    printf("[ %.4f ]\n", output[0]);

    // Clean up
    network_destroy(&network);

    return 0;
}