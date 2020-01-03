#include <iostream>
#include "SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Neuron/Izhikevich.h"

using namespace std;

SpikingPopulation::SpikingPopulation(int amount, string modelName) {
    output = vector<double>(amount, 0.0);
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
    output = vector<double>(amount, 0.0);
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

void SpikingPopulation::update(vector<double> &input) {
    while(current_time < clock->getCurrentTime()) {
        for(int i = 0; i < input.size(); i++) {
            output[i] = neurons[i]->update(input[i], clock->getDt());
        }
        current_time += clock->getDt();
    }
}