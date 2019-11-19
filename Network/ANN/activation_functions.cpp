#include "activation_functions.h"
#include <math.h> 

double activation_functions::tanh_transfer(double x)
{
    return tanh(x);
}

double activation_functions::tanh_transfer_derivative(double x)
{
    return 1 - (x*x);
}

double activation_functions::sigmoid_transfer(double x)
{
    return 1 / (1 + exp(-x));
}

double activation_functions::sigmoid_transfer_derivative(double x)
{
    return  x * (1 - x);
}