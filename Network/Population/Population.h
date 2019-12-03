#pragma once

#include <iostream>
#include <vector>

class Population
{
public:
    virtual void update(std::vector<double> &input, double dt)
    {
        std::cout << "Update not implemented!" << std::endl;
    }
    virtual int getNumberOfNeurons() {
        return numberOfNeurons;
    }
    int numberOfNeurons;
private:

};
