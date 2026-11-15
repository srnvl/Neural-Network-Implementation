// 3. Activation Functions

#include <stdio.h>
#include <math.h>

struct Neuron
{
    double input[100];
    double weight[100];
    double bias;
};

double activation_functions(double z)
{   
    int select;
    double k;
    printf("Enter a number to select an actiavtion function: ");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            printf("Linear activation function:\n");
            return z;
        case 2:
            printf("ReLU activation function:\n");
            return z > 0.0f ? z : 0.0f;
        case 3:
            printf("Sigmoid activation function:\n");
            return 1.0f / (1.0f + exp(-z));
        case 4:
            printf("Step activation function:\n");
            return z < 0.0f ? 0.0f : 1.0f;
        case 5:
            printf("Binary Step activation function:\n");
            return z >= 0.0f ? 1.0f : 0.0f;
        case 6:
            printf("Tanh activatioun function:\n");
            return tanh(z);
        case 7:
            printf("Leaky ReLU activation function:\n");
            printf("Enter a value for the constant: ");
            scanf("%lf", &k);
            return z > 0.0f ? z : k*z;
        default:
            printf("Invalid selection of activation function!");
            return -1.0;            
    }
}

int main(){
    
    struct Neuron neuron;
    int n;
    double z = 0.0;

    printf("Please enter the number of inputs and weights: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf("Enter the value for input %d: ", i);
        scanf("%lf", &neuron.input[i]);
    }

    for(int i = 0; i < n; i++)
    {
        printf("Enter the value for weight %d: ", i);
        scanf("%lf", &neuron.weight[i]);
    }

    printf("Enter a value for bias: ");
    scanf("%lf", &neuron.bias);

    // Calculate weighted sum z
    for(int i = 0; i < n; i++)
    {
        z = z + (neuron.input[i] * neuron.weight[i]);
    }
    z = z + neuron.bias;

    double output = activation_functions(z);  
    printf("Neuron Output: %lf\n", output);

    return 0;
}