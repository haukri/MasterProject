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
    void setOutputSize(int size);
    void setLearningRate(int learning_rate);

    void build();

    ~ANN();

private:
    vector<Layer> layers;
    vector<int> layerSizes; 
    int inputSize = 0;
    int outputSize = 0;
    double learning_rate;
};
