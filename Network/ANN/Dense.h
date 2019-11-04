#pragma once
#include <vector>
#include "../../Eigen/Dense"
#include "./Layer.h"
#include <iostream>

using namespace std;

class Dense : public Layer
{
public:
    Dense(int input_size, int output_size, double learning_rate);

    Eigen::MatrixXf forward(Eigen::MatrixXf input);
    Eigen::MatrixXf backward(Eigen::MatrixXf input, Eigen::MatrixXf grad_output);
    Eigen::MatrixXf getActivation();

    ~Dense();

private:
    Eigen::MatrixXf weigths;
    Eigen::MatrixXf biases;
    Eigen::MatrixXf activation;
    double learning_rate;
};
