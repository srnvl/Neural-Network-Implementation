# Implementation of Neural Networks from Scratch

Implementing neural networks from scratch using C.

This project consists of a series of lessons that go from the fundamentals of neural networks to eventually implementing a neural network from scratch.  

In order to run each lesson, please use:  
> gcc lessonx.c -o lesson  
> ./lesson      

where 'x' is the number of that particular lesson  

## List Of Contents  

### Module 1 - Understanding The Fundamentals

#### Lesson 1 - What Is A Neuron?

- Defined a basic neuron.
- Implemented ReLU and Sigmoid activation functions.

#### Lesson 2 - The Mathematics Of A Neuron

- Implemented calculations using fixed inputs and weights.
- Implemented calculations using variable inputs and weights.
- Implemented the dot product.

#### Lesson 3 - Activation Functions  

- Implemented various activation functions:  
    - Linear 
    - ReLU
    - Sigmoid
    - Step
    - Binary Step
    - Tanh
    - Leaky ReLU

#### Lesson 4 - Building Your First Neuron  
  
- Created a reusable Neuron structure using C structs.  
- Implemented dynamic memory allocation for neuron weights.  
- Added support for configurable activation functions:  
    - Linear
    - ReLU
    - Sigmoid
    - Tanh
    - Leaky ReLU
- Implemented neuron initialization and memory management. 
- Implemented forward propagation to calculate neuron outputs using inputs, weights, and bias.
- Integrated user input to configure neurons dynamically.
- Implemented memory cleanup to prevent memory leaks.

#### Lesson 5 - Building a Neural Network

- Introduced the Layer structure to group multiple neurons into a single layer.  
- Implemented dynamic memory allocation for layers and their individual neurons.
- Implemented layer initialization with configurable neuron counts, input sizes, and activation functions.
- Added functionality to safely configure individual neuron weights and biases.
- Implemented forward propagation for individual neurons.
- Implemented layer forward propagation to calculate the outputs of all neurons within a layer.
- Demonstrated how multiple neurons process the same input vector to produce an output vector.
- Implemented memory management and cleanup for dynamically allocated neurons and layers.
- Tested a layer containing three neurons, each receiving two inputs and using ReLU activation.
