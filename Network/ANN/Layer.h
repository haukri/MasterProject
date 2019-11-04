#pragma once
#include "../../Eigen/Dense"
#include <iostream>

class Layer
{
public:

    virtual Eigen::MatrixXf forward(Eigen::MatrixXf input) {
        std::cout << "Forward not implemented!" << std::endl;
        return input;
    }
    
    virtual Eigen::MatrixXf backward(Eigen::MatrixXf input, Eigen::MatrixXf grad_output) {
        std::cout << "Backward not implemented!" << std::endl;
        return input;
    }

private:
};
