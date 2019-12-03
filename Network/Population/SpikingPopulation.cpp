#include <iostream>
#include "SpikingPopulation.h"
#include "Network/Neuron/LIF.h"
#include "Network/Neuron/Izhikevich.h"

using namespace std;

SpikingPopulation::SpikingPopulation(int amount, string modelName) {
    output = vector<double>(amount);
    numberOfNeurons = amount;
    if(modelName == "lif") {
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
    output = vector<double>(amount);
    numberOfNeurons = amount;
    if(modelName == "lif") {
        for(int i = 0; i < amount; i++) {
            neurons.push_back(new LIF(static_cast<LIF_param*>(param)));
        }
    }
    else if(modelName == "izhikevich") {
        for(int i = 0; i < amount; i++) {
            neurons.push_back(new Izhikevich(static_cast<Izhikevich_param*>(param)));
        }
    }
}

void SpikingPopulation::update(vector<double> &input, double dt) {
    for(int i = 0; i < input.size(); i++) {
        output[i] = neurons[i]->update(input[i], dt);
    }
    current_time += dt;
}

double SpikingPopulation::getCurrentTime() {
    return current_time;
}