#ifndef FILTER_H
#define FILTER_H


#include <vector>
#include "Eigen/Core"
#include "Layer.h"
#include <iostream>
#include "activation_functions.h"
#include "Network/utils/FIR.h"
#include "Network/utils/Clock.h"

using namespace std;

class Filter : public Layer
{
public:
    Filter(int input_size, int output_size, double* learning_rate, string type);

    Eigen::MatrixXd forward(Eigen::MatrixXd input);
    Eigen::MatrixXd backward(Eigen::MatrixXd grad_output) {};
    Eigen::MatrixXd getActivation() {};

    void setWeights(Eigen::MatrixXd) {};
    void setBiases(Eigen::MatrixXd){};

    ~Filter();

private:
    string type;
    FIR filter = FIR();
    Clock* clock;
    Eigen::MatrixXd output;
};

#endif