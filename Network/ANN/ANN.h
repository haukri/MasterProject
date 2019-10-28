#pragma once
#include <vector>
#include "../../Eigen/Dense"

using namespace std;

class ANN
{
public:
    ANN();

    void addLayer(int size);

    ~ANN();

private:
    vector<Eigen::VectorXf> layers;
};
