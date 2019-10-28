#pragma once
#include <vector>
#include "../../Eigen/Dense"
#include "./Layer.h"

using namespace std;

class Dense : public Layer
{
public:
    Dense(int input_size, int output_size, double learning_rate);

    Eigen::MatrixXf forward(Eigen::MatrixXf input);
    Eigen::MatrixXf backward(Eigen::MatrixXf input, Eigen::MatrixXf grad_output);

    ~Dense();

private:
    Eigen::MatrixXf weigths;
    Eigen::MatrixXf biases;
    double learning_rate;
};
