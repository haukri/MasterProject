#include "Filter.h"

Filter::Filter(int input_size, int output_size, double* learning_rate, string type) {
    clock = Clock::getInstance();
    double normalizedFreq = 6.0 / (1.0 / clock->getDt());
    cout << "normfreq: " << normalizedFreq << endl;
    output = Eigen::MatrixXd(1, 1);
    if(type == "lowpass") {
        filter.lowpass(5000, normalizedFreq);
    }
};

Eigen::MatrixXd Filter::forward(Eigen::MatrixXd input) {
    output(0,0) = filter.filter(input(0,0));
    return output;
};