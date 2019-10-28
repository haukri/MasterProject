#pragma once
#include "../../Eigen/Dense"

class Layer
{
public:
    Layer() {

    }

    Eigen::MatrixXf forward(Eigen::MatrixXf input) {

    }
    
    Eigen::MatrixXf backward(Eigen::MatrixXf input, Eigen::MatrixXf grad_output) {

    }

    ~Layer() {

    }

private:
};
