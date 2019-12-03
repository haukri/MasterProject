#include <iostream>
#include "StaticSynapse.h"

using namespace std;

StaticSynapse::StaticSynapse(Population* n_from, Population* n_to) : 
    param(new StaticSynapse_param), 
    from_population(n_from), 
    to_population(n_to) 
{
    inputSize = n_from->getNumberOfNeurons();
    outputSize = n_to->getNumberOfNeurons();
    weights = Eigen::MatrixXd::Constant(inputSize, outputSize, 1.0);
    output = vector<double>(outputSize, 0.0);
}

StaticSynapse::StaticSynapse(Population* n_from, Population* n_to, StaticSynapse_param* param) : 
    param(param), 
    from_population(n_from), 
    to_population(n_to)
{
    inputSize = n_from->getNumberOfNeurons();
    outputSize = n_to->getNumberOfNeurons();
    weights = Eigen::MatrixXd::Constant(inputSize, outputSize, 1.0);
    output = vector<double>(outputSize, 0.0);
}

void StaticSynapse::update(double dt) {
    output = vector<double>(outputSize, 0.0);
    for(int i = 0; i < outputSize; i++) {
        for(int j = 0; j < inputSize; j++) {
            output[i] += weights(j, i);
        }
    }
}