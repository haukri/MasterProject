#include <iostream>
#include "SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/utils/Event.h"
#include "Network/Neuron/CurrentGenerator.h"

using namespace std;

/*SpikingPopulation::SpikingPopulation(int amount, string modelName) {
    numberOfNeurons = amount;
    initialize();
    if(modelName == "iaf") {
        for(int i = 0; i < amount; i++) {
            neurons.push_back(new LIF());
        }
    }
    else if(modelName == "izhikevich") {
        for(int i = 0; i < amount; i++) {
            neurons.push_back(new Izhikevich((long)this, i));
        }
    }
    else if(modelName == "CurrentGenerator") {
        for(int i = 0; i < amount; i++) {
            neurons.push_back(new CurrentGenerator());
        }
    }
}

SpikingPopulation::SpikingPopulation(int amount, string modelName, Parameters* param) {
    numberOfNeurons = amount;
    initialize();
    if(modelName == "iaf") {
        for(int i = 0; i < amount; i++) {
            neurons.push_back(new LIF(static_cast<LIF_param*>(param)));
        }
    }
    else if(modelName == "izhikevich") {
        for(int i = 0; i < amount; i++) {
            neurons.push_back(new Izhikevich((long)this, i, static_cast<Izhikevich_param*>(param)));
        }
    }
    else if(modelName == "CurrentGenerator") {
        for(int i = 0; i < amount; i++) {
            neurons.push_back(new CurrentGenerator(static_cast<CurrentGenerator_param*>(param)));
        }
    }
    else {
        // TODOS throw exception
    }
}*/

void SpikingPopulation::update() {
    while(current_time < clock->getCurrentTime()) {
        resetOutput();
        for(int i = 0; i < numberOfNeurons; i++) {
            output[i] = neurons[i]->update(clock->getDt());
            if(output[i]->type != EventType::No) {
                logger->logEvent((long)this, i, output[i]->type);
            }
            neurons[i]->resetInput();
        }
        current_time += clock->getDt();
    }
}