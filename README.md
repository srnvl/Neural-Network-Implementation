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

#### Lesson 5 - 