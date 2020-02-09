#pragma once
#include <vector>
#include "Eigen/Core"
#include "Layer.h"
#include "Dense.h"
#include "activation_functions.h"

using namespace std;

class ANN
{
public:
    ANN();

    void addLayer(int size, string type);

    void setInputSize(int size);
    void setLearningRate(double learning_rate);

    int getInputSize();

    void fit(Eigen::MatrixXd X, Eigen::MatrixXd y);
    Eigen::MatrixXd predict(Eigen::MatrixXd input);

    ~ANN();

private:
    vector<Layer*> layers;
    vector<int> layerSizes;
    int inputSize = 0;
    double learning_rate;
};
