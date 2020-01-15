#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include "Network/utils/Event.h"
#include "Network/utils/Logging.h"

class Neuron
{
public:
    virtual Event* update(double dt)
    {
        throw "Update not implemented!";
    }
    virtual void handleEvent(Event* e) {
        throw "HandleEvent not implemented!";
    }
    virtual void resetInput() {
        throw "resetInput not implemented!";
    }
    void initialize() {
        logger = Logging::getInstance();
    }
    long populationID;
    int neuronID;
    Logging* logger;
private:
};

#endif