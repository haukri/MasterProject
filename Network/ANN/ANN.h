#pragma once
#include <vector>
#include "../../Eigen/Dense"
#include "./Layer.h"

using namespace std;

class ANN
{
public:
    ANN();

    void addLayer(int size);

    void setInputSize(int size);
    void setLearningRate(int learning_rate);

    void build();
    Eigen::MatrixXf predict(Eigen::MatrixXf input);

    ~ANN();

private:
    vector<Layer*> layers;
    vector<int> layerSizes; 
    int inputSize = 0;
    double learning_rate;
};
