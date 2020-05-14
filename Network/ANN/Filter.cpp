#include "Filter.h"

Filter::Filter(int input_size, int output_size, double* learning_rate, string type) {
    clock = Clock::getInstance();
    int pos = type.find_first_of(',');
    string filterType = type.substr(0, pos);
    string cutoffFreq = type.substr(pos+1);
    double normalizedFreq = stoi(cutoffFreq) / (1.0 / clock->getDt());
    output = Eigen::MatrixXd(1, 1);
    if(filterType == "lowpass") {
        filter.lowpass(2000, normalizedFreq);
    }
};

Eigen::MatrixXd Filter::forward(Eigen::MatrixXd input) {
    output(0,0) = filter.filter(input(0,0));
    return output;
};