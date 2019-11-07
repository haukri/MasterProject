#include "./activation_functions.h"
#include <math.h> 

double activation_functions::tanh_transfer(double x)
{
    return tanh(x);
}

double activation_functions::tanh_transfer_derivative(double x)
{
    return 1 - (tanh(x)*tanh(x));
}