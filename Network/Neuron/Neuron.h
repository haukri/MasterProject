#ifndef NEURON_H
#define NEURON_H

#include <iostream>

class Neuron
{
public:
    virtual void update()
    {
        std::cout << "Update not implemented!" << std::endl;
    }
private:
};

#endif