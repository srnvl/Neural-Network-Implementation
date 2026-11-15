// The Mathematics of a Neuron

#include <stdio.h>
#include <math.h>

double dot_product(const double inputs[], const double weights[], int n)
{
    double sum = 0.0;
    for(int i = 0; i < n; i++)
    {
        sum = sum + inputs[i] * weights[i];
    }
    return sum;
}

int main()
{
    // Step 1 : Calculation for fixed input & weight
    /*
    double weight1 = 0.5, weight2 = 0.8, input1 = 2, input2 = 3, bias = 0.1;
    double z = (input1 * weight1) + (input2 * weight2) + bias;
    printf("Weighted sum: %f\n", z);
    */

    // Step 2: Calculation for variable input & weight 

    double inputs[100];
    double weights[100]; 
    double bias;
    // double sum = 0.0;
    // double z[100];

    int n;

    printf("Enter the no. of inputs and weights: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf("Enter the value for input %d: ", i);
        scanf("%lf", &inputs[i]);
    }

    for(int i = 0; i < n; i++)
    {
        printf("Enter the value for weight %d: ", i);
        scanf("%lf", &weights[i]);
    }

    printf("Type the value of bias: ");
    scanf("%lf", &bias);

    /*

    for(int i = 0; i < n; i++)
    {
        z[i] = inputs[i] * weights[i];
        sum += z[i];
    }

    double weighted_output = sum + bias;
    printf("Weighted output: %lf\n", weighted_output);

    */

    // Step 3: Dot product

    double sum = dot_product(inputs, weights, n);
    double weighted_output = sum + bias;
    printf("Weighted output: %lf\n", weighted_output);

    return 0;
}