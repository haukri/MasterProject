#include <iostream>
#include "ReceptiveFieldEncodingSynapse.h"
#include <math.h>
#include "Network/utils/helperFunctions.h"

using namespace std;

ReceptiveFieldEncodingSynapse::ReceptiveFieldEncodingSynapse(Population* n_from, Population* n_to) : 
    param(new ReceptiveFieldEncodingSynapse_param)
{
    initialize(n_from, n_to);
}

ReceptiveFieldEncodingSynapse::ReceptiveFieldEncodingSynapse(Population* n_from, Population* n_to, ReceptiveFieldEncodingSynapse_param* param) : 
    param(param)
{
    initialize(n_from, n_to);
}

void ReceptiveFieldEncodingSynapse::initialize(Population* n_from, Population* n_to) {
    inputSize = n_from->getNumberOfNeurons();
    outputSize = n_to->getNumberOfNeurons();
    if(inputSize != 1) {
        cout << "There can only be one input neuron" << endl;
        throw "There can only be one input neuron";
    }
    from_population = n_from;
    to_population = n_to;
    clock = Clock::getInstance();
    logger = Logging::getInstance();
    spikeTimes = Eigen::VectorXd(param->number_of_neurons);
    spikeTimes.setConstant(-1);
    currentWindow = param->window_length_s;
    gaussianMax = gaussian(0, param->input_min);
    for(int i = 0; i < param->number_of_neurons; i++) {
        output.push_back(new NoEvent());
    }
}

void ReceptiveFieldEncodingSynapse::resetOutput() {
    for(int i = 0; i < output.size(); i++) {
        if(output[i]) {
            delete output[i];
            output[i] = NULL;
        }
    }
}

double ReceptiveFieldEncodingSynapse::gaussian(int index, double value) {
    double center = param->input_min + ((2*index+1-1)/2)*((param->input_max-param->input_min)/(param->number_of_neurons-1));
    double variance = 1/param->beta*((param->input_max-param->input_min)/(param->number_of_neurons-1));
    double gauss = 1 / variance * sqrt(2*M_PI) * exp(-0.5 * pow((value - center) / variance, 2));
    return gauss;
}

void ReceptiveFieldEncodingSynapse::update() {
    resetOutput();
    for(int j = 0; j < spikeTimes.size(); j++) {
        if(spikeTimes(j) <= clock->getCurrentTime() && spikeTimes(j) > -1) {
            output[j] = new SpikeEvent();
            output[j]->setWeight(1300.0);
            spikeTimes(j) = -1;
        }
        else {
            output[j] = new NoEvent();
        }
        to_population->setInput(j, output[j]);
        // logger->logEvent((long)this, 0, output[j]->type);
    }
    if(currentWindow <= clock->getCurrentTime()) {
        for(int j = 0; j < spikeTimes.size(); j++) {
            double receptiveFieldValue = gaussian(j, static_cast<ValueEvent*>(from_population->output[0])->value) / gaussianMax;
            double scaledValue = 0.1 + receptiveFieldValue * 0.8;
            double vs = scaledValue * param->window_length_s;
            spikeTimes(j) = currentWindow + param->window_length_s - helperFunctions::clamp(vs, 0*param->window_length_s, param->window_length_s*0.9);
        }
        currentWindow += param->window_length_s;
    }
}