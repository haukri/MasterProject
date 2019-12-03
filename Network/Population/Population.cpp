#include <iostream>
#include "Population.h"
#include "Network/Neuron/LIF.h"

using namespace std;

Population::Population(int amount, string modelName) {
    if(modelName == "lif") {
        for(int i = 0; i < amount; i++) {
            neurons.push_back(new LIF());
        }
    }
}

Population::Population(int amount, string modelName, Parameters* param) {
    if(modelName == "lif") {
        for(int i = 0; i < amount; i++) {
            neurons.push_back(new LIF(static_cast<LIF_param*>(param)));
        }
    }
}