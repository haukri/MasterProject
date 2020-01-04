#include <iostream>
#include "SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Neuron/Izhikevich.h"
#include "Network/utils/Event.h"

using namespace std;

SpikingPopulation::SpikingPopulation(int amount, string modelName) {
    output = vector<Event>(amount, NoEvent());
    numberOfNeurons = amount;
    clock = Clock::getInstance();
    if(modelName == "iaf") {
        for(int i = 0; i < amount; i++) {
            neurons.push_back(new LIF());
        }
    }
    else if(modelName == "izhikevich") {
        for(int i = 0; i < amount; i++) {
            neurons.push_back(new Izhikevich());
        }
    }
}

SpikingPopulation::SpikingPopulation(int amount, string modelName, Parameters* param) {
    output = vector<Event>(amount, NoEvent());
    numberOfNeurons = amount;
    clock = Clock::getInstance();
    if(modelName == "iaf") {
        for(int i = 0; i < amount; i++) {
            neurons.push_back(new LIF(static_cast<LIF_param*>(param)));
        }
    }
    else if(modelName == "izhikevich") {
        for(int i = 0; i < amount; i++) {
            neurons.push_back(new Izhikevich(static_cast<Izhikevich_param*>(param)));
        }
    }
    else {
        // throw exception
    }
}

void SpikingPopulation::update() {
    while(current_time < clock->getCurrentTime()) {
        for(int i = 0; i < input.size(); i++) {
            // output[i] = neurons[i]->update(input[i], clock->getDt());
        }
        current_time += clock->getDt();
    }
}