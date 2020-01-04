#pragma once

#include <iostream>
#include <vector>
#include "Network/utils/Event.h"

class Population
{
public:
    virtual void update()
    {
        std::cout << "Update not implemented!" << std::endl;
    }
    virtual int getNumberOfNeurons() {
        return numberOfNeurons;
    }

    virtual std::vector<Event> getEvents() {
        return output;
    }

    std::vector<Event> input;
    std::vector<Event> output;
    int numberOfNeurons;
private:

};
