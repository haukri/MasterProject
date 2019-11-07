#include <iostream>
#include "./ANN.h"

using namespace std;

ANN::ANN()
{

}

void ANN::addLayer(int size, string type) {
    layers.push_back(new Dense(inputSize, size, learning_rate, type));
    inputSize = size;
}

void ANN::setInputSize(int size) {
    inputSize = size;
}

void ANN::setLearningRate(int learning_rate) {
    learning_rate = learning_rate;
}

void ANN::build() {
    for(int outputSize : layerSizes) {
        // layers.push_back(new Dense(inputSize, outputSize, learning_rate));
        // inputSize = outputSize;
    }
}

Eigen::MatrixXd ANN::predict(Eigen::MatrixXd input) {
    for(auto layer : layers) {
        input = layer->forward(input);
    }
    return input;
}

ANN::~ANN()
{
    
}