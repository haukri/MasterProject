#include "./Dense.h"

Dense::Dense(int input_size, int output_size, double learning_rate) {
    weigths = Eigen::MatrixXf(input_size, output_size);
    biases = Eigen::MatrixXf(input_size, 1);
    learning_rate = learning_rate;
}

Eigen::MatrixXf Dense::forward(Eigen::MatrixXf input) {
    return input*weigths + biases;
}

Dense::~Dense() {
    
}