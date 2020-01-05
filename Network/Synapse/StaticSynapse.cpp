#include <iostream>
#include "StaticSynapse.h"

using namespace std;

StaticSynapse::StaticSynapse(Population* n_from, Population* n_to) : 
    param(new StaticSynapse_param)
{
    inputSize = n_from->getNumberOfNeurons();
    outputSize = n_to->getNumberOfNeurons();
    weights = Eigen::MatrixXd::Constant(inputSize, outputSize, 1.0);
    from_population = n_from;
    to_population = n_to;
}

StaticSynapse::StaticSynapse(Population* n_from, Population* n_to, StaticSynapse_param* param) : 
    param(param)
{
    inputSize = n_from->getNumberOfNeurons();
    outputSize = n_to->getNumberOfNeurons();
    weights = Eigen::MatrixXd::Constant(inputSize, outputSize, 1.0);
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