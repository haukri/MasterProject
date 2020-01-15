#pragma once

#include <iostream>
#include <vector>
#include "Network/utils/Event.h"
#include "Network/utils/Clock.h"
#include <string>
#include "Network/Neuron/Neuron.h"
#include "Network/utils/Logging.h"

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

    virtual std::vector<Event*> getEvents() {
        return output;
    }

    void initialize() {
        output = std::vector<Event*>(numberOfNeurons, NULL);
        clock = Clock::getInstance();
        logger = Logging::getInstance();
    }

    void resetOutput() {
        for(int i = 0; i < output.size(); i++) {
            if(output[i]) {
                delete output[i];
                output[i] = NULL;
            }
        }
    }

    void setInput(int neuronIndex, Event* e) {
        if(neuronIndex < 0 || neuronIndex >= neurons.size()) {
            throw "Index of input neuron out of range!";
        }
        neurons[neuronIndex]->handleEvent(e);

    }

    std::vector<Event*> output;
    int numberOfNeurons;
    std::vector<Neuron*> neurons;
    double current_time;
    Clock* clock;
    Logging* logger;
private:

};
