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
    inputSize = n_from->getNumberOfOutputNeurons();
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
        input.assign(inputSize, deque<double>(param->filter_length, 0));
    }
    
    if(param->window == HAMMING) {
        for(int i = 0; i < param->filter_length; i++) {
            filter.push_back((0.54 - 0.46 * cos(6.283185307179586*i/(param->filter_length-1))) * param->scale);
        }
    }
    else if(param->window == TRIANGLE) {
        int middle = ceil(param->filter_length/2.0);
        int len = param->filter_length;
        bool isEven = len % 2 == 0;
        for(int i = 1; i <= middle; i++) {
            filter.push_back((i) / (double)middle * param->scale);
        }
        if(isEven) {
            filter.push_back(filter.back());
        }
        for(int i = middle; i > 1; i--) {
            filter.push_back((i-1) / (double)middle * param->scale);
        }
    }
    if(filter.size() != param->filter_length) {
        cout << "BSA_SpikeEncodingSynapse: filter length does not matched the generated filter" << endl;
    }

    // filter = vector<double>{0.05942473828591342,0.07318223830709897,0.11232230333947553,0.17484795255681723,0.25675440297792484,0.3523237031416342,0.454573094246691,0.5558198517560227,0.6483143637949771,0.724886509451,0.7795486730754763,0.8080021690669681,0.8080021690669681,0.7795486730754763,0.724886509451,0.6483143637949771,0.5558198517560227,0.45457309424669107,0.3523237031416343,0.256754402977925,0.17484795255681737,0.11232230333947553,0.07318223830709897,0.05942473828591342};
    // filter = vector<double>{0.0,0.030303030303030304,0.06060606060606061,0.0909090909090909,0.12121212121212122,0.15151515151515152,0.1818181818181818,0.21212121212121213,0.24242424242424243,0.27272727272727276,0.30303030303030304,0.27272727272727276,0.24242424242424243,0.21212121212121213,0.1818181818181818,0.15151515151515152,0.12121212121212122,0.0909090909090909,0.06060606060606061,0.030303030303030304,0.0};
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
            input[i].pop_front();
            double error1 = 0;
            double error2 = 0;
            // Ben's Spiker Algorithm
            for(int j = 0; j < param->filter_length; j++) {
                error1 += abs(input[i][j] - filter[j]);
                error2 += abs(input[i][j]);
            }
            if(error1 <= (error2 - param->threshold)) {
                output[i] = new SpikeEvent();
                for(int j = 0; j < param->filter_length; j++) {
                    input[i][j] -= filter[j];
                }
            }
            else {
                output[i] = new NoEvent();
            }
            to_population->setInput(i, output[i]);
            logger->logEvent((long)this, i, output[i]->type);
        }
    }
}