#pragma once

#include <iostream>
#include <vector>

class Population
{
public:
    virtual void update(std::vector<double> &input)
    {
        std::cout << "Update not implemented!" << std::endl;
    }
    virtual int getNumberOfNeurons() {
        return numberOfNeurons;
    }

    virtual std::vector<double> getOutput() {
        return output;
    }
    std::vector<double> output;
    int numberOfNeurons;
private:

};
