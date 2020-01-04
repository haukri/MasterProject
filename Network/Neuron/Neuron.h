#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include "Network/utils/Event.h"

class Neuron
{
public:
    virtual Event update(double dt)
    {
        throw "Update not implemented!";
    }
    virtual void handleEvent(SpikeEvent* e) {
        throw "HandleEvent for SpikeEvent not implemented!";
    }
    virtual void handleEvent(CurrentEvent* e) {
        throw "HandleEvent for CurrentEvent not implemented!";
    }
private:
};

#endif