#include "./Dense.h"

Dense::Dense(int input_size, int output_size, double learning_rate, string ntype) {
    weigths = Eigen::MatrixXd(input_size, output_size);
    for(int i = 0; i < input_size; i++) {
        for(int j = 0; j < output_size; j++) {
            weigths(i, j) = 2;
        }
    }
    cout << "Layer" << endl;
    cout << weigths << endl;
    biases = Eigen::MatrixXd(1, output_size);
    learning_rate = learning_rate;
    type = ntype;
}

Eigen::MatrixXd Dense::forward(Eigen::MatrixXd input) {
    activation = input*weigths + biases;
    if(type == "tanh") {
        activation = activation.unaryExpr(&activation_functions::tanh_transfer);
    }
    return activation;
}

Eigen::MatrixXd Dense::backward(Eigen::MatrixXd input, Eigen::MatrixXd grad_output) {
    Eigen::MatrixXd grad_input = grad_output * weigths.transpose();

    Eigen::MatrixXd grad_weights = input.transpose() * grad_output;
    Eigen::MatrixXd grad_biases = grad_output.rowwise().mean() * input.rows();

    weigths = weigths - learning_rate * grad_weights;
    biases = biases - learning_rate * grad_biases;

    return grad_input;
}

Eigen::MatrixXd Dense::getActivation() {
    return activation;
}

Dense::~Dense() {
    cout << "Object deconstructed!" << endl;
}