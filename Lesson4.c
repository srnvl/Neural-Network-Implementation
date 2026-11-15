#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Activation function types
typedef enum
{
    LINEAR,
    RELU,
    SIGMOID,
    TANH_ACT,
    LEAKY_RELU
} ActivationType;

// Neuron structure
typedef struct
{
    double *weights;
    double bias;
    int input_count;
    ActivationType activation;
} Neuron;


// Apply activation function
double activate(double z, ActivationType type)
{
    switch (type)
    {
        case LINEAR:
            return z;

        case RELU:
            return z > 0.0 ? z : 0.0;

        case SIGMOID:
            return 1.0 / (1.0 + exp(-z));

        case TANH_ACT:
            return tanh(z);

        case LEAKY_RELU:
            return z > 0.0 ? z : 0.01 * z;

        default:
            return z;
    }
}

// Initialize neuron
int neuron_init(Neuron *neuron, int input_count, ActivationType activation)
{
    if (input_count <= 0)
        return 0;

    neuron->weights = malloc(input_count * sizeof(double));

    if (neuron->weights == NULL)
        return 0;

    neuron->input_count = input_count;
    neuron->bias = 0.0;
    neuron->activation = activation;

    return 1;
}

// Calculate neuron output
double neuron_forward(const Neuron *neuron, const double inputs[])
{
    double z = 0.0;

    for (int i = 0; i < neuron->input_count; i++)
    {
        z = z + inputs[i] * neuron->weights[i];
    }

    z = z + neuron->bias;

    return activate(z, neuron->activation);
}

// Free allocated memory
void neuron_destroy(Neuron *neuron)
{
    free(neuron->weights);

    neuron->weights = NULL;
    neuron->input_count = 0;
}

int main(void)
{
    Neuron neuron;

    int n;
    double inputs[100];

    printf("Enter the number of inputs: ");

    if (scanf("%d", &n) != 1 || n <= 0 || n > 100)
    {
        printf("Invalid number of inputs.\n");
        return 1;
    }

    // Initialize neuron with ReLU activation
    if (!neuron_init(&neuron, n, RELU))
    {
        printf("Neuron initialization failed.\n");
        return 1;
    }

    // Read weights
    for (int i = 0; i < n; i++)
    {
        printf("Enter weight %d: ", i + 1);

        if (scanf("%lf", &neuron.weights[i]) != 1)
        {
            printf("Invalid weight.\n");
            neuron_destroy(&neuron);
            return 1;
        }
    }

    // Read bias
    printf("Enter bias: ");

    if (scanf("%lf", &neuron.bias) != 1)
    {
        printf("Invalid bias.\n");
        neuron_destroy(&neuron);
        return 1;
    }

    // Read inputs
    for (int i = 0; i < n; i++)
    {
        printf("Enter input %d: ", i + 1);

        if (scanf("%lf", &inputs[i]) != 1)
        {
            printf("Invalid input.\n");
            neuron_destroy(&neuron);
            return 1;
        }
    }

    // Calculate output
    double output = neuron_forward(&neuron, inputs);

    printf("\nNeuron output: %.4f\n", output);

    // Release memory
    neuron_destroy(&neuron);

    return 0;
}