#ifndef PassThrough_H
#define PassThrough_H

#include <iostream>
#include "Neuron.h"
#include "Network/utils/Parameters.h"
#include <vector>

struct PassThrough_param : Parameters {
};

class PassThrough : public Neuron
{
public:
    PassThrough();
    PassThrough(PassThrough_param*);
    Event* update(double);
    void handleEvent(Event*);
    void resetInput();
    ~PassThrough();
private:
    double dt;
    PassThrough_param* param;
    EventType eventType = EventType::No;
    double weight = 0.0;
    int multiplicity = 1.0;
};

#endif
