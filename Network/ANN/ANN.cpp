#include <iostream>
#include "ANN.h"
#include <assert.h>
#include "Filter.h"

using namespace std;

ANN::ANN()
{

}

void ANN::addLayer(int size, string type) {
    outputSize = size;
    if(type == "lowpass" || type == "highpass" || type == "passband") {
        layers.push_back(new Filter(inputSize, size, &learning_rate, type));
    }
    else {
        layers.push_back(new Dense(inputSize, size, &learning_rate, type));
    }
}

void ANN::setInputSize(int size) {
    inputSize = size;
}

void ANN::setLearningRate(double nlearning_rate) {
    learning_rate = nlearning_rate;
}

int ANN::getInputSize() {
    return inputSize;
}

int ANN::getOutputSize() {
    return outputSize;
}

void ANN::fit(Eigen::MatrixXd X, Eigen::MatrixXd y) {
    // Calculate feed forward for X
    Eigen::MatrixXd predicted = predict(X);
    // Calculate error for output
    Eigen::MatrixXd error = y - predicted;
    error.transposeInPlace();
    // Backpropagate error
    for(int i = layers.size()-1; i > 0; i--) {
        error = layers[i]->backward(error);
    }
}

Eigen::MatrixXd ANN::predict(Eigen::MatrixXd input) {
    for(auto layer : layers) {
        input = layer->forward(input);
    }
    return input;
}

Layer* ANN::getLayer(int index) {
    return layers[index];
}

ANN::~ANN()
{
    
}