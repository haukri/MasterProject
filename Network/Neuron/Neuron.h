#ifndef NEURON_H
#define NEURON_H

#include <iostream>

class Neuron
{
public:
    virtual double update(double input, double dt)
    {
        std::cout << "Update not implemented!" << std::endl;
    }
private:
};

#endif