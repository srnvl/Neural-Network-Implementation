// 1. What is a Neural Network?

#include <stdio.h>
#include <math.h>

struct Neuron{

    double weight1;
    double weight2;
    double bias;   
    int select;
};

double activate(struct Neuron* neuron, double x1, double x2)
{
    double z = (x1 * neuron->weight1) + (x2 * neuron->weight2) + neuron->bias;
    printf("Please select which activation function to use: ");
    scanf("%d", &(neuron->select));

        switch(neuron->select)
        {
            case 1:
                return z > 0.0f ? z : 0.0f;
            case 2:
                return 1.0f / (1.0f + expf(-z));
            default:
                printf("Invalid selection of activation function!");
                return -1;
        }
}

int main()
{
    struct Neuron n;
    n.weight1 = 4.0f;
    n.weight2 = 2.0f;
    n.bias = 2.5f;
    double output = activate(&n, 4.0f, 3.0f);
    printf("Neuron output: %.1f\n", output);
    return 0;
}
