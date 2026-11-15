// Building a Neural Network

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum{
    ReLU,
    Linear,
} ActivationType;

typedef struct{
    double* weights;
    int input_count;
    double bias;
    ActivationType activation;
} Neuron;

double activate(double z, ActivationType type){
    switch(type)
    {
        case ReLU:
            return z > 0.0f? z : 0.0f;
        case Linear:
            return z;
        default:
            return -1;
    }
}

int neuron_init(Neuron *neuron, int input_count, ActivationType activation){
    if(input_count <= 0){
        return 0;
    }
    neuron->weights = malloc(input_count * sizeof(double));

    if(neuron->weights == NULL)
    {
        return 0;
    }
    neuron->input_count = input_count;
    neuron->activation = activation;
    neuron->bias = 0.0;
}

double neuron_set_weight(Neuron *neuron, int index, double value)
{
    if(neuron == NULL || neuron->weights == NULL)
        return 0;
    
    if(index < 0 || index >= neuron->input_count)
        return 0; // Failure

    neuron->weights[index] = value;  
    return 1; // Success
}

double neuron_forward(const Neuron* neuron, const double input[])
{
    double z = 0.0f;
    for(int i = 0; i < neuron->input_count; i++)
    {
        z = z + input[i] * neuron->weights[i];
    }
    z = z + neuron->bias;

    return activate(z, neuron->activation);
}

void neuron_destroy(Neuron * neuron)
{
    free(neuron->weights);
    neuron->weights = NULL;
    neuron->input_count = 0.0;
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
    if (!neuron_init(&neuron, n, ReLU))
    {
        printf("Neuron initialization failed.\n");
        return 1;
    }

    // Read weights using the safe setter function
    for (int i = 0; i < n; i++)
    {
        double temp_weight;
        printf("Enter weight %d: ", i + 1);

        if (scanf("%lf", &temp_weight) != 1)
        {
            printf("Invalid weight.\n");
            neuron_destroy(&neuron);
            return 1;
        }

        if (!neuron_set_weight(&neuron, i, temp_weight))
        {
            printf("Failed to set weight.\n");
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