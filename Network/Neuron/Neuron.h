#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include "Network/utils/Event.h"

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
private:
};

#endif