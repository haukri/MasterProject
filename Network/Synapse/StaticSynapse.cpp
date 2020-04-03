#include <iostream>
#include "StaticSynapse.h"

using namespace std;

StaticSynapse::StaticSynapse(Population* n_from, Population* n_to) : 
    param(new StaticSynapse_param)
{
    initialize(n_from, n_to);
}

StaticSynapse::StaticSynapse(Population* n_from, Population* n_to, StaticSynapse_param* param) : 
    param(param)
{
    initialize(n_from, n_to);
}

void StaticSynapse::initialize(Population* n_from, Population* n_to) {
    inputSize = n_from->getNumberOfNeurons();
    outputSize = n_to->getNumberOfNeurons();
    weights = Eigen::MatrixXd::Zero(inputSize, outputSize);
    from_population = n_from;
    to_population = n_to;
}

void StaticSynapse::update() {
    for(int i = 0; i < outputSize; i++) {
        for(int j = 0; j < inputSize; j++) {
            from_population->output[j]->setWeight(weights(j, i));
            to_population->setInput(i, from_population->output[j]);
        }
    }
}

void StaticSynapse::setWeight(int from_neuron, int to_neuron, double n_weight) {
    weights(from_neuron, to_neuron) = n_weight;
}