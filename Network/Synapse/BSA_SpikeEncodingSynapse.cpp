#include <iostream>
#include "BSA_SpikeEncodingSynapse.h"

using namespace std;

BSA_SpikeEncodingSynapse::BSA_SpikeEncodingSynapse(Population* n_from, Population* n_to) : 
    param(new BSA_SpikeEncodingSynapse_param)
{
    initialize(n_from, n_to);
}

BSA_SpikeEncodingSynapse::BSA_SpikeEncodingSynapse(Population* n_from, Population* n_to, BSA_SpikeEncodingSynapse_param* param) : 
    param(param)
{
    initialize(n_from, n_to);
}

void BSA_SpikeEncodingSynapse::initialize(Population* n_from, Population* n_to) {
    inputSize = n_from->getNumberOfNeurons();
    outputSize = n_to->getNumberOfNeurons();
    if(inputSize != outputSize) {
        cout << "Number of input neurons not equal to number of output neurons" << endl;
        throw "Number of input neurons not equal to number of output neurons";
    }
    from_population = n_from;
    to_population = n_to;
    clock = Clock::getInstance();
    logger = Logging::getInstance();
    for(int i = 0; i < inputSize; i++) {
        output.push_back(new NoEvent());
        input.assign(inputSize, deque<double>(0));
    }
    filter = vector<double>{0.05942473828591342,0.07318223830709897,0.11232230333947553,0.17484795255681723,0.25675440297792484,0.3523237031416342,0.454573094246691,0.5558198517560227,0.6483143637949771,0.724886509451,0.7795486730754763,0.8080021690669681,0.8080021690669681,0.7795486730754763,0.724886509451,0.6483143637949771,0.5558198517560227,0.45457309424669107,0.3523237031416343,0.256754402977925,0.17484795255681737,0.11232230333947553,0.07318223830709897,0.05942473828591342};
    for(int i = 0; i < param->filter_length; i++) {
        // TODO add
        // filter.push_back(0.5);
    }
}

void BSA_SpikeEncodingSynapse::resetOutput() {
    for(int i = 0; i < output.size(); i++) {
        if(output[i]) {
            delete output[i];
            output[i] = NULL;
        }
    }
}

void BSA_SpikeEncodingSynapse::update() {
    double currentTime = clock->getCurrentTime();
    resetOutput();
    for(int i = 0; i < inputSize; i++) {
        if(from_population->output[i]->type == EventType::Value) {
            input[i].push_back(static_cast<ValueEvent*>(from_population->output[i])->value);
            if(input[i].size() > param->filter_length) {
                input[i].pop_front();
            }
            double error1 = 0;
            double error2 = 0;
            if(input[i].size() >= param->filter_length) {
                // Ben's Spiker Algorithm
                for(int j = 0; j < param->filter_length; j++) {
                    error1 += abs(input[i][j] - filter[j]);
                    error2 += abs(input[i][j]);
                }
                if(error1 <= (error2 + param->threshold)) {
                    output[i] = new SpikeEvent();
                    for(int j = 0; j < param->filter_length; j++) {
                        input[i][j] -= filter[j];
                    }
                }
                else {
                    output[i] = new NoEvent();
                }
            }
            else {
                output[i] = new NoEvent();
            }
            output[i]->setWeight(10.0);
            to_population->setInput(i, output[i]);
            logger->logEvent(456, 0, output[i]->type);
        }
    }
}