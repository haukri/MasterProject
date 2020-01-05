#ifndef CurrentGenerator_H
#define CurrentGenerator_H

#include <iostream>
#include "Neuron.h"
#include "Network/utils/Parameters.h"

struct CurrentGenerator_param : Parameters {
    double I = 100.0;
};

class CurrentGenerator : public Neuron
{
public:
    CurrentGenerator();
    CurrentGenerator(CurrentGenerator_param*);
    Event* update(double);
    void handleEvent(Event*);
    void resetInput();
    ~CurrentGenerator();
private:
    double dt;
    CurrentGenerator_param* param;
};



#endif
