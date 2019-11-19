#pragma once
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
