#include <iostream>
#include "./ANN.h"
#include "./Dense.h"

using namespace std;

ANN::ANN()
{

}

void ANN::addLayer(int size) {
    layerSizes.push_back(size);
}

void ANN::setInputSize(int size) {
    inputSize = size;
}

void ANN::setOutputSize(int size) {
    outputSize = size;
}

void ANN::setLearningRate(int learning_rate) {
    learning_rate = learning_rate;
}

void ANN::build() {
    for(int outputSize : layerSizes) {
        layers.push_back(Dense(inputSize, outputSize, learning_rate));
        inputSize = outputSize;
    }
}

ANN::~ANN()
{
    
}