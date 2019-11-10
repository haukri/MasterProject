#ifndef DENSE_H
#define DENSE_H


#include <vector>
#include "../../Eigen/Core"
#include "./Layer.h"
#include <iostream>
#include "./activation_functions.h"

using namespace std;

class Dense : public Layer
{
public:
    Dense(int input_size, int output_size, double learning_rate, string type);

    Eigen::MatrixXd forward(Eigen::MatrixXd input);
    Eigen::MatrixXd backward(Eigen::MatrixXd grad_output);
    Eigen::MatrixXd getActivation();

    ~Dense();

private:
    Eigen::MatrixXd weigths;
    Eigen::MatrixXd biases;
    Eigen::MatrixXd activation;
    Eigen::MatrixXd last_input;
    double learning_rate;
    string type;
};

#endif