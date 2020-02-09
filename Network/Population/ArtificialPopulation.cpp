#include <iostream>
#include "ArtificialPopulation.h"
#include "Network/utils/Event.h"

using namespace std;

ArtificialPopulation::ArtificialPopulation(ANN* a) {
    initialize();
    ann = a;
    annInput = Eigen::MatrixXd(1, ann->getInputSize());
}

ArtificialPopulation::ArtificialPopulation(ANN* a,  Parameters* param) {
    initialize();
    ann = a;
    annInput = Eigen::MatrixXd(1, ann->getInputSize());
}

void ArtificialPopulation::setInput(int neuronIndex, Event* e) {
    annInput(0, neuronIndex) = static_cast<ValueEvent*>(e)->value;
}

void ArtificialPopulation::update() {
    while(current_time < clock->getCurrentTime()) {
        resetOutput();
        annOutput = ann->predict(annInput);
        for(int i = 0; i < numberOfNeurons; i++) {
            output[i] = new ValueEvent(annOutput(0, i));
        }
        current_time += clock->getDt();
    }
}