#include "./Dense.h"

Dense::Dense(int input_size, int output_size, double learning_rate) {
    cout << "Constructed" << endl;
    weigths = Eigen::MatrixXf(input_size, output_size);
    biases = Eigen::MatrixXf(1, output_size);
    learning_rate = learning_rate;
}

Eigen::MatrixXf Dense::forward(Eigen::MatrixXf input) {
    cout << input.rows() << " : " << input.cols() << endl;
    cout << weigths.rows() << " : " << weigths.cols() << endl;
    activation = input*weigths + biases;
    return activation;
}

Eigen::MatrixXf Dense::backward(Eigen::MatrixXf input, Eigen::MatrixXf grad_output) {
    Eigen::MatrixXf grad_input = grad_output * weigths.transpose();

    Eigen::MatrixXf grad_weights = input.transpose() * grad_output;
    Eigen::MatrixXf grad_biases = grad_output.rowwise().mean() * input.rows();

    weigths = weigths - learning_rate * grad_weights;
    biases = biases - learning_rate * grad_biases;

    return grad_input;
}

Eigen::MatrixXf Dense::getActivation() {
    return activation;
}

Dense::~Dense() {
    cout << "Object deconstructed!" << endl;
}