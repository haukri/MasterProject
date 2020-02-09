#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Network/utils/Parameters.h"
#include "Population.h"
#include "Network/ANN/ANN.h"

class ArtificialPopulation : public Population
{
public:
    ArtificialPopulation(ANN* a);
    ArtificialPopulation(ANN* a, Parameters*);
    void update();
    void setInput(int, Event*);

private:
    ANN* ann;
    Eigen::MatrixXd annInput;
    Eigen::MatrixXd annOutput;
};
