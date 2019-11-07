#ifndef LAYER_H
#define LAYER_H

#include "../../Eigen/Dense"
#include <iostream>

class Layer
{
public:

    virtual Eigen::MatrixXd forward(Eigen::MatrixXd input) {
        std::cout << "Forward not implemented!" << std::endl;
        return input;
    }
    
    virtual Eigen::MatrixXd backward(Eigen::MatrixXd input, Eigen::MatrixXd grad_output) {
        std::cout << "Backward not implemented!" << std::endl;
        return input;
    }

private:
};

#endif