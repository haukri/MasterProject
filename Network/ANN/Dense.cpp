#include "./Dense.h"
#include <random>
#include <chrono>

Dense::Dense(int input_size, int output_size, double nlearning_rate, string ntype) {
    weigths = Eigen::MatrixXd(input_size, output_size);
    /*for(int i = 0; i < input_size; i++) {
        for(int j = 0; j < output_size; j++) {
            weigths(i, j) = 2;
        }
    }
    cout << "Layer" << endl;
    cout << weigths << endl;*/
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::normal_distribution<double> distribution(0.0,1.0);
    for(int i = 0; i < weigths.rows(); i++) {
        for(int j = 0; j < weigths.cols(); j++) {
            weigths(i,j) = distribution(generator);
        }
    }

    biases = Eigen::MatrixXd(1, output_size);
    for(int i = 0; i < biases.cols(); i++) {
        biases(0,i) = distribution(generator);
    }
    learning_rate = nlearning_rate;
    type = ntype;
}

Eigen::MatrixXd Dense::forward(Eigen::MatrixXd input) {
    activation = input*weigths + biases.replicate(input.rows(),1);;
    if(type == "tanh") {
        activation = activation.unaryExpr(&activation_functions::tanh_transfer);
    }
    else if(type == "sigmoid") {
        activation = activation.unaryExpr(&activation_functions::sigmoid_transfer);
    }
    last_input = input;
    return activation;
}

Eigen::MatrixXd Dense::backward(Eigen::MatrixXd grad_output) {
    Eigen::MatrixXd delta;
    if(type == "tanh") {
        delta = grad_output.cwiseProduct(activation.unaryExpr(&activation_functions::tanh_transfer_derivative).transpose());
    }
    else if(type == "sigmoid") {
        delta = grad_output.cwiseProduct(activation.unaryExpr(&activation_functions::sigmoid_transfer_derivative).transpose());
    }

    /*
    cout << "1" << endl;
    cout << "delta" << endl;
    cout << delta << endl;
    cout << "activation" << endl;
    cout << last_input.transpose() << endl;
    cout << "weights" << endl;
    Eigen::MatrixXd a(1, 3);
    Eigen::VectorXd b(2);
    Eigen::MatrixXd c = b.array().rowwise() * a.array();
    cout << c << endl;
    Eigen::MatrixXd test = delta.array().rowwise() * last_input.transpose().array();
    cout << test << endl;
    weigths = weigths ;//+ delta.array().colwise() * last_input.transpose().array();
    cout << "2" << endl;
    return weigths * delta;
    */
    Eigen::MatrixXd grad_input = weigths * delta;

    Eigen::MatrixXd delta_weights = last_input.transpose() * delta.transpose();
    weigths = weigths + delta_weights * learning_rate;

    Eigen::MatrixXd delta_biases = delta.rowwise().mean() * last_input.rows();
    biases = biases + delta_biases.transpose() * learning_rate;

    return grad_input;

    /*
    cout << delta << endl;
    Eigen::MatrixXd grad_input = weigths * delta;
    cout << grad_input << endl;
    cout << "2" << endl;
    Eigen::MatrixXd grad_weights = activation.transpose() * delta;
    cout << activation << endl;
    cout << "3" << endl;
    Eigen::MatrixXd grad_biases = delta.rowwise().mean() * weigths.rows();
    cout << "4" << endl;
    weigths = weigths - learning_rate * grad_weights;
    cout << "5" << endl;
    biases = biases - learning_rate * grad_biases.transpose();
    cout << "6" << endl;
    return grad_input;
    */
}

Eigen::MatrixXd Dense::getActivation() {
    return activation;
}

Dense::~Dense() {
    cout << "Object deconstructed!" << endl;
}